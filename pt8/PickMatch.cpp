#include <iostream>

using namespace std;

int main() {
    int matches = 21;
    cout << "There are " << matches << " matches on the table.\n";
    cout << "You move first. Whoever takes the last match loses.\n";

    bool humanTurn = true;
    while (matches > 0) {
        if (humanTurn) {
            int take = 0;
            while (true) {
                cout << "How many matches will you take (1-4)? ";
                if (!(cin >> take)) {
                    cout << "Invalid input. Exiting.\n";
                    return 0;
                }
                if (take >= 1 && take <= 4 && take <= matches) {
                    break;
                }
                cout << "Please choose a number between 1 and 4 that does not exceed the remaining matches." << endl;
            }
            matches -= take;
            cout << "You took " << take << " match" << (take == 1 ? "" : "es")
                 << ". Remaining: " << matches << "\n";
            if (matches == 0) {
                cout << "You took the last match and lose.\n";
                cout << "Computer wins!\n";
                break;
            }
        } else {
            int take = (matches - 1) % 5;
            if (take == 0 || take > 4) {
                take = 1;
            }
            if (matches <= 1) {
                take = 1;
            } else if (take >= matches) {
                take = matches - 1;
            }
            matches -= take;
            cout << "Computer takes " << take << " match" << (take == 1 ? "" : "es")
                 << ". Remaining: " << matches << "\n";
            if (matches == 0) {
                cout << "Computer was forced to take the last match and loses.\n";
                cout << "Congratulations!\n";
                break;
            }
        }
        humanTurn = !humanTurn;
    }
    return 0;
}

