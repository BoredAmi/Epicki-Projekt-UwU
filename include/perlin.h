#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <vector>

class PerlinNoise {
public:
    PerlinNoise(unsigned int seed = 2023);

    double noise(double x, double y) const;

private:
    std::vector<int> p;

    double fade(double t) const;
    double lerp(double t, double a, double b) const;
    double grad(int hash, double x, double y) const;
};

#endif // PERLINNOISE_HPP
