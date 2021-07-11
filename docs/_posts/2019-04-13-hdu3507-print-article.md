---
title: Print Article
subtitle: "2010 ACM-ICPC 多校训练赛 - HDU 3507"
tags:
  - 动态规划
  - 斜率优化
  - 入门题
---

斜率优化：把决策与决策之间表示成一个类似斜率 $\frac{y_1-y_2}{x_1-x_2}$ 的式子，进一步分析其中的单调性，并用队列维护其有用决策。因此斜率优化又称队列优化。


## Problem

Source: [HDU 3507](http://acm.hdu.edu.cn/showproblem.php?pid=3507){:target="_blank"}, 2010 ACM-ICPC 多校训练赛


### Description

Zero has an old printer that doesn't work well sometimes. As it is antique, he still like to use it to print articles. But it is too old to work for a long time and it will certainly wear and tear, so Zero use a cost to evaluate this degree. 

One day Zero want to print an article which has $N$ words, and each word $i$ has a cost $C_i$ to be printed. Also, Zero know that print $k$ words in one line will cost $(\sum Ci)^2+M​$.

$M$ is a const number. 

Now Zero want to know the minimum cost in order to arrange the article perfectly. 


### Input

There are many test cases. For each test case, There are two numbers $N$ and $M$ in the first line $(0 ≤ n ≤ 500000, 0 ≤ M ≤ 1000)$. Then, there are $N$ numbers in the next $2$ to $N + 1$ lines. Input are terminated by EOF.


### Output

A single number, meaning the mininum cost to print the article.


### Sample Input

```
5 5
5
9
5
7
5
```


### Sample Output

```
230
```


&nbsp;

## Translation

给出 $N (0 \leq N  \leq 500000)$ 个单词，每个单词有个非负权值 $C_i$，现要将它们分成连续的若干段，每段的代价为 $(\sum Ci)^2+M$，求最优方案，使得总费用最小。


&nbsp;

## Solution

可以很容易的得到一个 $O(N^2)​$ 的算法：

$s(i)$：前 $i$ 个单词的权值和

$f(i)$：将前 $i$ 个单词划分完毕后的最优值

**状态转移方程：**

$$
f(i) = \min \Big ( f(j) + (s(i)-s(j))^2 + M \Big) \quad (0 \leq j \leq i-1)
$$

但 $N$ 的范围是 $500000$，这个算法会超时，所以需要优化。


### 斜率优化

#### 求斜率方程

固定 $i$，考虑它的两个决策点 $j,k (j<k)$。

记 $g(\text{pos}) = f(\text{pos}) + (s(i) - s(\text{pos}))^2 + M$，即 $i$ 从 $\text{pos}$ 转移的代价。如果决策点 $k$ 优于 $j$，那么就有：

$$
g(k) < g(j)
$$

一般化为左边是 $j,k$，右边是 $i$ 的形式：

$$
\Rightarrow f(k) + (s(i)-s(k))^2 + M < f(j) + (s(i)-s(j))^2 + M
$$

$$
\Rightarrow f(k) - f(j) + s(k)^2 - s(j)^2 < 2 \cdot s(i) \cdot (s(k)-s(j))​
$$

$$
\Rightarrow \frac{f(k) - f(j) + s(k)^2 - s(j)^2}{s(k) - s(j)} < 2 \cdot s(i)​
$$

$$
\Rightarrow \frac{f(j) - f(k) + s(j)^2 - s(k)^2}{s(j) - s(k)} < 2 \cdot s(i)
$$

可以看到不等式左边与 $i$ 无关，右边只与 $i$ 有关。

左边像一个两点间的斜率式，所以记：

$$
\text{Slope}(j,k) = \frac{f(j) - f(k) + s(j)^2 - s(k)^2}{s(j) - s(k)}
$$


#### 结论 1

对于 $i$ 的两个决策点 $j, k (j < k)$，决策 $k$ 优于决策 $j$ 就等价于 $\text{Slope}(j, k) < 2 \cdot s(i)$。换句话说，如果 $\text{Slope}(j, k) < 2 \cdot s(i)$，那么决策 $k$ 优于 $j$，反之决策 $j$ 不比 $k$ 差。

我们还可以知道，决策点 $k$ 永远会比决策点 $j$ 优，因为对于 $i$ 以后的点 $i'$，一定有：$\text{Slope}(j, k) < 2 \cdot s(i) < 2 \cdot s(i')$（也就证明了较优决策点对后续状态影响的持续性）。因此这里的优劣应该是全局的，而不只限于 $i$。


#### 结论 2

再来考虑三个点 $j, k, L (j < k < L)$ 之间的优劣关系，如果 $\text{Slope}(j, k) > \text{Slope}(k, L)$：

1. 若 $\text{Slope}(k, L) < 2 \cdot s(i)$，那么由之前的结论 1 可知，$L$ 比 $k$ 优；
2. 若 $\text{Slope}(k, L) > 2 \cdot s(i)$，则 $\text{Slope}(j,k) > 2 \cdot s(i)$，那么由之前的结论 1，决策 $j$ 不比 $k$ 差；

综上可知，如果 $\text{Slope}(j, k) > \text{Slope}(k, L)$，那么 $k$ 永远不会成为某个点的最优决策，是可以淘汰掉的。


#### 队列的维护规则

可以将决策放到一个队列中，利用以上两个结论剔除无用决策点，达到快速转移的目的。

记队列的头指针为 $h$，尾指针为 $t$：

1. 对于队首，如果 $\text{Slope}(q(h), q(h+1)) < 2 \cdot s(i)$，则 $q(h)$ 一定可以去掉，$h$++​；
2. 事实上经过这样的调整后，$q(h)$ 就是 $i$ 的最优决策，直接取来更新 $f(i)$；
3. $f(i)$ 加入队尾，并用 $i$ 去剔除无用决策。对于队列的尾部，如果 $\text{Slope}(q(t-1), q(t)) > \text{Slope}(q(t), i)$，那么 $q(t)$ 可以去掉，$t$- -。


#### 算法框架

```
for i=1 to n do
{    
    当队列不为空时，更新队头；
    取当前队头更新 f[i]；
    用 i 去更新队尾；
    将 i 加入队尾；
}
```

可以看到外层循环是 $O(N)$ 的，内层里每个元素进出队列仅一次，所以总效率为 $O(N)$。


## Code

[Github (C++)](https://github.com/Renovamen/OI-ACM/blob/master/Dynamic-Programming/Convex-Hull-Trick/HDU3507-Print-Article.cpp){:.button.button--outline-info.button--rounded}{:target="_blank"}

```c++
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
 
const int Maxn = 500005;
int f[Maxn], q[Maxn], Sum[Maxn];
int N, M;

// 斜率分子
int Slope_Up(int j,int k)
{
    return f[j] + Sum[j] * Sum[j] - (f[k] + Sum[k] * Sum[k]);
}
 
// 斜率分母
int Slope_Down(int j,int k)
{
    return Sum[j] - Sum[k];
}

void DP()
{
    int L = 0, R = 0;
    q[R++] = 0;
    f[0] = 0;

    for(int i = 1; i <= N; i++)
    {
        while(L + 1 < R && Slope_Up(q[L+1], q[L]) <= 2 * Sum[i] * Slope_Down(q[L+1], q[L]))L++;
        int j = q[L];
        
        f[i] = f[j] + (Sum[i]-Sum[j]) * (Sum[i]-Sum[j]) + M;
        
        while(L + 1 < R && Slope_Up(i, q[R-1]) * Slope_Down(q[R-1], q[R-2]) <= Slope_Up(q[R-1], q[R-2]) * Slope_Down(i, q[R-1]))R--;
        q[R++] = i;
    }
    cout << f[N] << endl;
}
 
int main()
{
    while(~scanf("%d%d", &N, &M))
    {
        Sum[0] = 0;
        for(int i = 1; i <= N; i++)
        {
            int x;
            cin >> x;
            Sum[i] = Sum[i-1] + x;
        }
        DP();
    }
    return 0;
}
```
