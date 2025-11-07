#include<bits/stdc++.h>
using namespace std;

int rod_cutting_dp(vector<int>&price, int currLength, int idx, vector<vector<int>>&dp){
    if(idx==0)
        return currLength*price[idx];
    
    if(dp[currLength][idx] != -1)
        return dp[currLength][idx];
    
    int include = 0;
    if(currLength >= idx + 1)
        include = price[idx] + rod_cutting_dp(price, currLength - idx - 1, idx, dp);

    int exclude = 0 + rod_cutting_dp(price, currLength, idx - 1, dp);
    return dp[currLength][idx] = max(include,exclude);
}

int main(){
    int n;
    cout << "\nEnter length of rod: ";
    cin >> n;
    vector<int> price(n+1);
    cout << "\nEnter price of each piece length (space separated): ";
    for(int i = 0; i < n; i++){
        cin >> price[i];
    } 
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    int ans = rod_cutting_dp(price, n, n - 1, dp);
    cout << "\nMax Profit: " << ans << endl;
    return 0;
}
