#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;

struct Piece {
    int row;
    int col;
    bool prefersBlack;
};

bool isBlackSquare(int row, int col) {
    return (row + col) % 2 == 0;
}

vector<pair<int, int>> legalMoves(const Piece &piece) {
    vector<pair<int, int>> options;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) {
                continue;
            }
            int nr = piece.row + dr;
            int nc = piece.col + dc;
            if (nr < 0 || nr >= 7 || nc < 0 || nc >= 7) {
                continue;
            }
            bool black = isBlackSquare(nr, nc);
            if ((piece.prefersBlack && black) || (!piece.prefersBlack && !black)) {
                options.push_back({nr, nc});
            }
        }
    }
    return options;
}

bool areAdjacent(const Piece &a, const Piece &b) {
    int dr = a.row - b.row;
    if (dr < 0) {
        dr = -dr;
    }
    int dc = a.col - b.col;
    if (dc < 0) {
        dc = -dc;
    }
    return dr <= 1 && dc <= 1 && (dr > 0 || dc > 0);
}

int main() {
    Piece a{};
    Piece b{};

    cout << "Enter the starting row and column for A (0-6 0-6): ";
    if (!(cin >> a.row >> a.col)) {
        cout << "Invalid input.\n";
        return 0;
    }
    cout << "Enter the starting row and column for B (0-6 0-6): ";
    if (!(cin >> b.row >> b.col)) {
        cout << "Invalid input.\n";
        return 0;
    }

    if (a.row < 0 || a.row >= 7 || a.col < 0 || a.col >= 7 ||
        b.row < 0 || b.row >= 7 || b.col < 0 || b.col >= 7) {
        cout << "Positions must stay inside the 7x7 board.\n";
        return 0;
    }

    a.prefersBlack = true;
    b.prefersBlack = false;

    if (!isBlackSquare(a.row, a.col)) {
        cout << "A must start on a black square (row + col even).\n";
        return 0;
    }
    if (isBlackSquare(b.row, b.col)) {
        cout << "B must start on a white square (row + col odd).\n";
        return 0;
    }

    random_device rd;
    mt19937 gen(rd());

    int step = 0;
    cout << "Step " << step << ": A(" << a.row << ", " << a.col << ")  B(" << b.row << ", " << b.col << ")\n";

    while (!areAdjacent(a, b)) {
        vector<pair<int, int>> nextA = legalMoves(a);
        if (!nextA.empty()) {
            uniform_int_distribution<size_t> pickA(0, nextA.size() - 1);
            auto choice = nextA[pickA(gen)];
            a.row = choice.first;
            a.col = choice.second;
        }

        vector<pair<int, int>> nextB = legalMoves(b);
        if (!nextB.empty()) {
            uniform_int_distribution<size_t> pickB(0, nextB.size() - 1);
            auto choice = nextB[pickB(gen)];
            b.row = choice.first;
            b.col = choice.second;
        }

        ++step;
        cout << "Step " << step << ": A(" << a.row << ", " << a.col
             << ")  B(" << b.row << ", " << b.col << ")\n";
    }

    cout << "A and B are now adjacent. Meeting condition reached.\n";
    return 0;
}

