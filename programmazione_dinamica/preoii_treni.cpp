// Problema: https://training.olinfo.it/#/task/preoii_treni/statement
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const int maxn = (int)1e6 + 1;
long long dp[maxn][3];
int tempo_massimo (int n, int A[], int B[])
{
  dp[0][0] = A[0];
  dp[0][1] = B[0];
  dp[0][2] = 0;
  for (int i = 1; i < n; i++) {
    int xa = A[i], xb = B[i];
    dp[i][0] = std::max (dp[i - 1][0] + xa, dp[i - 1][1] + xa);
    dp[i][1] = dp[i - 1][2] + xb;
    dp[i][2] = std::max (dp[i - 1][0], dp[i - 1][1]);
  }
  return std::max (dp[n - 1][0], dp[n - 1][1]);
}

int main ()
{}
