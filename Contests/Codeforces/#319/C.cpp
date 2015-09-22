#include <bits/stdc++.h>

using namespace std;

int n, x, y;
vector<pair<pair<int, int>, int>> pnt[1005];

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++) {
        scanf("%d%d", &x, &y);
        int id = y / 1000;
        if (id == 1000) id --;
        pnt[id].push_back({{x, y}, i});
    }
    for (int i = 0; i < 1000; i ++) {
        sort(pnt[i].begin(), pnt[i].end());
        if (i & 1) reverse(pnt[i].begin(), pnt[i].end());
        for (int j = 0; j < pnt[i].size(); j ++) {
            printf("%d ", pnt[i][j].second + 1);
        }
    }
}
