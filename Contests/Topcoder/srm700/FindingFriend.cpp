#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FindingFriend {
	public:
		int find(int roomSize, vector <int> leaders, int friendPlace) {
			int tot = 0, res = 0;
			sort(leaders.begin(), leaders.end());
			for (auto rank : leaders) {
				if (rank > friendPlace) break;
				if (rank - 1 == tot) res = 0;
				if (rank == friendPlace) {
					return 1;
				}
				tot += roomSize;
				res ++;
			}
			return res;
		}
};