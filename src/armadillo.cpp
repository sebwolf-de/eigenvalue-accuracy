#include <iostream>

#include <armadillo> 

#include "values.h"
#include "printer.h"

int main () {
  using CMatrix = typename arma::Mat<std::complex<double>>::template fixed<N, N>;
  using Matrix = typename arma::Mat<double>::template fixed<N, N>;
  using CVector = typename arma::Col<std::complex<double>>::template fixed<N>;
  Matrix A(matrixValues);

  CMatrix armaEigenvectors(arma::fill::zeros);
  CVector armaEigenvalues(arma::fill::zeros);

  arma::eig_gen(armaEigenvalues, armaEigenvectors, A, "balance");

  std::array<std::complex<double>, N> eigenvalues;
  std::array<std::complex<double>, N> residuals;
  for (size_t i = 0; i < N; i++) {
    eigenvalues[i] = armaEigenvalues(i);

    CVector matrixMult = A * armaEigenvectors.col(i);
    CVector valueMult = armaEigenvalues(i) * armaEigenvectors.col(i);
    double residual = arma::norm(matrixMult - valueMult);
    residuals[i] = residual;
  }

  print(eigenvalues, residuals);

  return 0;
}

