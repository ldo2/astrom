#include "RandomGenerator.hpp"

#include <cmath>

/*
 * class RandomGenerator
 */

    RandomGenerator::RandomGenerator() 
     : a(69069u), c(5u), state(1013904223u) {}

    RandomGenerator::~RandomGenerator() {}

    double RandomGenerator::rand() {
      state = a * state + c;
      return (double)((state >> 15) & 0x7fff)/0x7fff;
    }

    double RandomGenerator::rand(double range_max) {
      return range_max * rand();
    }

    double RandomGenerator::rand(double range_min, double range_max) {
      return range_min + (range_max - range_min) * rand();
    }
    
    double RandomGenerator::normal(double m, double sigma) {
      const double PI = 3.14159265358979;
      double r, phi;
      double value;

      r   = rand();
      phi = rand();

      value = std::sin(2*PI*phi) * std::sqrt(-2.0*(r > 0.0 ? std::log(r) : r));

      return m + sigma * value;
    }

