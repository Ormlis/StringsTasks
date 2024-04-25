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
    vector dpL(n, vector<vector<int>>(n));
    vector dpR(n, vector<vector<int>>(n));
    for (int i = 0; i < n; ++i) {
        string &str = s[i];
        int sz = str.size();
        dpL[i][i].resize(sz);
        dpR[i][i].resize(sz);
        for (int lq = 0; lq < sz; ++lq) {
            for (int rq = lq; rq < sz; ++rq) {
                bool ok = true;
                for (int t = 0; t <= rq - lq && ok; ++t) ok &= (str[lq + t] == str[rq - t]);
                if (ok) {
                    ckmax(dpR[i][i][rq], rq - lq + 1);
                    ckmax(dpL[i][i][lq], rq - lq + 1);
                }
            }
        }
        int mx = *max_element(dpL[i][i].begin(), dpL[i][i].end());
        dpL[i][i][0] = dpR[i][i][sz - 1] = mx;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dpL[i][j].resize(s[i].size());
            dpR[i][j].resize(s[j].size());
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
        assert(lq == 0 || rq == s[r].size() - 1);
        int &value = (lq == 0 ? dpR[l][r][rq] : dpL[l][r][lq]);
        if (value) return value;
        assert(l < r);
        ckmax(value, calc(l + 1, 0, r, rq));
        ckmax(value, calc(l, lq, r - 1, s[r - 1].size() - 1));
        if (lq == 0 && rq == s[r].size() - 1) {
            for (int j = 1; j <= s[l].size(); ++j) {
                ckmax(value, calc(l, j, r, rq));
            }
            for (int j = rq - 1; j >= -1; --j) {
                ckmax(value, calc(l, lq, r, j));
            }
            for (int t = 1; t <= s[l].size() && t <= s[r].size() && s[l][t - 1] == s[r][s[r].size() - t]; ++t) {
                ckmax(value,
                      t * 2 + max(calc(l, t, r - 1, s[r - 1].size() - 1), calc(l + 1, 0, r, rq - t)));
            }
        } else if (lq == 0) {
            for (int lq2 = 0; lq2 < s[l].size(); lq2++) {
                for (int t = 1; lq2 + t <= s[l].size() && rq - t >= -1 && s[l][lq2 + t - 1] == s[r][rq - t + 1]; ++t) {
                    ckmax(value,
                          t * 2 + max(calc(l, lq2 + t, r - 1, s[r - 1].size() - 1), calc(l + 1, 0, r, rq - t)));
                }
            }
        } else {
            for (int rq2 = rq; rq2 >= 0; --rq2) {
                for (int t = 1; lq + t <= s[l].size() && rq2 - t >= -1 && s[l][lq + t - 1] == s[r][rq2 - t + 1]; ++t) {
                    ckmax(value,
                          t * 2 + max(calc(l, lq + t, r - 1, s[r - 1].size() - 1), calc(l + 1, 0, r, rq2 - t)));
                }
            }
        }
        return value;
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
