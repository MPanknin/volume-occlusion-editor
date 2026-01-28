/**
 * @file cutil_inline.h
 * @brief CUDA utility functions - Modern compatibility layer
 *
 * This replaces the deprecated CUDA SDK cutil library with modern equivalents.
 * Original code used CUDA SDK 4.0 utilities which are no longer available.
 */

#ifndef __CUTIL_INLINE_H__
#define __CUTIL_INLINE_H__

#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

// Compatibility for old CUDA SDK macros
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check for CUDA errors and exit on failure
 */
inline void __cudaSafeCall(cudaError_t err, const char *file, const int line) {
    if (cudaSuccess != err) {
        fprintf(stderr, "CUDA error in file '%s' in line %i : %s.\n",
                file, line, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}

#define cudaSafeCall(err) __cudaSafeCall(err, __FILE__, __LINE__)
#define cutilSafeCall(err) __cudaSafeCall(err, __FILE__, __LINE__)
#define CUDA_SAFE_CALL(err) __cudaSafeCall(err, __FILE__, __LINE__)

/**
 * Check for CUDA errors from kernel launches
 */
inline void __cutilCheckMsg(const char *errorMessage, const char *file,
                            const int line) {
    cudaError_t err = cudaGetLastError();
    if (cudaSuccess != err) {
        fprintf(stderr, "CUDA error: %s in file '%s' in line %i : %s.\n",
                errorMessage, file, line, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}

#define cutilCheckMsg(msg) __cutilCheckMsg(msg, __FILE__, __LINE__)
#define CUT_CHECK_ERROR(msg) __cutilCheckMsg(msg, __FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif // __CUTIL_INLINE_H__
