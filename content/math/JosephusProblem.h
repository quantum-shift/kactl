/**
 * Author: BForBruteForce
 * Date: 2023-3-28
 * License: CC0
 * Description: Josephus Problem solution
 * Time: $O(k logn)$
 * Status: Not tested
 */
#pragma once

int josephus(int n, int k) {
    if (n == 1)
        return 0;
    if (k == 1)
        return n-1;
    if (k > n)
        return (josephus(n-1, k) + k) % n;
    int cnt = n / k;
    int res = josephus(n - cnt, k);
    res -= n % k;
    if (res < 0)
        res += n;
    else
        res += res / (k - 1);
    return res;
}