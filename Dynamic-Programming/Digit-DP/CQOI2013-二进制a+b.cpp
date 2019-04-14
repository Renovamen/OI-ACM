#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;
const int inf=0x7fffffff;
int f[2][40][40][40][2];
int n,m,p,n1,m1,p1,L;
 
void Init()
{     
  scanf("%d%d%d",&n,&m,&p);     
  n1=0,m1=0,p1=0; 
  int Max=max(n,max(m,p));  
  
  while(n)
  {
    if(n&1)n1++;
    n>>=1; 
  }
  
  while(m)
  {
    if(m&1)m1++;
    m>>=1; 
  }
  
  while(p)
  {
    if(p&1)p1++;
    p>>=1; 
  }
  
  while(Max)
  {
    L++;
    Max>>=1;
  }
}
 
void Dp()
{         
  for(int t=0;t<=1;t++)         
   for(int i=0;i<=n1;i++)              
    for(int j=0;j<=m1;j++)                 
     for(int k=0;k<=p1;k++)                     
      for(int p=0;p<=1;p++)f[t][i][j][k][p]=inf;     
  int t=0;
  f[t][0][0][0][0]=0;     
  
  for(int l=1;l<=L;l++)     
  {         
    t=!t;         
    for(int i=0;i<=n1;i++)             
     for(int j=0;j<=m1;j++)                 
      for(int k=0;k<=p1;k++)                     
       for(int p=0;p<=1;p++)                        
        if(f[!t][i][j][k][p]!=inf)                         
        {                             
          for(int x=0;x<=1;x++)                                 
           for(int y=0;y<=1;y++)                                 
           {                                     
             int res=x+y+p;                                     
             f[t][i+x][j+y][k+(res&1)][res>>1] = min(f[t][i+x][j+y][k+(res&1)][res>>1], f[!t][i][j][k][p]+((res&1)<<(l-1)));                                 
           }                             
           f[!t][i][j][k][p]=inf;                         
        }     
  }     
  if(f[t][n1][m1][p1][0]!=inf)printf("%d",f[t][n1][m1][p1][0]);     
  else printf("-1"); 
}
 
int main()
{    
  Init();    
  Dp();    
  return 0;
}