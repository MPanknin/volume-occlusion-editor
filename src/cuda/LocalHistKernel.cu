#ifndef __Kernel_CU__
#define __Kernel_CU__

#include "../common/include/cutil_inline.h"
#include "../common/include/cutil_math.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#define TYPE uchar
#define MULT 256

const int numBins = 1;

texture<TYPE, 3, cudaReadModeNormalizedFloat> d_tex3D;
cudaArray* d_volArray = 0;

__device__ float d_occprev[2000000];
__device__ float d_vis[MULT];

#define INT_MIN     (-2147483647 - 1)
#define INT_MAX       2147483647

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
#define GET_IDS() uint tx = threadIdx.x; uint ty = threadIdx.y;\
                  uint bx = blockIdx.x * blockDim.x; \
                  uint by = blockIdx.y * blockDim.y; \
                  uint x = bx + tx; uint y = by + ty;

// ============================================================================
/**
 * Local histogram kernel that computes histograms within a 3D neighborhood.
 * For each voxel, computes a histogram of intensity values within a cubic
 * neighborhood of radius 'rad', then normalizes the histogram bins.
 */
__global__ void
d_occ(TYPE* d_out, cudaExtent vd,
      const int rad, const int negRad,
      const float z, const float www, const float occScale)
{
  GET_IDS();

  float binBuffer[numBins];
  int binSize = 256 / numBins;

  for(int i = -rad; i <= rad; i++)
  {
    for(int j = -rad; j <= rad; j++)
    {
      for(int k = -rad; k <= rad; k++)
      {
        float u = ((int)x + i) / (float)vd.width;
        float v = ((int)y + j) / (float)vd.height;
        float w = ((int)z + k) / (float)vd.depth;

        u = max(0.0f, u);
        v = max(0.0f, v);
        w = max(0.0f, w);

        u = min(1.0f, u);
        v = min(1.0f, v);
        w = min(1.0f, w);

        float val = tex3D(d_tex3D, u, v, w) * 255.0f;
        for(int i = 0; i < numBins; i++)
        {
          if(val >= i * binSize && val < (i + 1) * binSize)
          {
            binBuffer[i]++;
          }
        }
      }
    }
  }

  __syncthreads();

  float maxVal = INT_MIN;
  float minVal = INT_MAX;

  for(int i = 0; i < numBins; i++)
  {
    float val = binBuffer[i];
    maxVal = val > maxVal ? val: maxVal;
    minVal = val < minVal ? val: minVal;
  }

  for(int i = 0; i < numBins; i++)
  {
    binBuffer[i] -= minVal;
    binBuffer[i] *= ((float) 255 / maxVal);
  }

  __syncthreads();

  if(x < vd.width && y < vd.height && z < vd.depth)
  {
    uint idx = calcIdx(vd, x * numBins, y * numBins, z * numBins);

    if(z >= 0)
    {
      for(int i = 0; i < numBins; i++)
      {
        d_out[idx + i] = binBuffer[i];
      }
    }
  }
}

// ============================================================================
/**
 * Brute-force averaging kernel that computes the mean intensity value
 * within a 3D neighborhood of radius 'rad' for each voxel.
 */
__global__ void
d_occ_bruteforce(TYPE* d_out, cudaExtent vd,
      const int rad, const int negRad,
      const float z, const float www, const float occScale)
{
  GET_IDS();

  float sum = 0.0f;
  long int samplesTaken = 0;

  for(int i = -rad; i <= rad; i++)
  {
    for(int j = -rad; j <= rad; j++)
    {
      for(int k = -rad; k <= rad; k++)
      {
        float u = ((int)x + i) / (float)vd.width;
        float v = ((int)y + j) / (float)vd.height;
        float w = ((int)z + k) / (float)vd.depth;

        u = max(0.0f, u);
        v = max(0.0f, v);
        w = max(0.0f, w);

        u = min(1.0f, u);
        v = min(1.0f, v);
        w = min(1.0f, w);

        float val = tex3D(d_tex3D, u, v, w) * 255.0f;
        sum += val;
        samplesTaken++;
      }
    }
  }

  sum /= samplesTaken;

  __syncthreads();

  if(x < vd.width && y < vd.height && z < vd.depth)
  {
    uint idx = calcIdx(vd, x, y, z);
    d_out[idx] = (uchar)sum;
  }
}

// ============================================================================
/**
 * Host wrapper function that launches the local histogram computation kernel.
 * Processes the volume slice by slice using the brute-force averaging method.
 */
extern "C" void
kernel(TYPE* h_out, cudaExtent vd, const int rad, const float occScale)
{
  printf(__FUNCTION__);
  printf("\n");

  uint size = vd.width * vd.height * vd.depth * sizeof(TYPE) * numBins;
  TYPE* d_out;
  cudaMalloc((void**) &d_out, size);
  checkCUDAError("cudaMalloc d_out");

  const dim3 block(32, 32);
  const dim3 grid((vd.width / block.x) + 1, (vd.height / block.y) + 1);

  float w = 2.0f * rad + 1.0f;
  w = w * w * w;
  const int negRad = -(rad + 1);

  for(int i = 0; i <= (int)vd.depth; i++)
  {
    d_occ_bruteforce<<<grid, block>>>(d_out, vd, rad, negRad, (float)i, w, occScale);

    checkCUDAError("kernel function");
    cudaDeviceSynchronize();
  }

  cudaMemcpy(h_out, d_out, size, cudaMemcpyDeviceToHost);
  checkCUDAError("memcpy result back to h_out");

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
  printf(__FUNCTION__);
  printf("\n");

  cudaMemcpyToSymbol("d_vis", vis, sizeof(float) * MULT, 0, cudaMemcpyHostToDevice);

  checkCUDAError("memcpy to vis");

  printf("Done\n");
}

// ============================================================================
/**
 * Binds the 3D volume data to a CUDA texture for efficient sampling.
 */
extern "C"
void bindVolume(const TYPE* h_vol, cudaExtent vd)
{
  printf(__FUNCTION__);
  printf("\n");

  cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<TYPE>();

  cutilSafeCall(cudaMalloc3DArray(&d_volArray, &channelDesc, vd));

  cudaMemcpy3DParms copyParams = {0};
  copyParams.srcPtr = make_cudaPitchedPtr((void*)h_vol,
                                          vd.width*sizeof(TYPE),
                                          vd.width, vd.height);

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

  printf("Done \n");
}
#endif
