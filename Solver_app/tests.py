from django.test import TestCase
from Solver_app.models import SudokuBoard
from functional_tests.tests import EXAMPLE_SUDOKU_BOARD, RESULT_EXAMPLE


class HomePageTest(TestCase):
    def test_uses_home_template(self):
        response = self.client.get('/')
        self.assertTemplateUsed(response, 'home.html')


class SolverPageTest(TestCase):
    def test_uses_solver_template(self):
        response = self.client.get('/solver/')
        self.assertTemplateUsed(response, 'solver.html')


class SolvedPageTest(TestCase):
    def test_uses_solver_template(self):
        board = SudokuBoard.objects.create(fields=EXAMPLE_SUDOKU_BOARD)
        self.response = self.client.get(f'/solver/{board.id}/')
        self.assertTemplateUsed(self.response, 'solved.html')


class SudokuBoardModelTest(TestCase):
    def test_board_has_81_fields(self):
        sudoku_board = SudokuBoard()
        self.assertEqual(len(sudoku_board.fields), 81, "Wrong number of sudoku fields")

    def test_board_can_get_elements(self):
        sudoku_board = SudokuBoard()
        sudoku_board.fields = EXAMPLE_SUDOKU_BOARD
        sudoku_board.save()
        saved_sudoku_board = SudokuBoard.objects.first()
        self.assertEqual(saved_sudoku_board.fields, sudoku_board.fields)

    def test_board_has_solved_sudoku(self):
        sudoku_board = SudokuBoard(fields=EXAMPLE_SUDOKU_BOARD)
        self.assertEqual(sudoku_board.fields, RESULT_EXAMPLE)

    def test_board_has_only_values_from_range_1_9(self):
        sudoku_board = SudokuBoard(fields=EXAMPLE_SUDOKU_BOARD)
        self.assertEqual(self.is_list_with_values_from_range_1_9(sudoku_board.fields), True,
                         "Board fields have wrong values")

    @staticmethod
    def is_list_with_values_from_range_1_9(list_):
        for val in list_:
            if val not in range(1, 10):
                return False
        return True


class NewSodokuBoardTest(TestCase):
    def test_can_save_POST_request(self):
        sudoku_board_example = [i for i in range(1, 10)] + [i for i in range(9, 0, -1)] + [7] * 9
        sudoku_board_example *= 3
        sudoku_board_data = {'sudoku_field': sudoku_board_example}

        self.client.post('/solver/new', data=sudoku_board_data)

        self.assertEqual(SudokuBoard.objects.count(), 1, "The board didn't crate")
        new_sudoku_board = SudokuBoard.objects.first()
        self.assertEqual(new_sudoku_board.fields, sudoku_board_example)

    def test_redirect_to_solved_view(self):
        sudoku_board_data = {'sudoku_field': EXAMPLE_SUDOKU_BOARD}

        response = self.client.post(f'/solver/new', data=sudoku_board_data)
        new_board = SudokuBoard.objects.first()

        self.assertRedirects(response, f'/solver/{new_board.id}/')

