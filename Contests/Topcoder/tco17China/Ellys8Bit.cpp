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

const long long inf = 1e9 + 7;

class Ellys8Bit {

  long long c[70][70];
  vector<int> res;

  void Dfs(int rem, long long tot) {
    // cout << rem << ' ' << tot << "~" << endl;
    if (rem == 0) return;
    int rest = rem - 1;
    for (int i = rest; i < 62; i ++) {
      tot -= c[i][rest];
      if (tot <= 0) {
        tot += c[i][rest];
        res.push_back(i+1);
        // cout << i << "@@" << endl;
        Dfs(rem-1, tot);
        break;
      }
    }
  }

  public:
  long long getNumber(int N) {
    memset(c, 0, sizeof(c));
    c[0][0] = 1;
    for (int i = 1; i < 70; i ++) {
      c[i][0] = 1;
      for (int j = 1; j <= 7; j ++) {
        c[i][j] = c[i-1][j-1] + c[i-1][j];
      }
    }
    res.clear();
    Dfs(8, N);
    long long sum = 0;
    for (int i = 0; i < res.size(); i ++)
      sum += (1LL << (res[i]-1));
    return sum;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; long long Arg1 = 255LL; verify_case(0, Arg1, getNumber(Arg0)); }
	void test_case_1() { int Arg0 = 2; long long Arg1 = 383LL; verify_case(1, Arg1, getNumber(Arg0)); }
	void test_case_2() { int Arg0 = 3; long long Arg1 = 447LL; verify_case(2, Arg1, getNumber(Arg0)); }
	void test_case_3() { int Arg0 = 1000; long long Arg1 = 7032LL; verify_case(3, Arg1, getNumber(Arg0)); }
	void test_case_4() { int Arg0 = 133742; long long Arg1 = 1087088LL; verify_case(4, Arg1, getNumber(Arg0)); }
	void test_case_5() { int Arg0 = 537655880; long long Arg1 = 1125899983585796LL; verify_case(5, Arg1, getNumber(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  Ellys8Bit ___test;
  ___test.run_test(-1);
}
// END CUT HERE 
