
#include "coriander-solver/cocl_solver_dn.h"

#include <iostream>

cusolverStatus_t cusolverDnCreate(cusolverDnHandle_t *p_handle){
  std::cout << "cusolverDnCreate" << std::endl;

  return CUSOLVER_STATUS_SUCCESS;
}

cusolverStatus_t cusolverDnDestroy(cusolverDnHandle_t *p_handle){
  std::cout << "cusolverDnDestroy" << std::endl;

  return CUSOLVER_STATUS_SUCCESS;
}

//TODO: implement
cusolverStatus_t cusolverDnSetStream(cusolverDnHandle_t handle, cudaStream_t streamId){

}
cusolverStatus_t cusolverDnGetStream(cusolverDnHandle_t handle, cudaStream_t *streamId){


}

//TODO: implement
cusolverStatus_t cusolverDnSpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *workspace_size ){

}
cusolverStatus_t cusolverDnDpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *workspace_size ){

}
cusolverStatus_t cusolverDnSpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float  *A, int lda, float  *Workspace, int workspace_size, int *devInfo ){

}
cusolverStatus_t cusolverDnDpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *Workspace, int workspace_size, int *devInfo ){

}
