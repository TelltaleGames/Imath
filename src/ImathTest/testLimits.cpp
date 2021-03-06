//
// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenEXR Project.
//

#ifdef NDEBUG
#    undef NDEBUG
#endif

#include "halfLimits.h"
#include "ImathHalfLimits.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <testLimits.h>

using namespace std;

namespace
{

float
mypow (int x, int y)
{
    bool negative = false;

    if (y < 0)
    {
        negative = true;
        y        = -y;
    }

    float z = 1;

    while (y > 0)
    {
        z *= x;
        y -= 1;
    }

    if (negative)
        z = 1 / z;

    return z;
}

} // namespace

void
testLimits()
{
    cout << "values in std::numeric_limits<half>\n";

    cout << "min_exponent\n";

    {
        half h (mypow (2, numeric_limits<half>::min_exponent - 1));
        assert (h.isNormalized());
    }

    {
        half h (mypow (2, numeric_limits<half>::min_exponent - 2));
        assert (h.isDenormalized());
    }

    cout << "max_exponent\n";

    {
        half h (mypow (2, numeric_limits<half>::max_exponent - 1));
        assert (h.isNormalized());
    }

    {
        half h (mypow (2, numeric_limits<half>::max_exponent));
        assert (h.isInfinity());
    }

    cout << "min_exponent10\n";

    {
        half h (mypow (10, numeric_limits<half>::min_exponent10));
        assert (h.isNormalized());
    }

    {
        half h (mypow (10, numeric_limits<half>::min_exponent10 - 1));
        assert (h.isDenormalized());
    }

    cout << "max_exponent10\n";

    {
        half h (mypow (10, numeric_limits<half>::max_exponent10));
        assert (h.isNormalized());
    }

    {
        half h (mypow (10, numeric_limits<half>::max_exponent10 + 1));
        assert (h.isInfinity());
    }

#if __cplusplus >= 201103L

    cout << "max_digits10\n";
    assert (numeric_limits<half>::max_digits10 ==
            std::ceil (numeric_limits<half>::digits * std::log10 (2) + 1));

    cout << "lowest\n";
    assert (numeric_limits<half>::lowest() == -HALF_MAX);

#endif

    cout << "ok\n\n" << flush;
}

void
testHalfLimits()
{
    cout << "values in Imath::limits<half>\n";
    
    assert (Imath::limits<half>::min() == float (-HALF_MAX)); 
    assert (Imath::limits<half>::max() == float (HALF_MAX));
    assert (Imath::limits<half>::smallest() == float (HALF_MIN));
    assert (Imath::limits<half>::epsilon() == float (HALF_EPSILON));
    assert (Imath::limits<half>::isIntegral() == false);
    assert (Imath::limits<half>::isSigned() == true);

    cout << "ok\n\n" << flush;
}
