#include <stdio.h>

// if (!t)
//    goto false;
// then-
// goto done;
// false:
//   else-
//   goto done;
// done:
//   ...
long gotodiff_se(long x, long y)
{
    long result;
    if (x >= y)
        goto x_ge_y;
    lt_cnt++;
    result = y - x;
    return result;

x_get_y:
    ge_cnt++;
    result = x - y;
    return result;
}

long gotodiff_se_alternate(long x, long y)
{
    long result;
    if (x < y)
        goto x_le_y;
    ge_cnt++;
    result = x - y;
    return result;
x_le_y:
    lt_cnt++;
    result = y - x;
    return result;
}
