#include <iostream>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "cusolverDn.h"

void checkError(size_t status){
  if(status != 0) {
    std::cout << "ERROR status non-zero: " << status << std::endl;
  }
}

int main(){
  cout << "Start test_constructor." << endl;
  cusolverDnHandle_t cusolverDnHandle;

  // Create CUBLAS and CUDNN handles
  int gpuid = 0;
  checkError(cudaSetDevice(gpuid));
  checkError(cusolverCreate(&cusolverDnHandle));
  checkError(cusolverDnDestroy(&cusolverDnHandle));

  cout << "finished test_constructor." << endl;
  return 0;
}
