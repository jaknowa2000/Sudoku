from django.shortcuts import render, redirect
from Solver_app.models import SudokuBoard


def home(request):
    return render(request, 'home.html')


def solver(request):
    return render(request, 'solver.html')


def new_sudoku_puzzle(request):
    post_request_list = list(map(int, request.POST.getlist('fields')))
    sudoku_puzzle = SudokuBoard.objects.create(fields=post_request_list)
    return redirect(f'/solver/{sudoku_puzzle.id}/')
