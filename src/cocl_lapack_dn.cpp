
#include "coriander-lapack/cocl_lapack_dn.h"

#include <iostream>
#include "EasyCL/util/easycl_stringhelper.h"
#include "cocl/hostside_opencl_funcs.h"

#include "clLapack_source_code.h"

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


//////Cholesky decomposition
//
// Could be used for an inplace matrix decomposition.
// We won't do this(yet)
//
// Arguments:
//   handle:             The handle
//   uplo:               input will be an upper- or lower-trangle matrix
//   n                   num rows?
//   *A                  The matrix //positive definite hermitian matrix
//   lda                 Dimension of a?
//   *workspace_size     Size of the workspace needed for cusolverDnSpotrf
cusolverStatus_t cusolverDnSpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *workspace_size){
  return 0;
}
cusolverStatus_t cusolverDnDpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *workspace_size){
  return 0;
}

// We'll implement it using a Cholesky-Crout implementation
//
// Arguments
//   handle:             The handle
//   uplo:               input will be an upper- or lower-trangle matrix
//   n                   num rows?
//   *A                  The matrix //positive definite hermitian matrix
//   lda                 Dimension of a?
//   *Workspace          pointer to the workspace(on the gpu)
//   workspace_size      Size of the workspace needed for cusolverDnSpotrf
//   *devInfo            ???
cusolverStatus_t cusolverDnSpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float  *A, int lda, float  *Workspace, int workspace_size, int *devInfo){
  easycl::CLKernel *kernel = cocl::compileOpenCLKernel("float_potrf", getFloatPotrfSourceCode());


  const size_t size = 5;
  kernel->run(1, size, size);
}
cusolverStatus_t cusolverDnDpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *Workspace, int workspace_size, int *devInfo){
  //easycl::CLKernel *kernel = cocl::compileOpenCLKernel("double_potrf", getDoublePotrfSourceCode());
  //TODO: implement
}



// LU decomposition
// cusolverStatus_t cusolverDnDgetrf(cusolverDnHandle_t handle, ...){
//
// }
