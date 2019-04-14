#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int M=20005;
int f[M],Sw[M],Sd[M],Cost[M],q[M],w[M],d[M];
//Cost[i]:把第一锯木场设在第i棵树的位置上,1~i棵树到i所需的费用
//Sw[i]:1~i棵树的总重量,Sd[i]:1~i棵树的距离 
//F[i]:第二个锯木厂设在i处所需的总费用
int n,Ans=1<<30;
 
double Slope(int x,int y)
{  
  return (double(Sw[x]*Sd[x]-Sw[y]*Sd[y])/double(Sw[x]-Sw[y]));
}
 
void Init()  
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
    scanf("%d%d",&w[i],&d[i]);
    Sd[i]=Sd[i-1]+d[i-1];
    Sw[i]=Sw[i-1]+w[i]; 
  }
  Sd[n+1]=Sd[n]+d[n],Sw[n+1]=Sw[n];
  for(int i=1;i<=n+1;i++)Cost[i]=Cost[i-1]+Sw[i-1]*d[i-1];  
}

void Dp()
{
  int L=1,R=1,j;
  for(int i=1;i<=n;i++)
  {
    while(Slope(q[L],q[L+1])<Sd[i]&&L<R)L++;
    j=q[L];
    f[i]=Cost[n+1]-Sw[j]*(Sd[i]-Sd[j])-Sw[i]*(Sd[n+1]-Sd[i]);
    /*
      W[i,j]:把第i~j棵木头都运送到第j棵树的位置上所需要的费用
      W[i][j]=Cost[j]-Cost[i-1]-Sw[i-1]*(Sd[j]-Sd[i-1])
	  
      f[i]=Cost[j]+W[j+1][i]+W[i+1][n+1]
	      =Cost[j]+Cost[i]-Cost[j]-Sw[j]*(Sd[i]-Sd[j])-Cost[n+1]-Cost[i]-Sw[i]*(Sd[n+1]-Sd[i])
	      =Cost[n+1]-Sw[j]*(Sd[i]-Sd[j])-Sw[i]*(Sd[n+1]-Sd[i])
    */
    while(Slope(q[R-1],q[R])>Slope(q[R],i)&&R>L)R--;
    q[++R]=i;
    Ans=min(Ans,f[i]);
  }
  printf("%d\n",Ans);
}
  
int main()
{ 
  Init();
  Dp();
  return 0;
} 