# N-Queens Constraint Puzzle Solver

A C++ console-based mini project that solves the classic N-Queens puzzle using recursive backtracking.

## DSA concepts
- **Backtracking:** place a queen, explore the next row, and undo the placement when needed.
- **Constraint checking:** reject any square sharing a column or diagonal with an earlier queen.
- **Recursion:** each recursive call attempts to place a queen in the next row.
- **Vector:** stores the column selected for the queen in each row.

## Features
1. Choose board size from 4 to 12.
2. Find and display one valid board.
3. Count all valid solutions.
4. Display the current board size.
5. Explain the backtracking method.
6. Validate menu and board-size input.

`Q` means a queen and `.` means an empty square. This program does not require external libraries or a data file.

## Compile and run

### Ubuntu Linux
```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o nqueens_solver
./nqueens_solver
```

### Windows (MinGW-w64)
Open Command Prompt in the project folder:
```bat
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o nqueens_solver.exe
nqueens_solver.exe
```

