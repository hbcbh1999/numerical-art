#ifndef BASIS_SPLINE
#define BASIS_SPLINE

#include <vector>
#include <Eigen/Core>

// 18-03-2020
// created by Jan Hünermann

using namespace std;
using namespace Eigen;

template<int Order, int Dims>
struct BSpline
{
    typedef Matrix<double, Dims, 1> VectorNd;

    vector<double> knots;
    vector<VectorNd> control_points;

    /**
     * Interpolates a point on the spline. Supply k to be faster.
     *
     * Algorithm from https://en.wikipedia.org/wiki/De_Boor%27s_algorithm.
     * @param  tau Value in the support of the spline.
     * @return     Point on spline.
     */
    VectorNd interpolate(double tau) const;
    VectorNd interpolate(double tau, int k) const;

    int findK(double tau) const;

    /**
     * Walks the spline.
     *
     * @param delta  Resolution
     * @param fn     Callback
     */
    void walk(double delta, void (*fn)(VectorNd pt, const BSpline &)) const;
    void walk(double delta, void (*fn)(VectorNd pt, const BSpline &), double a, double b) const;

    /**
     * Creates a spline from knots (numbers in support), and control points.
     * @param  knots          f(knots) = control_points. These are knot points.
     * @param  control_points The vectors at each knot point.
     * @return                BSpline
     */
    static BSpline create(vector<double> knots, vector<VectorNd> control_points, bool repeat_begin = true, bool repeat_end = true);

};

template<int Order>
using BSpline2 = BSpline<Order, 2>;

template<int Order>
using BSpline3 = BSpline<Order, 3>;

#endif