// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
int maxProfit(vector<int>& prices) {
    // Loop i=0..n
    // If buy at ith -> profit??
    int ans = 0;
    int prevMin = prices[0];
    for (int i=1;i<prices.size();i++) {
        ans = max(ans, prices[i] - prevMin);
        prevMin = min(prevMin, prices[i]);
    }
    return ans;
}