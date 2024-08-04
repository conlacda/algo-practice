// https://leetcode.com/problems/product-of-array-except-self/
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> prefix, suffix;
    int f = 1;
    int n = nums.size();
    for (int i=0;i<n;i++) {
        f *= nums[i];
        prefix.push_back(f);
    }
    f = 1;
    for (int i=n-1;i>=0;i--) {
        f *= nums[i];
        suffix.push_back(f);
    }
    reverse(suffix.begin(), suffix.end());
    vector<int> ans;
    for (int i=0;i<n;i++) {
        int b = (i == 0) ? 1: prefix[i-1];
        int a = (i >= n-1) ? 1: suffix[i+1];
        ans.push_back(a * b);
    }
    return ans;
}