#pragma once

#include <random>
#include <iostream>

namespace rdm {

std::mt19937 gen;

void init(unsigned int seed) {
    gen = std::mt19937(seed);
}

double randreal() {
    std::uniform_real_distribution<double> dis(0,1);
    return dis(gen);
}

double randbeta(double alpha, double beta) {
    std::gamma_distribution<double> gamma1(alpha, 1), gamma2(beta, 1);
    double a = gamma1(gen), b = gamma2(gen);
    return a/(a+b);
}

} // namespace rdm
