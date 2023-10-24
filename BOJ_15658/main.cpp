#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int n;
vl nums;
vi ops(4); // +, -, *, /
vi selected;

ll maxans = numeric_limits<ll>::min();
ll minans = numeric_limits<ll>::max();

ll resolve() {
	auto ret = nums[0];

	for (auto i = 1; i < n; ++i) {
		if (0 == selected[i - 1]) {
			ret += nums[i];
		}
		else if (1 == selected[i - 1]) {
			ret -= nums[i];
		}
		else if (2 == selected[i - 1]) {
			ret *= nums[i];
		}
		else if (3 == selected[i - 1]) {
			ret /= nums[i];
		}
	}

	return ret;
}

void solve() {
	if (n - 1 == selected.size()) {
		const auto val = resolve();
		maxans = max(maxans, val);
		minans = min(minans, val);

		return;
	}

	for (auto i = 0; i < 4; ++i) {
		if (ops[i] <= 0) {
			continue;
		}

		selected.push_back(i);
		--ops[i];
		solve();
		++ops[i];
		selected.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n;

	nums = vl(n);
	for (auto&& x : nums) {
		cin >> x;
	}

	for (auto&& x : ops) {
		cin >> x;
	}

	selected = vi{};
	selected.reserve(n);

	solve();

	cout << maxans << '\n'
		<< minans;

	return 0;
}