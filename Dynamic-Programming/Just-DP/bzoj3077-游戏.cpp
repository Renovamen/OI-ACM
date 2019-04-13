#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int M=1000005,inf=0x7fffffff/2;
struct node
{
  int to,next;
}T[M]; 
int a[M],h[M],vis[M],Color[M],ch[M],f[M][2],Fa[M],q[M];
int cnt,Root,n;
 
void AddEdge(int x,int y)
{
  cnt++;
  T[cnt].to=y;
  T[cnt].next=h[x];
  h[x]=cnt;
}
 
void Dye()
{
  int L=0,R=1;
  q[R]=Root;
  while(L!=R)
  {
    L=(L+1)%M;
    int k=q[L];
    for(int i=h[k];i;i=T[i].next)
    {
      int to=T[i].to;
      if(!Color[to])
      {
        Color[to]=3-Color[k];
        R=(R+1)%M;
        q[R]=to;
      }	
    }     
  }
}
 
void Bfs()
{   
  int L=0,R=0;
  for(int i=1;i<=n;i++) 
  {  
    f[i][0]=inf,f[i][1]=0;
    if(ch[i]==0)q[++R]=i,f[i][0]=0;
  }  
  
  while(L!=R)
  {
    L=(L+1)%M;
    int v=q[L],u=Fa[v];
    f[v][0]+=a[v];
	
    if(Color[v]==1)
    {  
      if(f[v][1]<f[u][0]||(f[v][1]==f[u][0]&&f[v][0]>f[u][1]))
        f[u][0]=f[v][1],f[u][1]=f[v][0];
    }
	
    else 
    {  
      if(f[v][0]>f[u][1]||(f[v][0]==f[u][1]&&f[v][1]<f[u][0]))
        f[u][0]=f[v][1],f[u][1]=f[v][0];
    }
    if(!--ch[u])
    {
      R=(R+1)%M;
      q[R]=u;	  
    }
  }
}
 
int main()
{	  
  int u,v;
  scanf("%d",&n);
  for(int i=1;i<=n;i++)scanf("%d",&a[i]);
  for(int i=1;i<n;i++)
  {  
    scanf("%d%d",&u,&v);
    AddEdge(u,v);
    vis[v]=1,ch[u]++,Fa[v]=u;
  }
  
  for(int i=1;i<=n;i++)
    if(!vis[i])
    {
      Root=i;
      break;
    }
  Color[Root]=1;
  
  Dye();
  Bfs();
  printf("%d %d\n",f[Root][0],f[Root][1]);
  return 0;
}