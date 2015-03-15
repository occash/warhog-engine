#ifndef MATHLIB_H
#define MATHLIB_H

namespace Math
{
    template <typename T> inline
    int sign(T x)
    {
        return x == 0 ? 0 : x / abs(x);
    }
}
#endif