#include <bits/stdc++.h>

int main() {
    std::string line;
    std::getline(std::cin, line);
    if (line.empty() && std::cin.good()) {
        std::getline(std::cin, line);
    }
    std::stack<char> st;
    auto match = [](char open, char close) {
        return (open == '(' && close == ')') ||
               (open == '[' && close == ']') ||
               (open == '{' && close == '}');
    };
    for (char ch : line) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (st.empty() || !match(st.top(), ch)) {
                std::cout << "No" << '\n';
                return 0;
            }
            st.pop();
        }
    }
    std::cout << (st.empty() ? "Yes" : "No") << '\n';
    return 0;
}
