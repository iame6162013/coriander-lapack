#pragma once


typedef int cusolverStatus_t;

struct cubsolverContext {

};
typedef struct cusolverContext* cusolverDnHandle_t;


extern "C" {
cusolverStatus_t cusolverCreate(cusolverDnHandle_t *p_handle);
cusolverStatus_t cusolverDnDestroy(cusolverDnHandle_t *p_handle);
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
