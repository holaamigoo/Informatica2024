#include <iostream>
#include <vector>

using namespace std;

bool canSumToK(vector<int>& nums, int k, int index) {
    if (k == 0) return true; // Нашли подмножество
    if (k < 0 || index >= nums.size()) return false; // Неудача

    // Вариант 1: Включить nums[index]
    if (canSumToK(nums, k - nums[index], index + 1)) {
        return true;
    }

    // Вариант 2: Не включать nums[index]
    return canSumToK(nums, k, index + 1);
}

int main4() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    if (canSumToK(nums, k, 0)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}