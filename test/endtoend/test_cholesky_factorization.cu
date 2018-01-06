#include <iostream>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <clblast.h>

#include "cublas_v2.h"
#include "cusolverDn.h"



void checkError(size_t status){
  if(status != 0) {
    std::cout << "ERROR status non-zero: " << status << std::endl;
  }
}

//TODO: this won't work for huge values.
//we need this because floats don't have infinite precision.
bool floatRoughlyEquals(float a, float b){
  if(a==b){
    return true;
  }
  if(abs(a-b)<1){
    return true;
  }
}

bool arrayMatch(float* A, float* B, int N){
  for(int i=0; i<N; i++){
    if(!floatRoughlyEquals(A[i], B[i])){
      return false;
    }
  }
  return true;
}

int main(){
  std::cout << "Start test_cholesky_factorization." << std::endl;
  cusolverDnHandle_t cusolverDnHandle;


  //The test:
  //Matrix_1 * Matrix_1 = Matrix_2
  //potrf(Matrix_2) == Matrix_1
  int N = 5;
  int leading_dimension_1 = N; //This is sometimes equal to the number of rows, it's not that complex is it? (haha).
  //It's the total number of rows of the matrix in memory.
  float host_Matrix_1[] =
  {1, 0, 0, 0, 0,
  1, 2, 0, 0, 0,
  1, 2, 3, 0, 0,
  56, 2, 9, 9, 0,
  56, 2, 9, 9, 2};






  cublasHandle_t blas;
  cublasCreate(&blas);
  cublasSetStream(blas, stream);


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
  cuMemAlloc(&device_Matrix_1, N^2 * sizeof(float));
  cuMemcpyHtoDAsync(device_Matrix_1, host_Matrix_1, N^2 * sizeof(float), stream);



  CUdeviceptr device_Matrix_2;
  cuMemAlloc(&device_Matrix_2, N^2 * sizeof(float));
  float alpha = 1f;
  float beta = 1f;
  int leading_dimension_2 = leading_dimension_1;
  cublasSgemm(blas, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &alpha, (float*) device_Matrix_1, leading_dimension_1, (float*) device_Matrix_1, &beta, device_Matrix_2, leading_dimension_1);




  int workspace_size;
  cusolverDnSpotrf_bufferSize(cusolverDnHandle, upperOrLower, N, (float *) device_Matrix_2, leading_dimension_2, &workspace_size);
  CUdeviceptr workspace=0; //this is on the gpu
  cuMemAlloc(&workspace, workspace_size * sizeof(float));

  int devInfo;
  cusolverDnSpotrf(cusolverDnHandle, upperOrLower, N, (float *) device_Matrix_2, leading_dimension_2, (float*) workspace, workspace_size, &devInfo);

  //We don't want an error do we?
  assert(devInfo==0);




  float host_Matrix_2[N^2];
  cuMemcpyDtoHAsync(host_Matrix_2, device_Matrix_2, N^2 * sizeof(float), stream);

  arrayMatch(host_Matrix_1, host_Matrix_2, N^2);

  /*for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        std::cout << "Element(" << i << ", " << j << ") = " << host_Matrix_2[i*N+j] << std::endl;
      }
  }*/

  checkError(cublasDestroy(blas));
  checkError(cusolverDnDestroy(&cusolverDnHandle));
  cuStreamDestroy(stream);

  std::cout << "finished test_cholesky_factorization." << std::endl;
  return 0;
}
