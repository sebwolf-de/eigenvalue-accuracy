#include <iostream>

#include <Eigen/Dense>

#include "values.h"
#include "printer.h"

int main() {
  using Matrix = Eigen::Matrix<double, N, N>;
  using CVector = Eigen::Matrix<std::complex<double>, N, 1>;

  Matrix A = Matrix(matrixValues);
  Eigen::ComplexEigenSolver<Matrix> eigensolver(A);
  if (eigensolver.info() != Eigen::Success) abort();

  std::array<std::complex<double>, N> eigenvalues;
  std::array<std::complex<double>, N> residuals;
  for (unsigned i = 0; i < N; i++) {
    eigenvalues[i] = eigensolver.eigenvalues()(i);
    const CVector v = eigensolver.eigenvectors().col(i);
    const CVector matrixMult = A * v;
    const CVector vectorMult = eigensolver.eigenvalues()(i) * v;
    double residual = (matrixMult - vectorMult).norm();
    residuals[i] = residual;
  }
  print(eigenvalues, residuals);
}
