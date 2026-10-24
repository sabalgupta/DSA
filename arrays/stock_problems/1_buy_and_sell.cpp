// Leetcode 121

#include <iostream>
#include <climits>
using namespace std;

// Brute Force: O(n^2)
// int maxProfit(int *prices, int size){
//     int bestBuy[size];
//     for(int i=size-1;i>=0;i--){
//         int bestBuyingPrice = INT_MAX;
//         for(int j=i-1;j>=0;j--){
//             bestBuyingPrice=min(bestBuyingPrice, prices[j]);
//         }
//         bestBuy[i]=bestBuyingPrice;
//     }
//     int profit = INT_MIN;
//     for(int i=0;i<size;i++){
//         profit=max(profit, prices[i]-bestBuy[i]);
//     }
//     if(profit<0)
//         return 0;
//     return profit;
// }

// Optimized: O(n) time with O(1) space
int maxProfit(int *prices, int size){
    int currMinBuyingPrice = INT_MAX;
    int profit = 0;

    for (int i = 0; i < size;i++){
        currMinBuyingPrice = min(currMinBuyingPrice, prices[i]);
        int currProfit = prices[i] - currMinBuyingPrice;
        profit = max(profit, currProfit);
    }

    return profit;
}

int main() {
    int prices[] = {7,6,4,3,1};
    int size = sizeof(prices)/sizeof(int);
    cout << maxProfit(prices, size);
    return 0;
}