#ifndef NOISE_HPP
#define NOISE_HPP

#include <random>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

namespace noise
{

    template<unsigned int Dims, class RNG = mt19937_64, typename FloatingPoint = float>
    class basePerlin
    {
    public:
        static const constexpr int Corners = 1 << Dims;

        typedef Matrix<FloatingPoint, Dynamic, 1> VectorXd;
        typedef Matrix<FloatingPoint, Dims, 1> VectorNd;
        typedef Matrix<int, Dims, 1> VectorNi;

        static_assert(Dims > 1);

        /**
         * @param size          Grid size, the higher, the more random, but the greater memory and computational cost.
         * @param resolution    Scales the grid
         * @param seed          Initial seed
         * @param engine        Random number generator
         */
        basePerlin(int size[Dims], FloatingPoint resolution, uint32_t seed = default_random_engine::default_seed, RNG engine = RNG());
        
        /**
         * Generates a perlin noise scalar at position v.
         * @param  v Position
         * @return   Noise
         */
        FloatingPoint noise(VectorNd v);

        /**
         * Reseeds underlying grid.
         * @param seed
         */
        void reseed(uint32_t seed);

    protected:

        /**
         * Returns gradient at respective position. Tiled.
         * @param  p [description]
         * @return   [description]
         */
        inline VectorNd gradient(VectorNd p)
        {
            int k = (int)p[0] % size_[0];

            for (int j = 1; j < Dims; ++j)
            {
                k = k * size_[j] + ((int)p[j] % size_[j]);
            }

            return grid_[k];
        }

        int numel_;
        int size_[Dims];
        VectorNd *grid_;
        VectorNd offsets_[Corners];
        FloatingPoint resolution_;
        RNG engine_;
    };

    template<unsigned int Dims, class RNG = mt19937_64, typename FloatingPoint = float>
    class perlin : public basePerlin<Dims, RNG, FloatingPoint>
    {};

    template<class RNG, typename FloatingPoint>
    class perlin<2, RNG, FloatingPoint> : public basePerlin<2, RNG, FloatingPoint>
    {
    public:
        using VectorNd = typename basePerlin<2, RNG, FloatingPoint>::VectorNd;

        using basePerlin<2, RNG, FloatingPoint>::basePerlin;
        using basePerlin<2, RNG, FloatingPoint>::noise;

        FloatingPoint noise(FloatingPoint x, FloatingPoint y)
        {
            return noise(VectorNd(x, y));
        }
    };

    template<class RNG, typename FloatingPoint>
    class perlin<3, RNG, FloatingPoint> : public basePerlin<3, RNG, FloatingPoint>
    {
    public:
        using VectorNd = typename basePerlin<3, RNG, FloatingPoint>::VectorNd;

        using basePerlin<3, RNG, FloatingPoint>::basePerlin;
        using basePerlin<3, RNG, FloatingPoint>::noise;

        FloatingPoint noise(FloatingPoint x, FloatingPoint y, FloatingPoint z)
        {
            return noise(VectorNd(x, y, z));
        }
    };

    template<class RNG, typename FloatingPoint>
    class perlin<4, RNG, FloatingPoint> : public basePerlin<4, RNG, FloatingPoint>
    {
    public:
        using VectorNd = typename basePerlin<4, RNG, FloatingPoint>::VectorNd;

        using basePerlin<4, RNG, FloatingPoint>::basePerlin;
        using basePerlin<4, RNG, FloatingPoint>::noise;

        FloatingPoint noise(FloatingPoint x, FloatingPoint y, FloatingPoint z, FloatingPoint w)
        {
            return noise(VectorNd(x, y, z, w));
        }
    };

    typedef perlin<2> perlin2;
    typedef perlin<3> perlin3;
    typedef perlin<4> perlin4;


};


#endif