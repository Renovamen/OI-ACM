#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int a[2005], s[2005], f[2005][2005];
int n, t;
 
void Dp()
{
  for(int l = 2; l <= n; l++)
   for(int i = 1; i <= n-l+1; i++)
   {
     int j = i+l-1;
     f[i][j] = max(a[i] + s[j] - s[i] - f[i+1][j], a[j] + s[j-1] - s[i-1] - f[i][j-1]);
   }
   
  if(t == 0) printf("%d\n",s[n] - f[1][n]);
  else printf("%d\n", f[1][n]); 
}
 
int main()
{	
  while(scanf("%d%d", &n, &t) != EOF)  
  {
    for(int i = 1; i <= n; i++)
    {
      scanf("%d", &a[i]);
      s[i] = s[i-1] + a[i];
      f[i][i] = a[i];
    }
    Dp();  
  }  
  return 0;
}