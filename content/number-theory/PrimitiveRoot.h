/**
 * Author: BForBruteForce
 * Date: 2023-3-28
 * License: CC0
 * Description: To find an integer $g$ such that for any integer $a$ such that $\gcd(a,n)=1$, there exists an integer $k$ such that $g^k=a$ (mod n). 
 * This works only if $p$ (in the code) is prime. To make it work for non-prime, add code for calculating $phi$.
 * Time: $O(Ans \cdot \log(n) \cdot \log(\phi(n)))$
 * Status: Not tested
 */
#pragma once

#include "ModMulLL.h"

int generator (int p) {
    vector<int> fact;
    int phi = p-1, n = phi; // calculate phi for non-prime 'p'
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1) fact.push_back (n);
    rep(r,2,p+1) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= modpow (r, phi / fact[i], p) != 1;
        if (ok)  return r;  
    }
    return -1;
}