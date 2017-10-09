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
  std::cout << "Start test_constructor." << std::endl;
  cusolverDnHandle_t cusolverDnHandle;

  // Create cuSolver handle
  int gpuid = 0;
  checkError(cudaSetDevice(gpuid));
  checkError(cusolverDnCreate(&cusolverDnHandle));
  checkError(cusolverDnDestroy(&cusolverDnHandle));

  std::cout << "finished test_constructor." << std::endl;
  return 0;
}
