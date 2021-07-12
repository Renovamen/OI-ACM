#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

const int M = 50005;

struct WE_ARE {
    int St, Ed, Sta;
} q[M];

struct THE_WORLD {
    ll a, b;
} L[M], Land[M];

ll n, N, f[M];

bool cmp(THE_WORLD x, THE_WORLD y) {
    return x.a < y.a;
}

ll Cal(int i, int j) {
    return f[j] + Land[i].b * Land[j+1].a;
}

int BiSearch(int l, int r, int t, int x) {
    int L = l, R = r, Mid;
    while(L < R) {
        Mid = (L + R) >> 1;
        if (Cal(Mid,t) >= Cal(Mid,x)) R = Mid;
        else L = Mid + 1;
    }
    if(L == r && Cal(L,x) > Cal(L,t)) return L + 1;
    return L;
}

void Dp() {
    int L = 1, R = 1;
    q[1].Sta = 0, q[1].St = 1, q[1].Ed = n;

    for(int i = 1; i <= n; i++) {
        while (L < R && q[L].Ed < i) L++;
        f[i] = Cal(i, q[L].Sta);
        while (L <= R && Cal(q[R].St, i) <= Cal(q[R].St, q[R].Sta)) R--;

        if(L <= R) {
            int w = BiSearch(q[R].St, q[R].Ed, q[R].Sta, i);
            if(w <= n) {
                if(w > q[R].St) {
                    q[R].Ed = w - 1;
                    q[++R].St = w;
                    q[R].Ed = n;
                }
                q[R].Sta = i;
            }
        }
        else q[++R].St = i + 1, q[R].Ed = n, q[R].Sta = i;
    }
    printf("%lld\n", f[n]);
}

void Init() {
    scanf("%lld", &N);
    for(int i = 1; i <= N; i++) scanf("%d%d", &L[i].a, &L[i].b);
    sort(L + 1, L + N + 1, cmp);
    for(int i = N; i >= 1; i--)
    if(L[i].b > Land[n].b) {
        Land[++n].b = L[i].b;
        Land[n].a = L[i].a;
    }
}

int main() {
    Init();
    Dp();
    return 0;
}
