#include "bits/stdc++.h"

using namespace std;

template<class T>
bool ckmax(T &a, const T &b) {
    if (b > a) {
        a = b;
        return true;
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto &x: s) cin >> x;
    vector dp(n, vector<vector<vector<int>>>(n));
    for (int i = 0; i < n; ++i) {
        string &str = s[i];
        int sz = str.size();
        dp[i][i].resize(sz, vector<int>(sz, 0));
        for (int lq = 0; lq < sz; ++lq) {
            for (int rq = lq; rq < sz; ++rq) {
                string sub = str.substr(lq, rq - lq + 1);
                string rsub = sub;
                reverse(rsub.begin(), rsub.end());
                if (sub == rsub) {
                    dp[i][i][lq][rq] = rq - lq + 1;
                }
            }
        }
        for (int rq = 0; rq < sz; ++rq) {
            int value = 0;
            for (int lq = rq; lq >= 0; --lq) {
                ckmax(value, dp[i][i][lq][rq]);
            }
            dp[i][i][0][rq] = value;
        }
        for (int lq = 0; lq < sz; ++lq) {
            int value = 0;
            for (int rq = lq; rq < sz; ++rq) {
                ckmax(value, dp[i][i][lq][rq]);
            }
            dp[i][i][lq].back() = value;
        }
        int value = 0;
        for (int lq = 0; lq < sz; ++lq) for (int rq = lq; rq < sz; ++rq) ckmax(value, dp[i][i][lq][rq]);
        dp[i][i][0][sz - 1] = value;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dp[i][j].resize(s[i].size(), vector<int>(s[j].size()));
        }
    }
    function<int(int, int, int, int)> calc = [&](int l, int lq, int r, int rq) {
        if (lq == s[l].size()) {
            l++;
            lq = 0;
        }
        if (rq == -1) {
            r--;
            rq = (int) s[r].size() - 1;
        }
        if (l > r) {
            assert(lq == 0 && rq == s[r].size() - 1 && r + 1 == l);
            return 0;
        }
        if (l == r || dp[l][r][lq][rq]) return dp[l][r][lq][rq];
        assert(l < r);
        if (s[l][lq] == s[r][rq]) ckmax(dp[l][r][lq][rq], calc(l, lq + 1, r, rq - 1) + 2);
        if (lq == 0) {
            for (int j = 1; j <= s[l].size(); ++j) ckmax(dp[l][r][lq][rq], calc(l, j, r, rq));
        }
        if (rq == (int) s[r].size() - 1) {
            for (int j = rq - 1; j >= -1; --j) ckmax(dp[l][r][lq][rq], calc(l, lq, r, j));
        }
        ckmax(dp[l][r][lq][rq], calc(l + 1, 0, r, rq));
        ckmax(dp[l][r][lq][rq], calc(l, lq, r - 1, s[r - 1].size() - 1));
        return dp[l][r][lq][rq];
    };
    cout << calc(0, 0, n - 1, s[n - 1].size() - 1) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(15) << fixed;
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
