#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<deque>
using namespace std;

const int inf=0x7fffffff/2;
int n,m;
int a[2005],b[2005],f[2005][2005]; 
  
int main()
{ 
    scanf("%d%d",&n, &m);
    for(int i=1; i<=n; i++)scanf("%d",&a[i]), a[i]--;
    for(int i=1; i<=m; i++)scanf("%d",&b[i]), b[i]--;
 
    for(int i=0; i<=n; i++)           	
        for(int j=0; j<=m; j++)f[i][j]=inf;
    
    f[0][0]=0;
 
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            f[i][j]=min(f[i-1][j-1],min(f[i][j-1],f[i-1][j]))+a[i]*b[j];
    
    printf("%d\n",f[n][m]); 
    return 0;
} 