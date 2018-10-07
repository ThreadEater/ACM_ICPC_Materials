// https://open.kattis.com/problems/fruitslicer

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

const double PI = acos(-1);

using namespace std;

int n;
double x[100];
double y[100];

pair<int, double> test(double rot) {
    int result = 0;

    multiset<pair<double, bool>> range;

    for (int i = 0; i < n; ++i) {
        range.insert({x[i] * sin(rot) - y[i] * cos(rot) - 1.000001, false});
        range.insert({x[i] * sin(rot) - y[i] * cos(rot) + 1.000001, true});
    }

    int current = 0;

    for (const pair<double, bool> &i: range) {
        if (!i.second) {
            current += 1;
        } else {
            current -= 1;
        }

        result = max(result, current);
    }

    return {result, rot};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    pair<int, double> best {0, 0};

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            best = max(best, test(atan2(y[j] - y[i], x[j] - x[i])));
        }
    }

    for (double rot = 0; rot < PI; rot += 1e-2) {
        best = max(best, test(rot));
    }

    for (double delta = 1e-2; delta >= 1e-8; delta *= 0.5) {
        best = max(best, test(best.second + delta));
        best = max(best, test(best.second - delta));
    }

    cout << best.first << endl;

    return 0;
}
