#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>

double f( double x, double y)
{
    return (5000 - 0.005*(x*x + y*y + x*y) + 12.5*(x+y))
        * exp(-fabs(0.000001 * (x*x + y*y) - 0.0015*(x+y) + 0.7));
}

// Computes f(x',y') where (x',y') is obtained from (x,y) by a step of the
// given size in the given direction.
double ff( double x, double y, double size, double angle)
{
    return f( x + cos( angle) * size, y + sin( angle) * size);
}

// Uses bisection to maximize f(x,0) with l <= x <= r.
double maximize( double l, double r, double tol)
{
    while( r-l > tol) {
        double m    = (l+r) / 2.0;
        double m2   = m + 1E-10;
        double h_m  = f( m,  0);
        double h_m2 = f( m2, 0);
        (h_m < h_m2 ? l : r) = m;
    }

    return (l+r) / 2.0;
}

// Uses bisection to find the angle in range [l, r] such that a step from (x,y)
// with the given size follows the contour line f_min of f. The angle is
// computed with tolerance tol.
double find_angle(
    double x, double y, double f_min, double l, double r, double tol, double size)
{
    while( r-l > tol) {
        double m   = (l+r) / 2.0;
        double h_m = ff( x, y, size, m);
        double h_l = ff( x, y, size, l);
        ((h_m > f_min) ^ (h_l > f_min) ? r : l) = m;
    }

    return (l+r) / 2.0;
}


// Finds the shortest path from (x0, y0) to (x1, y1) in steps of the given size
// such that the elevation f(x,y) at the intermediate points (x,y) does not
// exceed f_min. The value tol is the tolerance for the angle when following
// the contour line.
double find_path(
    double x0, double y0, double x1, double y1, double f_min, double tol, double size)
{
    double length = 0;
    double dist = sqrt( (y1-y0)*(y1-y0) + (x1-x0)*(x1-x0));

    while( dist > size) {

        // compute angle of straight line to target
        double angle = atan2( y1-y0, x1-x0);
        double h     = ff( x0, y0, size, angle);

        // if straight line is blocked compute angle of contour line
        if( h > f_min)
            angle = find_angle( x0, y0, f_min, angle - M_PI_2, angle + M_PI_2, tol, size);

        x0     += cos( angle) * size;
        y0     += sin( angle) * size;
        length += size;
        dist   =  sqrt( (y1-y0)*(y1-y0) + (x1-x0)*(x1-x0));
    }

    return length + dist;
}

int main( int /*argc*/, char* /*argv*/[])
{
    // The function is symmetric in x and y. A plot shows a volcano-like shape
    // with the start and ending point on the shoulders on opposite sides of
    // the volcano. The shortest path with minimal elevantion f_min is around
    // the volcano and the elevation f_min is given by the maximum of h along
    // the boundary y = 0 and 0 <= x <= 1600 (or x = 0 and 0 <= y <= 1600). Let
    // (x1, y1) denote this point, h(x1,y1) = f_min.
    //
    // The shortest path consists of a straight line tangential to the volcano
    // at elevation f_min, a curved segment of the contour line at elevation
    // f_min, and again a straight tangential line. We compute this shortest
    // path from the point (x1, y1) to the starting point (x0, y0) by following
    // the contour line until the point (x0, y0) becomes "in sight". Similar
    // for the shortest path from the point (x1, y1) to the end point (x2, y2).

    const double tol_x1    = 1E-9;
    const double tol_angle = 1E-4;
    const double size      = 1E-0;

    const double x0 =  200;
    const double y0 =  200;
    const double x2 = 1400;
    const double y2 = 1400;

    double x1 = maximize( 0, 1600, tol_x1);
    double y1 = 0;
    double f_min = f( x1, y1);

    double l1 = find_path( x1, y1, x0, y0, f_min, tol_angle, size);
    double l2 = find_path( x1, y1, x2, y2, f_min, tol_angle, size);
    double length = round( (l1+l2) * 1000.0) / 1000.0;

    std::cout << std::fixed << std::setprecision( 3) << length << std::endl;
    check( length == 2531.205);
    return EXIT_SUCCESS;
}