#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


int getElement (std::string& a, std::string& b, int i, int j, std::vector<std::vector<int>>& D) {
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
    std::vector<std::vector<int>> D (
    a.length () + 1, std::vector<int> (b.length () + 1, 0));

    for (int i = 0; i < a.length () + 1; ++i) {
        for (int j = 0; j < b.length () + 1; ++j)
            D[i][j] = getElement (a, b, i, j, D);
    }

    return D[a.length ()][b.length ()];
}

int main () {

    std::string a = "avstria";
    std::string b = "avstralia";

    std::cout << LevensteinDistance (b, a) << std::endl;


    return 0;
}