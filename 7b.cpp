#include <iostream>

using namespace std;

// op = 0 -> +
// op = 1 -> *
// op = 2 -> ||

long long int concatLL(long long int a, long long int b) {
  string sa = to_string(a), sb = to_string(b);
  return stoll(sa+sb);
}

bool evalSimple(long long int target, vector<long long int>& nums, vector<long long int>& ops) {
  long long int ans = nums[0];
  for (int i = 0; i < ops.size(); i++) {
    if (ops[i] == 0) {
      ans += nums[i+1];
    } else if (ops[i] == 1) {
      ans *= nums[i+1];
    } else {
      ans = concatLL(ans, nums[i+1]);
    }
  }
  return ans == target;
}

int findSolutions(long long int target, vector<long long int>& nums, vector<long long int>& ops) {
  if (ops.size() == nums.size() - 1) {
    return evalSimple(target, nums, ops) ? 1 : 0;
  }

  vector<long long int> nOps = ops, nOps2 = ops, nOps3 = ops;
  nOps.push_back(0);
  nOps2.push_back(1);
  nOps3.push_back(2);
  return findSolutions(target, nums, nOps)
    + findSolutions(target, nums, nOps2)
    + findSolutions(target, nums, nOps3);
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
