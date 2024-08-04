// https://leetcode.com/problems/contains-duplicate/
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> a{nums.begin(), nums.end()};
    return a.size() != nums.size();
}