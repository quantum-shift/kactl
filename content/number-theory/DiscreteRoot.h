/**
 * Author: BForBruteForce
 * Date: 2023-3-28
 * License: CC0
 * Description: Given a number $n$ and 2 integers $a$ and $k$, find all $x$ for which : $x^k = a$ (mod n).
 * Time: $O(sqrt(n) logn)$
 * Status: Not tested
 */
#pragma once

#include "PrimitiveRoot.h"
#include "ModLog.h"

vector<int> discreteRoots (int n, int k, int a) {
    if(!a) return {0};
    int g = generator(n);
    int x = modpow(g,k,n);
    int y = modLog(x,a,n);
    if(y == -1) return {};
    int del = (n-1) / gcd(k, n-1);
    vector<int> ans;
    for (int cur = y % del; cur < n-1; cur += del)
        ans.push_back(modpow(g, cur, n));
    return ans;
}