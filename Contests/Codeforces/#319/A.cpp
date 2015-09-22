#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <set>
#include <bitset>
#include <algorithm>
using namespace std;

const int N = 50005;

int n; vector<int> vec;
bool is_prime(int x){
    for (int i = 2; i < x; i ++)
        if (x % i == 0) return 0;
    return 1;
}

int main() {
    cin >> n;
    for (int i = 2; i <= n; i ++) {
        if (is_prime(i)) {
            for (int j = i; j <= n; j *= i)
                vec.push_back(j);
        }
    }
    cout << vec.size() << endl;
    for (int i = 0; i < vec.size(); i ++)
        cout << vec[i] << ' ';
}
