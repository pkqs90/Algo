// Simple tree dp, yet implemented poorly.
// Seems like a O(n^3) time complexity, but actually O(n^2). Each pair of nodes only contribute to the complexity once.
// There is actually no need for the cur[][], see this briliant code: http://codeforces.com/contest/581/submission/13269721

#include <bits/stdc++.h>

using namespace std;

const int N = 5007;
const int Inf = 0x3fffffff;
const int Mod = 1e9 + 7;
const double eps = 1e-8;

vector<int> e[N];
int sz, root, tot[N];
int f[N][2][N], cur[2][N];

void Dfs(int u, int pre) {
  if (e[u].size() == 1) {
    tot[u] = 1;
    f[u][1][1] = f[u][0][0] = 0;
    f[u][0][1] = f[u][1][0] = Inf;
    return;
  }
  for (int w = 0; w < e[u].size(); w++) {
    int v = e[u][w];
    if (v == pre) continue;

    Dfs(v, u);
    memset(cur, 0x3f, sizeof(cur));

    for (int i = 0; i < 2; i++) {
      int mxj = min(sz / 2, tot[u]);
      for (int j = mxj; j >= 0; j--) {
        for (int p = 0; p < 2; p++) {
          int mxq = min(tot[v], sz / 2);
          for (int q = 0; q <= mxq; q++) {
            if (j + q > sz / 2) break;
            cur[i][j + q] =
                min(cur[i][j + q], f[u][i][j] + f[v][p][q] + (i != p));
          }
        }
      }
    }
    tot[u] += tot[v];
    for (int i = 0; i < 2; i++) {
      int mxj = min(sz / 2, tot[u]);
      for (int j = mxj; j >= 0; j--) {
        f[u][i][j] = cur[i][j];
      }
    }
  }
}

int n, u, v;
int main() {
//  freopen("in.txt", "r", stdin);
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  if (n == 2) {
    puts("1");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    if (e[i].size() > 1) {
      root = i;
    } else {
      sz++;
    }
  }
  memset(f, 0x3f, sizeof(f));
  for (int i = 1; i <= n; i++) f[i][0][0] = f[i][1][0] = 0;
  Dfs(root, 0);
  printf("%d\n", f[root][0][sz / 2]);
}
