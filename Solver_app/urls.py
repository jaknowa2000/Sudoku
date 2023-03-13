from django.urls import path, include
from . import views

app_name = 'Solver_app'

urlpatterns = [
    path('', views.solver, name='solver'),
    path('new', views.new_sudoku_puzzle, name='new_sudoku_puzzle'),
    path('<str:board_id>/', views.solved_board, name='solved_board'),
]
