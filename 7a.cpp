#include <iostream>
#include <sstream>

using namespace std;

// op = 0 -> +
// op = 1 -> *

bool eval(long long int target, vector<long long int>& nums, vector<long long int>& ops) {
  long long int ans = nums[0];
  for (int i = 0; i < ops.size(); i++) {
    if (ops[i] == 0) {
      ans += nums[i+1];
    } else {
      ans *= nums[i+1];
    }
  }
  return ans == target;
}

int findSolutions(long long int target, vector<long long int>& nums, vector<long long int>& ops) {
  if (ops.size() == nums.size() - 1) {
    if (eval(target, nums, ops)) {
      return 1;
    } else {
      return 0;
    }
  }

  vector<long long int> nOps = ops, nOps2 = ops;
  nOps.push_back(0);
  nOps2.push_back(1);
  return findSolutions(target, nums, nOps) + findSolutions(target, nums, nOps2);
}

int main() {
  string s;
  long long int ans = 0;
  while (getline(cin, s)) {
    string target;
    vector<string> values;
    string temp;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == ':') {
        target = temp;
        temp = "";
      } else if (s[i] == ' ' || s[i] == '\0') {
        if (temp.size() > 0) values.push_back(temp);
        temp = "";
      } else {
        temp += s[i];
      }
    }
    if (temp.size() > 0) values.push_back(temp);

    long long int t = stoll(target);
    vector<long long int> v, ops;
    for (int i = 0; i < values.size(); i++) {
      v.push_back(stoll(values[i]));
    }

    if (findSolutions(t, v, ops) != 0) {
      ans += t;
    }
  }

  cout << ans << endl;
  return 0;
}

// 12366007968
