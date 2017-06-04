#ifndef DXMATH_H
#define DXMATH_H

#include <QtMath>
#include <math.h>
#include <stdlib.h>

class DxMath
{
public:
    DxMath(){};
    ~DxMath(){};

public:
    static inline double CompareDouble(double a, double b, double accuracy)
    {
        if(abs(a - b) < accuracy)
        {
            return 0;
        }
        else
        {
            return (a > b) ? 1 : -1;
        }
    }

    static inline bool DoubleEqual(double a, double b) { return DoubleEqual(a, b, kAccuracy); }

    static inline bool DoubleEqual(double a, double b, double accuracy)
    {
        return CompareDouble(a, b, accuracy) == 0 ? true : false;
    }

    static inline bool DoubleNotEqual(double a, double b)
    {
        return DoubleNotEqual(a, b, kAccuracy);
    }

    static inline bool DoubleNotEqual(double a, double b, double accuracy)
    {
        return !DoubleEqual(a, b, accuracy);
    }
    // Calculate the determinan of a 2x2 matrix in the form of
    // | a b |
    // | c d |
    static inline double Determinant2x2(double a, double b, double c, double d)
    {
        return (a * d - b * c);
    }

    // Calculate the determinant of a 3x3 matrix in the form of
    //   | a1, b1, c1 |
    //   | a2, b2, c2 |
    //   | a3, b3, c3 |
    static inline double
    Determinant3x3(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3)
    {
        return (a1 * DxMath::Determinant2x2(b2, b3, c2, c3) - b1 * DxMath::Determinant2x2(a2, a3, c2, c3) +
                c1 * DxMath::Determinant2x2(a2, a3, b2, b3));
    }

    // Calculate the determinant of a 4x4 matrix in the form of
    // | a1, b1, c1, d1 |
    // | a2, b2, c2, d2 |
    // | a3, b3, c3, d3 |
    // | a4, b4, c4, d4 |
    static inline double Determinant4x4(double a1,
                                        double a2,
                                        double a3,
                                        double a4,
                                        double b1,
                                        double b2,
                                        double b3,
                                        double b4,
                                        double c1,
                                        double c2,
                                        double c3,
                                        double c4,
                                        double d1,
                                        double d2,
                                        double d3,
                                        double d4)
    {
        return (a1 * DxMath::Determinant3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4) -
                b1 * DxMath::Determinant3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4) +
                c1 * DxMath::Determinant3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4) -
                d1 * DxMath::Determinant3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4));
    }

    static double AngleToRadian(double angle) { return angle / 180 * M_PI; }

private:
    static const double kAccuracy;
};

#endif
