from django.test import TestCase
from Solver_app.models import SudokuBoard


class HomePageTest(TestCase):
    def test_uses_home_template(self):
        response = self.client.get('/')
        self.assertTemplateUsed(response, 'home.html')


class SolverPageTest(TestCase):
    def test_uses_solver_template(self):
        response = self.client.get('/solver/')
        self.assertTemplateUsed(response, 'solver.html')


class SudokuBoardModelTest(TestCase):
    def test_board_has_81_fields(self):
        sudoku_board = SudokuBoard()
        self.assertEqual(len(sudoku_board.fields), 81, "Wrong number of sudoku fields")

    def test_board_can_can_fetch_and_save_elements_in_fields(self):
        sudoku_board = SudokuBoard()
        sudoku_board_example = [[i for i in range(10)] + [i for i in range(9, 0, -1)] + [7] * 9] * 3
        for index, value in enumerate(sudoku_board_example):
            sudoku_board.fields[index] = value
        sudoku_board.save()
        saved_sudoku_board = SudokuBoard.objects.first()
        self.assertEqual(saved_sudoku_board.fields, sudoku_board.fields)

