#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;
const int M=1000005;
ll Dis[M],Cost[M],Sum[M],Sumd[M],f[M],q[M];
int n;
 
void Init()
{  
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {  
    scanf("%lld%lld%lld",&Dis[i],&Sum[i],&Cost[i]);
    Sum[i]+=Sum[i-1];
    Sumd[i]=Sumd[i-1]+Sum[i-1]*(Dis[i]-Dis[i-1]);
  }
}
 
double Slope(int i,int j)
{
  return double((f[i]-Sumd[i]+Sum[i]*Dis[i])-(f[j]-Sumd[j]+Sum[j]*Dis[j]))/(Sum[i]-Sum[j]);
}
 
void Dp()
{
  int L=1,R=1;
  for(int i=1;i<=n;i++)  
  {
    while(L<R&&Slope(q[L],q[L+1])<Dis[i])L++;
    int j=q[L];
    f[i]=f[j]+Sumd[i]-Sumd[j]-Sum[j]*(Dis[i]-Dis[j])+Cost[i];
    while(L<R&&Slope(q[R-1],q[R])>Slope(q[R],i))R--;
    q[++R]=i;
  } 
  printf("%lld\n",f[n]);
}
 
int main()
{
  Init(); 
  Dp(); 
  return 0;
}