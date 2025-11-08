#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cout << "\nEnter string: ";
    cin >> s;
    int n = (int)s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    int maxLen = 0;
    int endPos = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (s[i - 1] == s[j - 1]) {
                dp[i][j] = min(dp[i - 1][j - 1] + 1, j - i);
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endPos = j;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    if (maxLen == 0) {
        cout << "No repeating non-overlapping substring found.\n";
    } else {
        string ans = s.substr(endPos - maxLen, maxLen);
        cout << "Longest Repeating Non-overlapping Substring: " << ans << "\n";
        cout << "Length: " << maxLen << "\n";
    }

    return 0;
}
