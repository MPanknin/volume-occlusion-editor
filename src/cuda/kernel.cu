#ifndef __Kernel_CU__
#define __Kernel_CU__

#include "../common/include/cutil_inline.h"
#include "../common/include/cutil_math.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#ifdef BIT_16
  #define TYPE ushort
  #define MULT 65536
#else
  #define TYPE uchar
  #define MULT 256
#endif

texture<TYPE, 3, cudaReadModeNormalizedFloat> d_tex3D;
cudaArray* d_volArray = 0;

__device__ float d_occprev[2000][2000];
__device__ float d_vis[MULT];

// ============================================================================
void checkCUDAError(const char* msg)
{
  cudaError_t err = cudaGetLastError();
  if(cudaSuccess != err)
  {
    fprintf(stderr, "Cuda error: %s: %s.\n", msg, cudaGetErrorString(err));
    exit(EXIT_FAILURE);
  }
}

// ============================================================================
__device__ uint
calcIdx(const cudaExtent vd, const uint x, const uint y, const uint z)
{
  uint SLICE = vd.width * vd.height * z;
  uint ROW = vd.width * y;
  uint COLUMN = x;
  return SLICE + ROW + COLUMN;
}

// ============================================================================
#define IMAD(a, b, c)(__mul24((a), (b)) + (c))

// ============================================================================
#define GET_IDS() uint tx = threadIdx.x; uint ty = threadIdx.y;\
                  uint bx = blockIdx.x * blockDim.x; \
                  uint by = blockIdx.y * blockDim.y; \
                  uint x = bx + tx; uint y = by + ty;

// ============================================================================
#define LOAD_ADD(lowx, upx, lowy, upy)\
for(int i = lowx; i <= upx; i++)\
{\
  for(int j = lowy; j <= upy; j++)\
  {\
    float u = (bx + i) / (float)vd.width;\
    float v = (by + j) / (float)vd.height;\
    int addPx = tex3D(d_tex3D, u, v, zAdd) * (float)MULT;\
    ds_slice[i+rad][j+rad] = d_vis[addPx];\
  }\
}

// ============================================================================
#define LOAD_SUBT(lowx, upx, lowy, upy)\
for(int i = lowx; i <= upx; i++)\
{\
  for(int j = lowy; j <= upy; j++)\
  {\
    float u = (bx + i) / (float)vd.width;\
    float v = (by + j) / (float)vd.height;\
    int subtPx = tex3D(d_tex3D, u, v, zSubt) * (float)MULT;\
    ds_slice[i+rad][j+rad] = d_vis[subtPx];\
  }\
}

// ============================================================================
/**
 * Slice-wise occlusion generation kernel with shared memory optimization.
 * Computes occlusion by comparing intensities between front and back slices
 * within a neighborhood radius. Uses cached occlusion values from previous slices.
 */
__global__ void
d_occ(TYPE* d_out, cudaExtent vd,
      const int rad, const int negRad,
      const float z, const float w, const float occScale)
{
  GET_IDS();

  const int SMEM_SIZE = 150;
  __shared__ TYPE ds_slice[SMEM_SIZE][SMEM_SIZE];

  int low = -rad;
  int upx = rad + (int)blockDim.x;
  int upy = rad + (int)blockDim.y;

  float zAdd = (z + (float)rad) / (float)vd.depth;
  float zSubt = (z + (float)negRad) / (float)vd.depth;

  __syncthreads();

  if(tx == 0 && ty == 0)
    LOAD_ADD(low, low / 2,  low, low / 2);
  if(tx == 1 && ty == 1)
    LOAD_ADD(low / 2, 0,    low, low / 2);
  if(tx == 2 && ty == 2)
    LOAD_ADD(0, upx / 2,    low, low / 2);
  if(tx == 3 && ty == 3)
    LOAD_ADD(upx / 2, upx,  low, low / 2);

  if(tx == 4 && ty == 4)
    LOAD_ADD(low, low / 2,  low / 2, 0);
  if(tx == 5 && ty == 5)
    LOAD_ADD(low / 2, 0,    low / 2, 0);
  if(tx == 6 && ty == 6)
    LOAD_ADD(0, upx / 2,    low / 2, 0);
  if(tx == 7 && ty == 7)
    LOAD_ADD(upx / 2, upx,  low / 2, 0);

  if(tx == 8 && ty == 8)
    LOAD_ADD(low, low / 2,  0, upy / 2);
  if(tx == 9 && ty == 9)
    LOAD_ADD(low / 2, 0,    0, upy / 2);
  if(tx == 10 && ty == 10)
    LOAD_ADD(0, upx / 2,    0, upy / 2);
  if(tx == 11 && ty == 11)
    LOAD_ADD(upx / 2, upx,  0, upy / 2);

  if(tx == 12 && ty == 12)
    LOAD_ADD(low, low / 2,  upy / 2, upy);
  if(tx == 13 && ty == 13)
    LOAD_ADD(low / 2, 0,    upy / 2, upy);
  if(tx == 14 && ty == 14)
    LOAD_ADD(0, upx / 2,    upy / 2, upy);
  if(tx == 15 && ty == 15)
    LOAD_ADD(upx / 2, upx,  upy / 2, upy);

  __syncthreads();

  float add = 0.0f;
  for(int i = -rad; i <= rad; i++)
  {
    for(int j = -rad; j <= rad; j++)
    {
      add += ds_slice[tx + i + rad][ty + j + rad];
    }
  }

  __syncthreads();

  if(tx == 0 && ty == 0)
    LOAD_SUBT(low, low / 2,  low, low / 2);
  if(tx == 1 && ty == 1)
    LOAD_SUBT(low / 2, 0,    low, low / 2);
  if(tx == 2 && ty == 2)
    LOAD_SUBT(0, upx / 2,    low, low / 2);
  if(tx == 3 && ty == 3)
    LOAD_SUBT(upx / 2, upx,  low, low / 2);

  if(tx == 4 && ty == 4)
    LOAD_SUBT(low, low / 2,  low / 2, 0);
  if(tx == 5 && ty == 5)
    LOAD_SUBT(low / 2, 0,    low / 2, 0);
  if(tx == 6 && ty == 6)
    LOAD_SUBT(0, upx / 2,    low / 2, 0);
  if(tx == 7 && ty == 7)
    LOAD_SUBT(upx / 2, upx,  low / 2, 0);

  if(tx == 8 && ty == 8)
    LOAD_SUBT(low, low / 2,  0, upy / 2);
  if(tx == 9 && ty == 9)
    LOAD_SUBT(low / 2, 0,    0, upy / 2);
  if(tx == 10 && ty == 10)
    LOAD_SUBT(0, upx / 2,    0, upy / 2);
  if(tx == 11 && ty == 11)
    LOAD_SUBT(upx / 2, upx,  0, upy / 2);

  if(tx == 12 && ty == 12)
    LOAD_SUBT(low, low / 2,  upy / 2, upy);
  if(tx == 13 && ty == 13)
    LOAD_SUBT(low / 2, 0,    upy / 2, upy);
  if(tx == 14 && ty == 14)
    LOAD_SUBT(0, upx / 2,    upy / 2, upy);
  if(tx == 15 && ty == 15)
    LOAD_SUBT(upx / 2, upx,  upy / 2, upy);

  __syncthreads();

  float subt = 0.0f;
  for(int i = -rad; i <= rad; i++)
  {
    for(int j = -rad; j <= rad; j++)
    {
      subt += ds_slice[tx + i + rad][ty + j + rad];
    }
  }

  float diff = (add - subt) / w;

  __syncthreads();

  if(x < vd.width && y < vd.height && z < vd.depth)
  {
    float occ = diff + d_occprev[x][y];
    d_occprev[x][y] = occ;
    if(z >= 0)
    {
      uint idx = calcIdx(vd, x, y, z);
      d_out[idx] = occ * occScale;
    }
  }
}

// ============================================================================
/**
 * Host wrapper function for occlusion generation.
 * Manages memory allocation, data transfer, and kernel launch for slice-by-slice
 * occlusion computation.
 */
extern "C" void
kernel(TYPE* h_out, cudaExtent vd, const int rad, const float occScale)
{
  uint size = vd.width * vd.height * vd.depth * sizeof(TYPE);
  TYPE* d_out;
  cudaMalloc((void**) &d_out, size);
  checkCUDAError("cudaMalloc d_out");

  cudaMemcpy(d_out, h_out, size, cudaMemcpyHostToDevice);
  checkCUDAError("memcpy d_out");

  const dim3 block(32, 32);
  const dim3 grid((vd.width / block.x) + 1, (vd.height / block.y) + 1);

  float w = 2.0f * rad + 1.0f;
  w = w * w * w;
  const int negRad = -(rad + 1);

  for(int i = negRad; i <= (int)vd.depth; i++)
  {
    d_occ<<<grid, block>>>(d_out, vd, rad, negRad, (float)i, w, occScale);
    cudaDeviceSynchronize();
  }

  cudaMemcpy(h_out, d_out, size, cudaMemcpyDeviceToHost);

  cudaFree(d_out);
}

// ============================================================================
/**
 * Binds the visibility mapping lookup table to device memory.
 */
extern "C"
void bindMappingLoookup(const bool useMapping,
                        const float* vis)
{
  cudaMemcpyToSymbol("d_vis", vis, sizeof(float) * MULT, 0, cudaMemcpyHostToDevice);
  checkCUDAError("memcpy to vis");
}

// ============================================================================
/**
 * Binds the 3D volume data to a CUDA texture for efficient sampling.
 */
extern "C"
void bindVolume(const TYPE* h_vol, cudaExtent vd)
{
  cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<TYPE>();

  cutilSafeCall(cudaMalloc3DArray(&d_volArray, &channelDesc, vd));

  cudaMemcpy3DParms copyParams = {0};
  copyParams.srcPtr = make_cudaPitchedPtr((void*)h_vol,
    vd.width*sizeof(TYPE), vd.width, vd.height);

  copyParams.dstArray = d_volArray;
  copyParams.extent   = vd;
  copyParams.kind     = cudaMemcpyHostToDevice;
  cutilSafeCall(cudaMemcpy3D(&copyParams));

  d_tex3D.normalized = true;
  d_tex3D.filterMode = cudaFilterModePoint;
  d_tex3D.addressMode[0] = cudaAddressModeBorder;
  d_tex3D.addressMode[1] = cudaAddressModeBorder;
  d_tex3D.addressMode[2] = cudaAddressModeBorder;

  cutilSafeCall(cudaBindTextureToArray(d_tex3D, d_volArray, channelDesc));
}
#endif
