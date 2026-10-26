// Leetcode 189

// class Solution {
// public:
//     void reverse(vector<int> &nums, int start, int end){
//         while(start<end){
//             swap(nums[start], nums[end]);
//             start++;
//             end--;
//         }
//     }

//     void rotate(vector<int>& nums, int k) {
//         int n=nums.size();
//         k=k%n; // Finding least number of rotations by eliminating all k=n(redundant) rotations
//         reverse(nums, 0, n-k-1);
//         reverse(nums,n-k,n-1);
//         reverse(nums,0,n-1);
//     }
// };