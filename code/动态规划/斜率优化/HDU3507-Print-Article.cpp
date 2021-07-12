#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int Maxn = 500005;
int f[Maxn], q[Maxn], Sum[Maxn];
int N, M;

// 斜率分子
int Slope_Up(int j,int k) {
    return f[j] + Sum[j] * Sum[j] - (f[k] + Sum[k] * Sum[k]);
}

// 斜率分母
int Slope_Down(int j,int k) {
    return Sum[j] - Sum[k];
}

void DP() {
    int L = 0, R = 0;

    q[R++] = 0;
    f[0] = 0;

    for(int i=1; i<=N; i++) {
        while(L + 1 < R && Slope_Up(q[L+1], q[L]) <= 2 * Sum[i] * Slope_Down(q[L+1], q[L]))L++;
        int j = q[L];

        f[i] = f[j] + (Sum[i]-Sum[j]) * (Sum[i]-Sum[j]) + M;

        while(L + 1 < R && Slope_Up(i, q[R-1]) * Slope_Down(q[R-1], q[R-2]) <= Slope_Up(q[R-1], q[R-2]) * Slope_Down(i, q[R-1]))R--;
        q[R++] = i;
    }
    cout << f[N] << endl;
}

int main() {
    while(~scanf("%d%d", &N, &M)) {
        Sum[0] = 0;
        for(int i=1; i<=N; i++) {
            int x;
            cin >> x;
            Sum[i] = Sum[i-1] + x;
        }
        DP();
    }
    return 0;
}
