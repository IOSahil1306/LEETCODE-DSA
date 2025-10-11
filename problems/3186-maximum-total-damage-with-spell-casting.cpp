// #include <bits/stdc++.h>
// using namespace std;

// class Solution {
// public:
//     long long maximumTotalDamage(vector<int>& power) {
//         int n = (int)power.size();
//         long long best = 0;

//         for (int i = 0; i < n; ++i) {
//             long long sum = power[i];
//             vector<int> chosen(n, 0);
//             chosen[i] = 1;

//             for (int j = 0; j < n; ++j) {
//                 if (chosen[j]) continue;
//                 bool ok = true;
//                 // check against all already chosen spells
//                 for (int k = 0; k < n; ++k) {
//                     if (!chosen[k]) continue;
//                     int diff = abs(power[j] - power[k]);
//                     if (diff == 1 || diff == 2) { ok = false; break; }
//                 }
//                 if (ok) {
//                     sum += power[j];
//                     chosen[j] = 1;
//                 }
//             }
//             best = max(best, sum);
//         }
//         return best;
//     }
// };
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        if (power.empty()) return 0;

        // 1) accumulate total damage per distinct value
        unordered_map<long long, long long> total;
        total.reserve(power.size()*2);
        for (int x : power) total[x] += x;

        // 2) get sorted distinct values
        vector<long long> vals;
        vals.reserve(total.size());
        for (auto &p : total) vals.push_back(p.first);
        sort(vals.begin(), vals.end());

        int m = (int)vals.size();
        if (m == 0) return 0;
        vector<long long> dp(m, 0);

        for (int i = 0; i < m; ++i) {
            // option: skip current value
            long long skip = (i >= 1) ? dp[i-1] : 0;

            // option: take all spells of this value
            long long take = total[vals[i]];

            // we can add dp[j] where vals[j] <= vals[i] - 3
            // find largest index j with vals[j] <= vals[i] - 3
            long long need = vals[i] - 3;
            int j = (int)(upper_bound(vals.begin(), vals.end(), need) - vals.begin()) - 1;
            if (j >= 0) take += dp[j];

            dp[i] = max(skip, take);
        }

        return dp[m-1];
    }
};
