#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP
#include <vector>
#include <random>

class SimplexNoise {
private:
    std::vector<int> p;
    std::vector<int> permutation;

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y);

public:
    SimplexNoise(unsigned int seed = std::random_device{}());
    double noise(double x, double y);
};
#endif // PERLINNOISE_HPP
