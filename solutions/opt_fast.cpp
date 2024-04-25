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
        for (int mid = 0; mid < sz; ++mid) {
            {
                // even
                int t = 0;
                while (mid - t - 1 >= 0 && mid + t < sz && str[mid + t] == str[mid - 1 - t]) {
                    ckmax(dpR[i][i][mid + t], (t + 1) * 2);
                    ckmax(dpL[i][i][mid - 1 - t], (t + 1) * 2);
                    t++;
                }
            }
            {
                // odd
                int t = 0;
                while (mid - t >= 0 && mid + t < sz && str[mid + t] == str[mid - t]) {
                    ckmax(dpR[i][i][mid + t], t * 2 + 1);
                    ckmax(dpL[i][i][mid - t], t * 2 + 1);
                    t++;
                }
            }
        }
        int mx = *max_element(dpL[i][i].begin(), dpL[i][i].end());
        dpL[i][i][0] = dpR[i][i][sz - 1] = mx;
    }
    vector<vector<int>> tmp;
    for (int diff = 1; diff < n; ++diff) {
        for (int l = 0; l + diff < n; ++l) {
            int r = l + diff;
            dpL[l][r].resize(s[l].size());
            dpR[l][r].resize(s[r].size());
            tmp.assign(s[l].size() + 1, vector<int>(s[r].size() + 1, 0));
            {
                for (int j = 1; j <= s[r].size(); ++j) {
                    tmp[s[l].size()][j] = dpR[l + 1][r][j - 1];
                }
            }
            {
                for (int j = 0; j < s[l].size(); ++j) {
                    tmp[j][0] = dpL[l][r - 1][j];
                }
            }
            {
                tmp[s[l].size()][0] = (diff >= 2 ? dpL[l + 1][r - 1][0] : 0);
            }
            for (int lq = s[l].size() - 1; lq >= 0; --lq) {
                for (int rq = 0; rq < s[r].size(); ++rq) {
                    int &value = tmp[lq][rq + 1];
                    if (s[l][lq] == s[r][rq]) {
                        value = 2 + tmp[lq + 1][rq];
                    } else {
                        value = max(dpR[l + 1][r][rq], dpL[l][r - 1][lq]);
                    }
                }
            }
            for (int rq = 0; rq < s[r].size(); ++rq) {
                for (int lq = 0; lq < s[l].size(); ++lq) {
                    ckmax(dpR[l][r][rq], tmp[lq][rq + 1]);
                    ckmax(dpL[l][r][lq], tmp[lq][rq + 1]);
                }
            }
            int mx = 0;
            for(int rq = 0; rq < s[r].size(); ++rq) {
                ckmax(mx, dpR[l][r][rq]);
            }
            for(int lq = 0; lq < s[l].size(); ++lq) {
                ckmax(mx, dpL[l][r][lq]);
            }
            dpL[l][r][0] = dpR[l][r][s[r].size() - 1] = mx;
        }
        if (diff >= 2) {
            for (int l = 0; l + diff - 2 < n; ++l) {
                int r = l + diff - 2;
                dpL[l][r].clear();
                dpL[l][r].shrink_to_fit();
                dpR[l][r].clear();
                dpR[l][r].shrink_to_fit();
            }
        }
    }
    cout << dpL[0][n - 1][0] << '\n';
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