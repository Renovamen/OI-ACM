#include<cstdio>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;
const ll Mod = 100000000000000000LL;
ll f[505][130][130];
int a[205];
int n, c1, c2, c3;
 
void Dp()
{
  f[0][0][0] = 1;
  for(int k = 1; k <= n; k++)
  {
    for(int x = 0; x <= c1; x++)
     for(int y = 0; y <= c2; y++)
     {
       for(int i = 0; i <= min(x, a[k]); i++)
        for(int j = 0; j <= min(y, a[k]-i); j++)
         f[k][x][y] = (f[k][x][y] + f[k-1][x-i][y-j]) % Mod;
     }
   }
   printf("%lld\n", f[n][c1][c2]);
}
 
int main()
{
  scanf("%d", &n);
  scanf("%d%d%d", &c1, &c2, &c3);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
  Dp();
  return 0;
}