
#include "coriander-lapack/cocl_lapack_dn.h"


#include <iostream>

#include <EasyCL/EasyCL.h>
#include "EasyCL/util/easycl_stringhelper.h"

#include "cocl/hostside_opencl_funcs.h"
#include "cocl/cocl_context.h"

#include "coriander-lapack/clLapack_source_code.h"



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
  (*workspace_size) = 0;
  return CUSOLVER_STATUS_SUCCESS;
}
cusolverStatus_t cusolverDnDpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *workspace_size){
  (*workspace_size) = 0;
  return CUSOLVER_STATUS_SUCCESS;
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
	std::cout << "cusolverDnSpotrf" << std::endl;
	cocl::ThreadVars* v = cocl::getThreadVars();

	easycl::CLKernel* kernel = cocl::compileOpenCLKernel("float_potrf", getFloatPotrfSourceCode());

	char buf[16];

	kernel->inout(16, buf);
	kernel->run_1d( 16, 16);

	std::cout << "cusolverDnSpotrf: "  << buf << std::endl;
}
cusolverStatus_t cusolverDnDpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *Workspace, int workspace_size, int *devInfo){
  //easycl::CLKernel *kernel = cocl::compileOpenCLKernel("double_potrf", getDoublePotrfSourceCode());
  //TODO: implement
}



// LU decomposition
// cusolverStatus_t cusolverDnDgetrf(cusolverDnHandle_t handle, ...){
//
// }
