#include <iostream>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "cublas_v2.h"
#include "cusolverDn.h"


void checkError(size_t status){
  if(status != 0) {
    std::cout << "ERROR status non-zero: " << status << std::endl;
  }
}

int main(){
  std::cout << "Start test_cholesky_factorization." << std::endl;
  cusolverDnHandle_t cusolverDnHandle;


  //Add matrix, etc

  //below needs to be a Hermitian matrix, also positive-definite matrix?
  float host_Matrix_1[] = {1, 2, 3, 4};
  int numRows_1 = 2;
  cublasFillMode_t upperOrLower = CUBLAS_FILL_MODE_LOWER;


  // Create CUstream, cuSolver and cuBlass handles
  int gpuid = 0;
  checkError(cudaSetDevice(gpuid));
  CUstream stream;
  cuStreamCreate(&stream, 0);

  cublasHandle_t blas;
  checkError(cublasCreate(&blas));
  cublasSetStream(blas, stream);

  checkError(cusolverDnCreate(&cusolverDnHandle));
  cusolverDnSetStream(cusolverDnHandle, stream);


  //Move matrici to device
  CUdeviceptr device_Matrix_1;
  cuMemAlloc(&device_Matrix_1, numRows_1^2 * sizeof(float));
  cuMemcpyHtoDAsync(device_Matrix_1, host_Matrix_1, numRows_1^2 * sizeof(float), stream);




  int leading_dimension_1 = numRows_1; //This is sometimes equal to the number of rows, it's complex (haha).
  //It's the total number of rows of the matrix in memory.
  int workspace_size;
  cusolverDnSpotrf_bufferSize(cusolverDnHandle, upperOrLower, numRows_1, (float *) device_Matrix_1, leading_dimension_1, &workspace_size);
  CUdeviceptr workspace=0; //this is on the gpu

  //TODO: this is a hack, and this hack is absent from 'normal' cuda code. This needs to be fixed some way.
  if(workspace_size!=0){
  	cuMemAlloc(&workspace, workspace_size * sizeof(float));
  }

  int devInfo;
  cusolverDnSpotrf(cusolverDnHandle, upperOrLower, numRows_1, (float *) device_Matrix_1, leading_dimension_1, (float*) workspace, workspace_size, &devInfo);

  //We don't want an error do we?
  assert(devInfo==0);

  //TODO; Check result.
  cuMemcpyDtoHAsync(host_Matrix_1, device_Matrix_1, numRows_1^2 * sizeof(float), stream);

  for(int i=0; i<numRows_1; i++){
      for(int j=0; j<numRows_1; j++){
        std::cout << "Element(" << i << ", " << j << ") = " << host_Matrix_1[i*numRows_1+j] << std::endl;
      }
  }

  checkError(cublasDestroy(blas));
  checkError(cusolverDnDestroy(&cusolverDnHandle));
  cuStreamDestroy(stream);

  std::cout << "finished test_cholesky_factorization." << std::endl;
  return 0;
}
