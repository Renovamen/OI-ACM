#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<cmath>
using namespace std;

const int inf = 0x7fffffff / 2;
int A[1005], B[1005], C[1005][1005];
int k, n, la, lb, x, y, z;
 
int main()
{
  scanf("%d%d%d%d", &n, &x, &y, &z);
  for(int i = 1; i <= n; i++) 
  {
    scanf("%d", &k); 
    //按位置展开A串
    while(k > 0) 
    { 
      A[++la] = i; 
      k--;
    }
    
    scanf("%d", &k); 
    //按位置展开B串
    while(k > 0) 
    { 
      B[++lb] = i; 
      k--;
    }
  }
  
  //初值
  for(int j = 0; j <= lb; j++) C[0][j] = j * x;
  for(int i = 0; i <= la; i++) C[i][0] = i * y;
 
  for(int i = 1; i <= la; i++)
   for(int j = 1; j <= lb; j++) 
   {
     C[i][j] = inf;
     C[i][j] = min(C[i][j], C[i][j-1] + x); // 插入
     C[i][j] = min(C[i][j], C[i-1][j] + y); // 删除
     C[i][j] = min(C[i][j], C[i-1][j-1] + z * abs(A[i] - B[j])); // 更改
   }  

  printf("%d\n", C[la][lb]);
  return 0;
}