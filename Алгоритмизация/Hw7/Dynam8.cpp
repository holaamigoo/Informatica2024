#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main2() {
    // Чтение первой последовательности
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Чтение второй последовательности
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // Инициализация ДП-таблицы
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Заполнение ДП-таблицы
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Длина НОП
    int lcs_length = dp[n][m];
    cout << lcs_length << endl;

    if (lcs_length == 0) {
        return 0; // Нет общей подпоследовательности
    }

    // Восстановление индексов
    vector<int> indices_a, indices_b;
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            indices_a.push_back(i); // Индексы с 1
            indices_b.push_back(j);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    // Разворачиваем, так как шли с конца
    reverse(indices_a.begin(), indices_a.end());
    reverse(indices_b.begin(), indices_b.end());

    // Вывод индексов первой последовательности
    for (int idx : indices_a) {
        cout << idx << " ";
    }
    cout << endl;

    // Вывод индексов второй последовательности
    for (int idx : indices_b) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
