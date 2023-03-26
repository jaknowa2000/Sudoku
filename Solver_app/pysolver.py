import sys
sys.path.append('Solver_cpp/build/')
from solver import solve_sudoku


def solve(sudoku_puzzle):
    if len(sudoku_puzzle) == 81:
        return solve_sudoku(sudoku_puzzle)
    else:
        raise ValueError("Invalid length of sudoku_puzzle")

