#include <iostream>
#include <climits>
using namespace std;
int subArray(int *arr, int size){
    int maxSum = INT_MIN;
    for(int start=0;start<size;start++){
        int sum =0;
        for(int end=start;end<size;end++){
            sum+=arr[end];
        }
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}

int main() {
    int arr[] = {2,-3,6,-5,4,2};
    cout << subArray(arr, sizeof(arr)/sizeof(int));
    return 0;
}