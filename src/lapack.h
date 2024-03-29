#ifndef LAPACK_20210208_H
#define LAPACK_20210208_H

#include "FC.h"

extern "C" {
  #define FC_dgeev FC_GLOBAL(dgeev, DGEEV)
  extern int FC_dgeev(char*, char*, int*, double*, int*, double*, double*, double*, int*, double*, int*, double*, int*, int*);
  #define FC_dgemv FC_GLOBAL(dgemv, DGEMV)
  extern int FC_dgemv(char*, int*, int*, double*, double*, int*, double*, int*, double*, double*, int*);
}

#endif // LAPACK_20210208_H
