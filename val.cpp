#include "testlib.h"
#include "bits/stdc++.h"

using namespace std;

constexpr int S = 500'000;
constexpr int N = 100'000;

const int MAX_TESTS = 14;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int tests = inf.readInt(1, MAX_TESTS, "t");
    inf.readEoln();

    for (int test_index = 1; test_index <= tests; test_index++) {
        setTestCase(test_index);

        int n = inf.readInt(1, N, "n");
        inf.readEoln();

        int L = 0;
        for (int i = 0; i < n; ++i) {
		    auto s = inf.readToken("[a-z]{1," + to_string(S) + "}", "s_i");
            inf.readEoln();
            L += s.size();
            ensuref(L <= S, "Sum of lens is too big");
        }
    }
    inf.readEof();
    return 0;
}
