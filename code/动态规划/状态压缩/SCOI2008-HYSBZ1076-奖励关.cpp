#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <queue>
using namespace std;

int v[20], d[20], P[21];
double f[55][65536];
int n, k, t;

void Init() {
    scanf("%d%d", &k, &n);
    for(int i = 1; i <= n+1; i++) P[i] = 1 << (i - 1);

    int x;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        while(scanf("%d", &x)) {
            if(x == 0) break;
            d[i] += P[x];
        }
    }
}

void Dp() {
    for(int i = k; i; i--)
        for(int j = 0; j <= P[n + 1] - 1; j++) {
            f[i][j] = 0;

            for(int h = 1; h <= n; h++) {
                if ((d[h] & j) == d[h])
                    f[i][j] += max(f[i + 1][j], f[i + 1][j | P[h]] + v[h]);
                else f[i][j] += f[i + 1][j];
            }

            f[i][j] /= double(n);
        }
    printf("%.6lf", f[1][0]);
}

int main() {
  Init();
  Dp();
  return 0;
}
