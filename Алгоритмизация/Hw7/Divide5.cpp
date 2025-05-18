#include <iostream>
#include <vector>

using namespace std;

long long mergeAndCount(vector<int>& a, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    long long invCount = 0;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        }
        else {
            temp[k++] = a[j++];
            invCount += (mid - i + 1); // Все элементы от i до mid > a[j]
        }
    }

    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];

    for (int idx = 0; idx < k; idx++) {
        a[left + idx] = temp[idx];
    }

    return invCount;
}

long long mergeSortAndCount(vector<int>& a, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += mergeSortAndCount(a, left, mid);
        invCount += mergeSortAndCount(a, mid + 1, right);
        invCount += mergeAndCount(a, left, mid, right);
    }
    return invCount;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << mergeSortAndCount(a, 0, n - 1) << endl;

    return 0;
}