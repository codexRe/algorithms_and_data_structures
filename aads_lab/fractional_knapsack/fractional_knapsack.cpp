#include<bits/stdc++.h>
using namespace std;

vector<pair<double,pair<int,int>>> normalize_sort(vector<int>& val, vector<int>& wt){
    vector<pair<double,pair<int,int>>> calc;
    for(long unsigned int i = 0; i < val.size(); i++){
        double ans = double(val[i]) / double(wt[i]);
        calc.push_back(make_pair(ans, make_pair(val[i], wt[i])));
    }
    sort(calc.begin(), calc.end(), [](auto &a, auto &b){ return a.first > b.first; });
    return calc;
}
      
double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
    vector<pair<double,pair<int,int>>> vec = normalize_sort(val, wt);
    double ans = 0.00;
    int currentweight = 0;
    for(long unsigned int i = 0; i < vec.size(); i++){
        int temp = currentweight + vec[i].second.second;
        if(temp > capacity){
            ans += double(vec[i].first) * double(capacity - currentweight);
            break;
        } 
        else{
            ans += vec[i].second.first;
            currentweight += vec[i].second.second;
        }
    }
    return ans;
}

int main(){
    int n = 0, capacity = 0;
    cout << "\nEnter total number of items: ";
    cin>>n;
    cout << "\nEnter value of items (space separated): ";
    vector<int>val(n);
    for(int i = 0; i < n; i++){
        cin>>val[i];
    }
    cout << "\nEnter weight of items (space separated): ";
    vector<int>wt(n);
    for(int i = 0; i < n; i++){
        cin>>wt[i];
    }
    cout << "\nEnter total capacity of knapsack: ";
    cin>>capacity;
    double ans = fractionalKnapsack(val, wt, capacity);

    cout << "\nMax Profit: ";
    cout<<ans<<endl;
    return 0;
}
