// https://leetcode.com/problems/two-sum/description/
vector<int> twoSum(vector<int>& nums, int target) {
    // a[i] + a[j] = target.
    // a[i] target-a[j] exists in nums
    set<int> a(nums.begin(), nums.end());
    int n = nums.size();
    for (int i=0;i<n;i++) {
        if (a.find(target - nums[i]) != a.end()) {
            for (int j=i+1;j<n;j++) {
                if (nums[j] == target - nums[i]) {
                    return vector<int>{i, j};
                }
            }
        }
    }
    return vector<int>{-1, -1};
}