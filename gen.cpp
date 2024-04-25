#include "testlib.h"
#include "bits/stdc++.h"

using namespace std;


struct Test {
    map<string, string> params;

    long long get(string name, long long def = 0) {
        if (params.count(name)) {
            return stoll(params[name]);
        } else {
            return def;
        }
    }

    vector<string> s;
    int n;
    int slen;

    void thue_gen() {
        int lst = 1;
        int len = slen;
        while (len >= lst) {
            int x = rnd.next(0, 1);
            s.emplace_back(lst, 'a');
            for (int i = 0; i < lst; i++) {
                s.back()[i] = 'a' + (__builtin_popcount(i) + x) % 2;
            }
            len -= lst;
            lst *= 2;
        }

        n = s.size();
        slen -= len;
    }


    void random_gen() {
        auto lens = rnd.partition(n, slen);
        int alph = get("alph", 26);
        for (auto len: lens) {
            s.emplace_back(len, 'a');
            for (auto &x: s.back()) {
                x += rnd.next(alph);
            }
        }
    }

    void palindrome_gen() {
        string T(slen, 'a');
        int alph = get("alph", 26);
        for (auto &x: T) x += rnd.next(alph);
        for (int i = 0; i < T.size(); ++i) T[i] = T[(int) T.size() - 1 - i];
        auto lens = rnd.partition(n, slen);
        int left = 0;
        for (int i = 0; i < n; ++i) {
            s.emplace_back(T.substr(left, lens[i]));
            left += lens[i];
        }
    }

    void post_process() {
        int add_len = get("alen", 0);
        int alph = get("alph", 26);

        auto parts = rnd.partition(n * 2, add_len, 0);
        for (int i = 0; i < n; ++i) {
            string L, R;
            for (int it = 0; it < parts[i * 2]; ++it) {
                L += 'a' + rnd.next(alph);
            }
            for (int it = 0; it < parts[i * 2 + 1]; ++it) {
                R += 'a' + rnd.next(alph);
            }
            s[i] = L + s[i] + R;
        }

        if (params.count("shuffle")) {
            shuffle(s.begin(), s.end());
        }
    }

    void anime() {
        vector<string> anime = {
                "gintama",
                "tokyoghoul",
                "naruto",
                "frieren",
                "onepiece",
                "mob",
                "abyss",
                "aprillie",
                "deathnote"
        };
        s = anime;
        slen = 0;
        for (auto &x: s) {
            slen += x.size();
        }
        n = s.size();
    }

    void make() {
        n = get("n");
        slen = get("slen");

        string mode = params["mode"];
        if (mode == "random") {
            random_gen();
        } else if (mode == "pal") {
            palindrome_gen();
        } else if (mode == "thue") {
            thue_gen();
        } else if (mode == "anime") {
            anime();
        } else {
            assert(0);
        }

        post_process();
    }

    Test() : n(0), slen(0) {}
};

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int arg = 1;
    vector<Test> tests;
    while (arg < argc) {
        Test test;
        while (arg < argc) {
            string s = string(argv[arg++]);
            if (s == "T") {
                break;
            }
            if (s.find("=") != string::npos) {
                auto pos = s.find("=");
                test.params[s.substr(0, pos)] = s.substr(pos + 1);
            } else {
                test.params[s] = "";
            }
        }
        test.make();
        tests.push_back(test);
    }

    cout << tests.size() << '\n';
    for (auto &test: tests) {
        cout << test.n << '\n';
        for (auto &str: test.s) {
            cout << str << '\n';
        }
    }
    return 0;
}
