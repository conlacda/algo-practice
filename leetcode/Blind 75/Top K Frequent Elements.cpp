// https://leetcode.com/problems/top-k-frequent-elements/
vector<int> topKFrequent(vector<int>& nums, int k) {
    /*
    map<int, int> m; val -> frequence
    vector<pair<int,int>> v;
    sort(v);
    get k elements
    */
    map<int, int> m;
    for (auto&v: nums) m[v]++;
    vector<pair<int,int>> a;
    for (auto&p: m) a.push_back(p);
    sort(a.begin(), a.end(), [&](pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;
    });
    vector<int> ans;
    for (int i=0;i<k;i++) {
        ans.push_back(a[i].first);
    }
    return ans;
}