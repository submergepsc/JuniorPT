#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string line;
    getline(cin, line);
    if (line.empty() && cin.good()) {
        getline(cin, line);
    }
    stack<char> st;
    for (char ch : line) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (st.empty()) {
                cout << "No" << '\n';
                return 0;
            }
            char open = st.top();
            bool ok = (open == '(' && ch == ')') ||
                      (open == '[' && ch == ']') ||
                      (open == '{' && ch == '}');
            if (!ok) {
                cout << "No" << '\n';
                return 0;
            }
            st.pop();
        }
    }
    cout << (st.empty() ? "Yes" : "No") << '\n';
    return 0;
}
