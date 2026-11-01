    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <string>
    #include <vector>
    #ifdef _WIN32
    #include <windows.h>
    #endif
    using namespace std;

    const int WIDTH = 68;
    void enableColors() {
    #ifdef _WIN32
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h != INVALID_HANDLE_VALUE) {
            DWORD mode = 0;
            if (GetConsoleMode(h, &mode)) SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    #endif
    }
    void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[H";
    #endif
    }
    void line(char c='=') { cout << "+" << string(WIDTH-2, c) << "+\n"; }
    void boxText(const string& s) {
        int n = (int)s.size();
        if (n > WIDTH-4) { cout << "| " << s.substr(0, WIDTH-4) << " |\n"; return; }
        int left = (WIDTH-2-n)/2, right = WIDTH-2-n-left;
        cout << "|" << string(left, ' ') << s << string(right, ' ') << "|\n";
    }
    void pauseScreen() { cout << "\nPress Enter to continue..."; string dummy; getline(cin, dummy); }
    int readInt(const string& prompt, int low, int high) {
        while (true) {
            cout << prompt;
            string s; getline(cin, s);
            stringstream ss(s); int x; char extra;
            if (ss >> x && !(ss >> extra) && x >= low && x <= high) return x;
            cout << "\033[31mInvalid input. Enter a number from " << low << " to " << high << ".\033[0m\n";
        }
    }

    class NQueensSolver {
        int n;
        vector<int> queenColumn;
        vector<int> firstSolution;
        long long solutionCount;
        bool showFirst;

        // A placement is safe when no earlier queen shares its column or diagonal.
        bool isSafe(int row, int col) const {
            for (int previousRow = 0; previousRow < row; ++previousRow) {
                int previousCol = queenColumn[previousRow];
                if (previousCol == col) return false;
                if (previousRow - previousCol == row - col) return false;
                if (previousRow + previousCol == row + col) return false;
            }
            return true;
        }
        void backtrack(int row) {
            if (row == n) {
                ++solutionCount;
                if (firstSolution.empty()) firstSolution = queenColumn;
                return;
            }
            for (int col = 0; col < n; ++col) {
                if (isSafe(row, col)) {
                    queenColumn[row] = col;
                    backtrack(row + 1);
                    queenColumn[row] = -1;
                }
            }
        }
    public:
        explicit NQueensSolver(int size) : n(size), queenColumn(size, -1), solutionCount(0), showFirst(false) {}
        void solve() {
            fill(queenColumn.begin(), queenColumn.end(), -1);
            firstSolution.clear();
            solutionCount = 0;
            backtrack(0);
        }
        long long count() const { return solutionCount; }
        void displayFirstSolution() const {
            if (firstSolution.empty()) {
                cout << "\033[31mNo solution exists for N = " << n << ".\033[0m\n";
                return;
            }
            cout << "\nFirst valid arrangement (Q = queen, . = empty):\n\n   ";
            for (int c=0; c<n; ++c) cout << setw(2) << c+1 << " ";
            cout << "\n";
            for (int r=0; r<n; ++r) {
                cout << setw(2) << r+1 << " ";
                for (int c=0; c<n; ++c) {
                    if (firstSolution[r] == c) cout << "\033[33m Q \033[0m";
                    else cout << " . ";
                }
                cout << "\n";
            }
        }
        void showRules() const {
            line(); boxText("HOW BACKTRACKING WORKS"); line('-');
            boxText("Place one queen in each row.");
            boxText("Reject a position if a column or diagonal is occupied.");
            boxText("If no position works, return to the previous row.");
            boxText("Continue until every row has a queen.");
            line();
            cout << "\nA solution has exactly N queens, with no shared row, column,\n"
                << "or diagonal. The search tries valid columns recursively.\n";
        }
    };

    void welcome() {
        clearScreen(); line();
        boxText("N-QUEENS CONSTRAINT PUZZLE SOLVER"); boxText("C++ DSA MINI PROJECT");
        line(); boxText("Backtracking and Constraint Checking");
        line(); cout << "\nPreparing solver ";
        for (int i=0; i<5; ++i) cout << "\033[36m.\033[0m" << flush;
        cout << "\n\n";
    }
    void menu() {
        line(); boxText("MAIN MENU"); line('-');
        boxText("1. Set board size (N)");
        boxText("2. Find and display a solution");
        boxText("3. Count all solutions");
        boxText("4. Show current board size");
        boxText("5. Explain the algorithm");
        boxText("0. Exit");
        line();
    }
    int main() {
        enableColors();
        welcome();
        int n = 8;
        cout << "Default board size: 8 x 8\n";
        pauseScreen();
        while (true) {
            clearScreen(); menu();
            int choice = readInt("Select an option: ", 0, 5);
            clearScreen();
            if (choice == 0) {
                cout << "\033[32mSolver closed. Thank you!\033[0m\n";
                break;
            }
            if (choice == 1) {
                n = readInt("Enter N (4 to 12): ", 4, 12);
                cout << "\033[32mBoard size set to " << n << " x " << n << ".\033[0m\n";
            } else if (choice == 2) {
                NQueensSolver solver(n);
                solver.solve();
                cout << "Board size: " << n << " x " << n << "\n";
                solver.displayFirstSolution();
                cout << "Total valid solutions: " << solver.count() << "\n";
            } else if (choice == 3) {
                NQueensSolver solver(n);
                cout << "Counting solutions for N = " << n << "...\n";
                solver.solve();
                cout << "\033[32mTotal valid solutions: " << solver.count() << "\033[0m\n";
                cout << "Note: counting all solutions takes longer for larger N.\n";
            } else if (choice == 4) {
                cout << "Current board size: " << n << " x " << n << "\n";
            } else {
                NQueensSolver solver(n);
                solver.showRules();
            }
            pauseScreen();
        }
        return 0;
    }
