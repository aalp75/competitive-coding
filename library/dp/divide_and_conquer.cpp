#include <vector>

using namespace std;

const long long INF64 = 1e18 + 10;

/** 
 * Divide and conquer DP (Dynamic Programming)
 * 
 * To solve problems of the form:
 * 
 *      dp[j][i] = min(dp[j - 1][p] + C(p + 1, i)) for p in [0, i - 1]
 * 
 * where C is an O(1) function that respect the quadrangle inequality
 * (for example, convex function on R+ respect the condition)
 * 
 * if we define opt[j][i] as the p that minimizes dp[j][i], by the above condition
 * we have opt[j][i] <= opt[j][i + 1] so if we know opt[j][l] and opt[j][r] we can 
 * reduce the search space for all opt[j][i] with i in [l, r]
 * That leads to a divide and conquer algorithm
 *  
 * complexity:
 *      O(m * n * log(n)) with n the length of the array and m the number of groups
 * 
 * example of problem:
 *      find the best partition into exactly k subarrays giving the minimum 
 *      possible score. The score of a partition is the sum of the values of 
 *      all its subarrays and the value of a subarray is defined as the square 
 *      of the sum of its elements
 * 
 *      dp[j][i] = minimum score for j groups on the i-st elements
 * 
 *      answer: dp[k][n]
 * 
 * notes:
 *  - the memory can be reduced by replacing the dp 2d array by just 2 1d arrays prev and cur
 *  - in the below implementation, pref array is 1-indexed
 */

long long costDC(vector<long long>& pref, int start, int end) {
    long long s = pref[end] - pref[start - 1];
    return s * s; // be careful on overflow
}

void computeDC(int l, int r, int optL, int optR, int g,
               vector<vector<long long>>& dp, vector<long long>& pref) {

    if (l > r) return;

    int mid = (l + r) / 2;

    int bestIndex = -1;
    long long bestVal = INF64;

    for (int index = optL; index <= min(optR, mid - 1); index++) {
        long long val = dp[g - 1][index] + costDC(pref, index + 1, mid);
        if (val < bestVal) {
            bestVal = val;
            bestIndex = index;
        }
    }

    dp[g][mid] = bestVal;

    computeDC(l, mid - 1, optL, bestIndex, g, dp, pref);
    computeDC(mid + 1, r, bestIndex, optR, g, dp, pref);
}

long long dynamicProgrammingDC(vector<int> v, int k) {
    int n = v.size();

    vector<long long> pref(n + 1, 0); // prefix sum
    for (int i = 1; i <= n; i++) {
        pref[i] = v[i - 1] + pref[i - 1];
    }

    vector<vector<long long>> dp(k + 1, vector<long long> (n + 1, INF64));
    dp[0][0] = 0;

    for (int g = 1; g <= k; g++) {
        computeDC(g, n, g - 1, n - 1, g, dp, pref);
    }

    long long res = dp[k][n];
    return res;
}