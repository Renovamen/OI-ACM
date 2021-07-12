#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int M = 50005;

struct node {
    long long a, b;
} L[M], Land[M];

long long f[M], q[M * 2];
int n, N;

bool cmp(node x, node y) {
    return x.a < y.a;
}

double Slope(int x, int y) {
    return (double(f[y] - f[x]) / double(Land[x + 1].b - Land[y + 1].b));
}

void Init() {
    scanf("%lld", &N);
    for(int i = 1; i <= N; i++) scanf("%d%d", &L[i].a, &L[i].b);
    sort(L + 1, L + N + 1, cmp);
    for(int i = 1; i <= N; i++) {
        while(n && Land[n].b <= L[i].b) n--;
        Land[++n] = L[i];
    }
}

void Dp() {
    int L = 1, R = 1, j;
    for(int i = 1; i <= n; i++) {
        while(L < R && Slope(q[L], q[L+1]) < Land[i].a) L++;
        j = q[L];
        f[i] = f[j] + (Land[j + 1].b) * (Land[i].a);
        while(L < R && Slope(q[R - 1], q[R]) > Slope(q[R], i)) R--;
        q[++R] = i;
    }
    printf("%lld\n", f[n]);
}

int main() {
    Init();
    Dp();
    return 0;
}
