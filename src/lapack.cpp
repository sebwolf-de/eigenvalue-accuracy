#include <complex>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>

#include "lapack.h"
#include "values.h"
#include "printer.h"


int main(int argc, char** argv){

  int n = N;
  // allocate data
  char Nchar = 'N';
  char Vchar = 'V';
  double eigReal[N];
  double eigImag[N];
  double *vl;
  double vr[N*N];
  int one = 1;
  int lwork = 6*N;
  double work[lwork];
  int info;

  // dgeev overwrites the matrix, so we need to copy the values
  double A[N*N];
  std::copy(matrixValues, matrixValues+N*N, A);
  dgeev_(&Nchar, &Vchar, &n, A, &n, eigReal, eigImag, vl, &one, vr, &n, work, &lwork, &info);

  // check for errors
  if (info != 0){
    std::cout << "Error: dgeev returned error code " << info << std::endl;
    return -1;
  }

  double y[N];
  double alpha = 1.0;
  double beta = 0.0;

  std::array<std::complex<double>, N> eigenvalues;
  std::array<std::complex<double>, N> residuals;
  std::copy(matrixValues, matrixValues+N*N, A);
  for (int i = 0; i < N; i++){
    eigenvalues[i] = std::complex<double>(eigReal[i], eigImag[i]);

    double* vec = &vr[N*i];
    dgemv_(&Nchar, &n, &n, &alpha, A, &n, vec, &one, &beta, y, &one);

    double residual_squared = 0;
    for (int j = 0; j < N; j++){
      double diff = y[j] - eigReal[i] * vr[N*i+j];
      residual_squared += diff*diff;
    }
    residuals[i] = std::sqrt(residual_squared);
  }
  print(eigenvalues, residuals);

  return 0;
}
