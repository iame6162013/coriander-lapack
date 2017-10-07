
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
