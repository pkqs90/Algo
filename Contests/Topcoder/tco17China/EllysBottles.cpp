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

const double eps = 1e-12;

class EllysBottles {

  public:
  double getVolume(vector <int> bottles, int k) {
    vector<double> s;
    for (int i = 0; i < bottles.size(); i ++)
      s.push_back(bottles[i]);
    while (k --) {
      sort(s.begin(), s.end());
      double mn = s[0];
      double mx = s[s.size() - 1];
      if (mx - mn < eps) break;
      double t = (mn + mx) / 2.0;
      s[0] = s[s.size() - 1] = t;
    }
    sort(s.begin(), s.end());
    return s[0];
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {42, 13, 17, 7, 22}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; double Arg2 = 20.0625; verify_case(0, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {42, 42, 42}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 42; double Arg2 = 42.0; verify_case(1, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1111111, 2222222, 3333333, 4444444, 5555555, 6666666, 7777777, 8888888, 9999999}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 5555555.0; verify_case(2, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {937831252, 223252363, 706118333, 954711869, 819583497, 520873195, 879422756, 464831418,
 156067240, 646868794, 894534170, 23380905, 855234472, 319560027, 305097549, 374217481,
 86837363, 718892301, 952809474, 558293585, 91833518, 862607400, 982038771, 942620013,
 507984782, 546527456, 615697673, 237645185, 53645793, 780959476, 136257699, 969658933,
 959150775, 43875123, 9012, 349823412, 85123543, 349085123, 194357213, 229834565}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1234567; double Arg2 = 5.08428837725E8; verify_case(3, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; double Arg2 = 0.5; verify_case(4, Arg2, getVolume(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  EllysBottles ___test;
  ___test.run_test(-1);
}
// END CUT HERE 
