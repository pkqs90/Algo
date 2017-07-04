#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class ScoresSequence {

  bool f[105][105], used[105];

  public:
  int count(vector <int> s) {
    memset(f, 0, sizeof(f));
    memset(used, 0, sizeof(used));
    int n = s.size();
    for (int i = 0; i < n; i ++)
      f[i][i] = 1;
    while (1) {
      int id = -1, mx = 0;
      for (int i = 0; i < n; i ++) {
        if (s[i] > mx && !used[i]) {
          mx = s[i], id = i;
        }
      }
      if (id == -1) break;
      vector<pair<int, int>> v;
      for (int i = 0; i < n; i ++) {
        if (i != id && !used[i]) v.push_back({s[i], i});
      }
      sort(v.begin(), v.end());
      for (int i = 0; i < s[id]; i ++) {
        f[id][v[i].second] = 1;
      }
      for (int i = s[id]; i < v.size(); i ++) {
        f[v[i].second][id] = 1; s[v[i].second] --;
      }
      s[id] = 0;
      used[id] = 1;
    }
    for (int k = 0; k < n; k ++)
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
          if (f[i][k] && f[k][j]) f[i][j] = 1;
    int tot = 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        tot += f[i][j];
    return tot;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arr0[] = {1, 0, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arr0[] = {0, 2, 8, 4, 3, 9, 1, 5, 7, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 55; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { int Arr0[] = {22,20,14,13,17,15,12,18,23,15,21,26,33,5,19,9,37,0,25,28,4,12,35,32,25,7,31,6,2,29,10,33,36,27,39,28,40,3,8,38,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1422; verify_case(4, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  ScoresSequence ___test;
  ___test.run_test(-1);
}
// END CUT HERE 
