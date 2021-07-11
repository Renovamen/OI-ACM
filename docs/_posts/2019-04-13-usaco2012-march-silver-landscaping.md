---
title: Landscaping
tags:
  - 动态规划
---


## Problem

Source: [USACO 2012 March Silver](http://www.usaco.org/index.php?page=viewproblem2&cpid=126){:target="_blank"}


### Description

Farmer John is building a nicely-landscaped garden, and needs to move a large amount of dirt in the process. The garden consists of a sequence of $N$ flowerbeds $(1 \leq N \leq 100)$, where flowerbed $i$ initially contains $A_i$ units of dirt.  Farmer John would like to re-landscape the garden so that each flowerbed $i$ instead contains $B_i$ units of dirt.  The $A_i$'s and $B_i$'s are all integers in the range $0 - 10$. To landscape the garden, Farmer John has several options: he can purchase one unit of dirt and place it in a flowerbed of his choice for $X$.  He can remove one unit of dirt from a flowerbed of his choice and have it shipped away for ​$Y$. He can also transport one unit of dirt from flowerbed $i$ to flowerbed $j$ at a cost of $Z$ times $\text{abs}(i-j)$.  Please compute the minimum total cost for Farmer John to complete his landscaping project.


### Input

Line $1$: Space-separated integers $N$, $X$, $Y$, and $Z (0 \leq X, Y, Z \leq 1000)$.

Lines $2 \dots 1+N​$: Line $i+1​$ contains the space-separated integers $A_i​$ and $B_i​$.


### Output

Line $1$: A single integer giving the minimum cost for Farmer John's landscaping project.


### Sample Input

```
4 100 200 1
1 4
2 3
3 2
4 0
```


### Sample Output

```
210
```


&nbsp;

## Translation

$N$ 个数排成一行，值分别为 $A_i$，现在希望把每个数对应地改成 $B_i$（$A_i, B_i$ 的值均在 0 - 10 之间）。改变的方式有 3 种：

1. 把 $A_i$ 增加到 $B_i$，每增加 1，花费 $X$

2. 把 $A_i$ 减少到 $B_i$，每减少 1，花费 $Y$

3. 把第 $i$ 个数的值转移到第 $j$ 个数，每转移 1，花费为 $Z * \text{abs}(i-j)$

问：最小的花费是多少。



&nbsp;

## Solution

由于数字范围小（$0-10$），所以可以把原始状态和目标状态换成另一种表示方式，如：

- 原始状态：$1, 2, 3, 4$，表示成：$1, 2, 2, 3, 3, 3, 4, 4, 4, 4$
- 目标状态：$4, 3, 2, 0$，表示成：$1, 1, 1, 1, 2, 2, 2, 3, 3$

这样该题就变为了标准的求字符串编辑距离（$A$ 串变成 $B$ 串的代价）动规。


**状态转移方程：**

$C(i,j)$：将 $A$ 串的前 $i$ 个变成 $B$ 串的前 $j$ 个的最小代价

$$
C(i, j) = \min \Big( C(i - 1, j) + Y,     C(i, j - 1) + X,    C(i - 1, j - 1) + Z * \text{abs}(A[i] - B[j]) \Big)
$$

$N$ 最大为 100，转换后最长为 1000，算法时间复杂度为 $O(n^2)$。


## Code

[Github (C++)](https://github.com/Renovamen/OI-ACM/blob/master/Dynamic-Programming/Others/USACO2012-March-Silver-Landscaping.cpp){:.button.button--outline-info.button--rounded}{:target="_blank"}


```c++
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
```
