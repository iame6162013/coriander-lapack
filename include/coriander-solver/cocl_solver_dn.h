#pragma once

#include "cocl/cocl_streams.h"
#include "coriander-clblast/cocl_blas.h"
//#include "coriander_plugins/corianderclblast/coriander-clblast/cocl_blas.h"

typedef int cusolverStatus_t;

struct cusolverContext {

};
typedef struct cusolverContext* cusolverDnHandle_t;


extern "C" {
cusolverStatus_t cusolverDnCreate(cusolverDnHandle_t *p_handle);
cusolverStatus_t cusolverDnDestroy(cusolverDnHandle_t *p_handle);



//TODO: implement 'helper' functions
cusolverStatus_t cusolverDnSetStream(cusolverDnHandle_t handle, cudaStream_t streamId);
cusolverStatus_t cusolverDnGetStream(cusolverDnHandle_t handle, cudaStream_t *streamId);

//TODO: implement 'solver' functions

//Calculate the minimum size of the work buffers.
cusolverStatus_t cusolverDnSpotrf_bufferSize(cusolverDnHandle_t handle,cublasFillMode_t uplo, int n, float *A, int lda, int *Lwork );            //Single
cusolverStatus_t cusolverDnDpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *Lwork );           //Double
// cusolverStatus_t cusolverDnCpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, int *Lwork );       //Complex
// cusolverStatus_t cusolverDnZpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, int *Lwork);  //Double complex



}


//Shouold CUSOLVER_STATUS_SUCCESS be part of an enum or a define?
enum SolverErrors {
  CUSOLVER_STATUS_SUCCESS = 0,
  CUSOLVER_STATUS_NOT_INITIALIZED = 70000,
  CUSOLVER_STATUS_MATRIX_TYPE_NOT_SUPPORTED,
  CUSOLVER_STATUS_ALLOC_FAILED,
  CUSOLVER_STATUS_INVALID_VALUE,
  CUSOLVER_STATUS_ARCH_MISMATCH,
  CUSOLVER_STATUS_MAPPING_ERROR,
  CUSOLVER_STATUS_EXECUTION_FAILED,
  CUSOLVER_STATUS_INTERNAL_ERROR
};
