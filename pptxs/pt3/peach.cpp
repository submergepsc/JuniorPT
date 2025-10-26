#include <iostream>

using namespace std;

int main() {
    int days = 10;
    int peaches = 1;
    for (int day = days - 1; day >= 1; --day) {
        peaches = (peaches + 1) * 2;
    }
    cout << peaches << '\n';
    return 0;
}
