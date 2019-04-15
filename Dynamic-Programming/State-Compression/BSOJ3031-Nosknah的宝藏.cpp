#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<deque>
using namespace std;
typedef long long LL;
const LL inf=1LL<<60;
LL n,m,P,a[15];
LL f[205][5005],map[205][205],Ans=inf;
 
void Init()
{
  LL z,x,y,h;	
  
  cin>>n>>m;
  for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)map[i][j]=inf;  
 
  for(int i=1;i<=m;i++)
  {
    cin>>x>>y>>z;
    map[x][y]=map[y][x]=min(map[x][y],z);
  }
  
  cin>>P;
  h=1<<P;
  for(int i=0;i<=n;i++)
    for(int j=0;j<=h;j++)f[i][j]=inf;
  
  for(int i=1;i<=P;i++)cin>>a[i]; 
}
 
void Floyed()
{ 
  for(int k=1;k<=n;k++)
  {  
    map[k][k]=0;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      if(i!=j&&map[i][j]>map[i][k]+map[k][j])
       map[i][j]=map[i][k]+map[k][j];
  }   
}
 
int Check()
{
  if(map[1][n]==inf)return 0;
  
  for(int i=1;i<=P;i++)
   for(int j=1;j<=n;j++)
    if(map[a[i]][j]==inf)return 0;
 
  return 1;
}

void Dfs(LL x,LL dis,LL A)
{
  if(f[x][A]>dis)f[x][A]=dis;
  else return;
  
  if(A==((1<<P)-1))
  {
    Ans=min(Ans,dis+map[x][n]);
    return;
  }
  
  for(int i=1;i<=P;i++)
   if(!(A&(1<<(i-1))))
    Dfs(a[i],dis+map[x][a[i]],A|(1<<(i-1)));
}
 
int main()
{  
  Init();
  Floyed();
  if(Check())
  {  
    Dfs(1,0,0);
    cout<<Ans<<endl;
  }
  else printf("-1\n"); 
  return 0; 
}