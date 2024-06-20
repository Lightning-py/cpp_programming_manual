#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


// функция для полчения значения в ячейке [i][j]
int getElement (std::string& a, std::string& b, int i, int j, std::vector<std::vector<int>>& D) {
    // все по алгоритму из методички
    if ((i == 0) && (j == 0))
        return 0;

    if (i == 0)
        return j;
    if (j == 0)
        return i;

    int ans = D[i][j - 1] + 1;
    ans     = std::min (ans, D[i - 1][j] + 1);
    ans     = std::min (ans, D[i - 1][j - 1] + !(a[i - 1] == b[j - 1]));

    return ans;
}

int LevensteinDistance (std::string& a, std::string& b) {
    // создадим таблицу
    std::vector<std::vector<int>> D (
    a.length () + 1, std::vector<int> (b.length () + 1, 0));

    // пройдемся по таблице и заполним ее
    for (int i = 0; i < a.length () + 1; ++i) {
        for (int j = 0; j < b.length () + 1; ++j)
            D[i][j] = getElement (a, b, i, j, D);
    }


    // вернем значение в последней ячейке
    return D[a.length ()][b.length ()];
}

int main () { // функция для проверки

    std::string a = "labrador"; // создадим две строки (на русском не пашет, хз почему)
    std::string b = "gibraltar";

    std::cout << LevensteinDistance (b, a) << std::endl; // выведем результат


    return 0;
}