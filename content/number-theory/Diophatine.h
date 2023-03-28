/**
 * Author: BForBruteForce
 * Date: 2023-3-28
 * License: CC0
 * Description: Solution to diophatine equation $ax+by=c$
 * Time: $O(log(MAX))$
 * Status: Not tested
 */
#pragma once

#include "euclid.h"

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    if (c % g) {
        return false;
    }
    g = euclid(abs(a), abs(b), x0, y0);
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
