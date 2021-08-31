#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <array>

template<typename T, size_t N> 
void print(std::array<T,N> values, std::array<T,N> residuals) {
  for (size_t i = 0; i < N; i++) {
    std::cout << i << "th eigenvalue = " << values.at(i) << ", Residual of " << i << "th eigenpair = " << residuals.at(i) << std::endl;
  }
};

#endif
