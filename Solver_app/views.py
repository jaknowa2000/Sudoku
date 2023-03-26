from django.shortcuts import render, redirect
from Solver_app.models import SudokuBoard
from Solver_app.pysolver import solve


def home(request):
    return render(request, 'home.html')


def solver(request):
    return render(request, 'solver.html')


def new_sudoku_puzzle(request):
    post_request_list = list(map(lambda x: int(x) if x else 0, request.POST.getlist('sudoku_field')))
    solved_puzzle = solve(post_request_list)
    sudoku_puzzle = SudokuBoard.objects.create(fields=solved_puzzle)
    return redirect(f'/solver/{sudoku_puzzle.id}/')


def solved_board(request, board_id):
    puzzle = SudokuBoard.objects.get(id=board_id)
    return render(request, 'solved.html', {'board': puzzle})
