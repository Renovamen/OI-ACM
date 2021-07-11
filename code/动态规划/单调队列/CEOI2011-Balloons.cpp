#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<cmath>
using namespace std;

const int M = 200005;
int n, top;
double x[M], r[M], q[M];
 
double Cal(int i,int j)
{
  return (x[i] - x[j]) * (x[i] - x[j]) / (4 * r[j]);
}
 
int main()
{
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> x[i] >> r[i];
 
  for(int i = 1; i <= n; i++)
  {
    while(top)
    {	
      int j = q[top];
      r[i] = min(r[i], Cal(i,j));
      if(r[i] >= r[j]) top--;
      else break;
    }
    q[++top] = i;
  }  
  for(int i = 1; i <= n; i++) cout << fixed << setprecision(5) << r[i] << endl;
  return 0;
}