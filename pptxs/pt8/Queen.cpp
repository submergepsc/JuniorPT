#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<int> &positions, int row, int col) {
    for (int prevRow = 0; prevRow < row; ++prevRow) {
        int prevCol = positions[prevRow];
        if (prevCol == col) {
            return false;
        }
        int rowDiff = row - prevRow;
        if (prevCol + rowDiff == col || prevCol - rowDiff == col) {
            return false;
        }
    }
    return true;
}

void printBoard(const vector<int> &positions, int solutionIndex) {
    cout << "Solution " << solutionIndex << ":\n";
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (positions[row] == col) {
                cout << 'Q';
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

void solveQueens(int row, vector<int> &positions, int &solutionCount) {
    if (row == 8) {
        ++solutionCount;
        printBoard(positions, solutionCount);
        return;
    }
    for (int col = 0; col < 8; ++col) {
        if (isSafe(positions, row, col)) {
            positions[row] = col;
            solveQueens(row + 1, positions, solutionCount);
        }
    }
}

int main() {
    vector<int> positions(8, -1);
    int solutionCount = 0;
    solveQueens(0, positions, solutionCount);
    cout << "Total solutions: " << solutionCount << "\n";
    return 0;
}

