---
title: Selection
tags:
  - 动态规划
  - 博弈
---


## Problem

Source: BSOJ 1744


### Description

wind 发明了一个好玩的游戏，叫小杉一起玩。但小杉玩了十几盘，总是输，他想知道是不是从一开始他就注定要输。

这个游戏是这样的，wind 先写下一排数。既然是一排，当然有首尾咯。wind 和小杉每次只能从这排数的头或尾取一个数。最后谁取的数的和多，谁就赢了。

假如你是小杉，请算出你最多能取到的和。wind 的智商是很高的（怪不得小杉一直输），你必须知道他总是做出最优决策。 


### Input

多组输入数据。

每组测试数据的第一行仅有一个数 $n (n \leq 2000)$

第二行也仅有一个数，0 表示 wind 先取数，1 表示小杉先取数

第三行有 $n$ 个数，是 wind 给出的一排数，这 $n$ 个数均不超过 $1e6$


### Output

对每组测试数据输出一行，仅有一个整数 $s$，表示小杉最多能取到多少数


### Sample Input

```
1
1
1
```


### Sample Output

```
1
```


&nbsp;

## Solution

$f(i,j)$：先取数的人在第 $i$ 个数到第 $j$ 个数之间能取到的最大和

$s(i,j)​$：第 ​$i​$ 个数到第 $j​$ 个数的部份和

**状态转移方程：**

$$
f(i,j)= \max \Big \{ a(i)+s(i+1,j)-f(i+1,j),a(j)+s(i,j-1)-f(i,j-1) \Big \}
$$

解释：先取的人从 $i$ 到 $j$ 取得最大和的情况，要么是该人先取 $i$，加上 $i+1$ 到 $j$ 的总和，再减去对方先取时从 $i+1$ 到 $j$ 取得的最大和；或是该人先取 $j$，加上 $i$ 到 $j-1$ 的总和，再减去对方先取时从 $i$ 到 $j-1$ 取得的最大和（因为两人都按同一策略取）。


## Code

[Github (C++)](https://github.com/Renovamen/OI-ACM/blob/master/code/动态规划/其他/BSOJ1744-selection.cpp){:.button.button--outline-info.button--rounded}{:target="_blank"}


```c++
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int a[2005], s[2005], f[2005][2005];
int n, t;

void Dp() {
    for(int l = 2; l <= n; l++)
        for(int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            f[i][j] = max(a[i] + s[j] - s[i] - f[i+1][j], a[j] + s[j-1] - s[i-1] - f[i][j-1]);
        }

    if(t == 0) printf("%d\n",s[n] - f[1][n]);
    else printf("%d\n", f[1][n]);
}

int main() {
    while(scanf("%d%d", &n, &t) != EOF) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            s[i] = s[i-1] + a[i];
            f[i][i] = a[i];
        }
        Dp();
    }
    return 0;
}
```
