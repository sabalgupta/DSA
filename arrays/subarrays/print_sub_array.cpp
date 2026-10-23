#include <iostream>
using namespace std;
void subArray(int *arr, int size){
    for(int start=0;start<size;start++){
        for(int end=start;end<size;end++){
            for (int i = start; i <= end;i++){
                cout << arr[i] << " ";
            }
            cout << ",";
        }
        cout << endl;
    }
}

int main() {
    int arr[] = {2,-3,6,-5,4,2};
    subArray(arr, sizeof(arr)/sizeof(int));
    return 0;
}