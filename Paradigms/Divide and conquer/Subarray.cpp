#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i=0;i<n;i++) {
        cin >> arr[i];
    }

    int maxSoFar=arr[0];
    int globalMax=arr[0];

    int start=0 , end=0 , curStart=0;

    for (int i=1;i<n;i++) {
        if (maxSoFar < 0) {
            maxSoFar=arr[i];
            curStart = i;
        }
        else {
            maxSoFar+=arr[i];
        }
        if (maxSoFar > globalMax) {
            globalMax=maxSoFar;
            start=curStart;
            end=i;
        }
    }

    cout << " Maksimalna suma e: " << globalMax << endl;
    cout << "Podnizata e: " ;
    for (int i=start ; i<=end; i++) {
        cout << arr[i] << " " ;
    }
}
