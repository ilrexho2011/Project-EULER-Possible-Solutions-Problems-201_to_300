#include <iostream>
#include <cmath>
#include <chrono>
#include <algorithm>

const long double PI = 3.14159265358979323846;

struct IntegerPoint
{
    long long x, y;
    void Print() const {
        std::cout << '(' << x << ',' << y << ')';
    }
};

struct FloatPoint
{
    long double x, y;
    void Print() const {
        std::cout << '(' << x << ',' << y << ')';
    }
};

class Circle {
private:
public:
    IntegerPoint m;
    int r;
    Circle(const IntegerPoint& mIn, const int& rIn) {
        m = mIn; r = rIn;
    };
private:
};

/*  This class is only for laying ellipses*/
class Ellipse {
private:
    // For standard ellipse equation form ( x / a^2 + y / b^2 = 1) where j = a, k = b and l = c
    long long j, l;
    double k,multiplier;
    // Center of the ellipse.
    IntegerPoint m;
    // For conic section equation form (ax^2 + by^2 + cx + dy + e = 0)
    long long a, b, c, d, e;
public:
    Ellipse(const Circle& circle, const IntegerPoint& f1In, const IntegerPoint& f2In) {
        l = abs(f1In.x - f2In.x) / 2;
        m.x = circle.m.x + l;
        m.y = circle.m.y;
        j = (circle.r + circle.m.x + std::max(f1In.x, f2In.x)) / 2 - m.x;
        k = sqrt(-l * l + j * j);
        multiplier = 0.0001;

        a = pow(k, 2) * multiplier;
        b = pow(j, 2) * multiplier;
        c = -2 * pow(k, 2) * m.x * multiplier;
        d = (-2 * pow(j, 2) * m.y) * multiplier;
        e = (pow(j, 2) * pow(k, 2) - pow(j, 2) * pow(m.y, 2) - pow(k, 2) * pow(m.x, 2)) * -multiplier;
    };

    /*  This gets the solution  */
    long AmountOfPoints() const {
        int flipDistance;
        // Part of my problem, angle of anything on y = m.y is a devide by zero error
        IntegerPoint test = { -15000, m.y + 1 };
        // First it goes from left to right till it find an angle that is 45 degrees
        for (long double i = -15000; i < -j; i++) {
            test.x = i;
            if (Angle(test) >= 45) {
                flipDistance = -test.x - j + m.x;
                break;
            }
        }
        long total = 1;
        // Now it goes from this position and it follows the outer boundary curve for the top
        // , adding up the distance for every new X position
        while (test.x <= m.x) {
            test.x += 1;
            while (Angle(test) > 45) test.y += 1;
            int distance = LatticeVerticalDistance(test);
            total += distance;
        }
        while (test.y > m.y) {
            test.x += 1;
            while (Angle(test) < 45) test.y -= 1;
            int distance = LatticeVerticalDistance(test);
            total += distance;
        }
        total += flipDistance;
        // Total times 2 because only the top half was checked
        return total * 2;
    };

    void PrintParameters() const {
        std::cout << "\nEllipse equation: (x - " << m.x << ")^2 / " << pow(j, 2) << " + (y - " << m.y << ")^2 / " << pow(k, 2) << " = 1\n";
        std::cout << "Conic section: " << a << "x^2 + " << b << "y^2 + " << c << "x + " << d << "y + " << e << " = 0\n";
        std::cout << "Center = "; m.Print(); std::cout << '\n';
        // For the general ellipse equation
        std::cout << "a = " << j << '\n';
        std::cout << "b = " << k << '\n';
        std::cout << "c = " << l << '\n';
    };
private:
    /*  This function gets the angle between the two tangents of the ellipse in a point outside of the ellipse*/
    double Angle(const IntegerPoint& in) const {
        FloatPoint intersect1, intersect2;
        // fx + gy = h
        const double f = a * in.x + 0.5 * c;
        const double g = b * in.y + 0.5 * d;
        const double h = -0.5 * c * in.x - 0.5 * d * in.y - e;
        // Wolfram Alpha gigachad (I tried solving manually but my formula was stupidly large)
        // I currently have a,b,c,d and e baked in, also to reduce the formula length. 
        const double c1 = 18 * h * f + 30000 * g * g - 27000 * f * g;
        const double c2 = sqrt(5220000000 * pow(g, 4.0) + 540000 * h * pow(g, 3.0) - 1620000000 * f * pow(g, 3.0) - 180 * h * h * g * g + 8505000000 * f * f * g * g + 1080000 * h * f * g * g);
        const double c3 = 2 * (9 * f * f + 5 * g * g);
        intersect1.x = (c1 + c2) / c3;
        intersect2.x = (c1 - c2) / c3;
        intersect1.y = (h - f * intersect1.x) / g;
        intersect2.y = (h - f * intersect2.x) / g;
        // Now calculate the tangents of the polar line intersections
        const double tangent1 = atan(((-2 * a * intersect1.x) - c) / ((2 * b * intersect1.y) + d));
        const double tangent2 = atan(((-2 * a * intersect2.x) - c) / ((2 * b * intersect2.y) + d));
        // Calculate the angle between the tangents
        double angle = ((std::max(tangent1, tangent2) - std::min(tangent1, tangent2)) * 180) / PI;
        if (angle > 90) angle = 180 - angle;
        return angle;
    };

    /*  This calculates the vertical distance between the ellipse (or the y of the center of the ellipse) and the input point*/
    int LatticeVerticalDistance(const IntegerPoint& in) const {
        int distance = 0;
        if (in.x < m.x - j || in.x > m.x + j) distance = (in.y - m.y);
        else {
            const double boundary = (-d + sqrt(pow(d, 2.0) - 4 * b * (a * in.x * in.x + c * in.x + e))) / (2 * b);
            distance = in.y - ceil(boundary);
        }
        return distance;
    }
};

int main()
{
    IntegerPoint M = { -2000, 1500 };
    IntegerPoint G = { 8000, 1500 };
    const double r = 15000;
    Circle c(M, r);
    Ellipse e(c, G, M);
    auto start = std::chrono::high_resolution_clock::now();
    const long points = e.AmountOfPoints();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Your answer is " << 100 - (100.0 * points) / 810834388 << "% off.\n";
    std::cout << "It was: " << points << '\n';
    std::cout << "It took " << diff.count() << " seconds to find.\n";
    e.PrintParameters();
    system("pause");
}