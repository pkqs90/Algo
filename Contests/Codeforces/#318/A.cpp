#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <set>
#include <bitset>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 7;

int main() {
    int a, b = -1, n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        scanf("%d", &a);
        while (a % 2 == 0) a /= 2;
        while (a % 3 == 0) a /= 3;
        if (b == -1) b = a;
        else if (b != a) {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
}
