#include <iostream>
#include <climits>
using namespace std;
int subArray(int *arr, int size){
    int maxSum = INT_MIN,currSum=0;
    for(int i=0;i<size;i++){
        currSum+=arr[i];
        maxSum=max(currSum,maxSum);
        
        // Skip if currSum becomes negative as negative sum never contributes for greater sum.
        if(currSum<0){
            currSum=0;
        }
    }
    return maxSum;
}

int main() {
    int arr[] = {2,-3,6,-5,4,2};
    cout << subArray(arr, sizeof(arr)/sizeof(int));
    return 0;
}