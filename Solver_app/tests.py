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

    def test_board_can_fetch_and_save_elements_in_fields(self):
        sudoku_board = SudokuBoard()
        sudoku_board_example = [i for i in range(1, 10)] + [i for i in range(9, 0, -1)] + [7] * 9
        sudoku_board_example *= 3
        sudoku_board.fields = sudoku_board_example
        sudoku_board.save()
        saved_sudoku_board = SudokuBoard.objects.first()
        self.assertEqual(saved_sudoku_board.fields, sudoku_board.fields)
        self.assertEqual(saved_sudoku_board.fields, sudoku_board_example)


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
        sudoku_board_example = [i for i in range(1, 10)] + [i for i in range(9, 0, -1)] + [7] * 9
        sudoku_board_example *= 3
        sudoku_board_data = {'sudoku_field': sudoku_board_example}

        response = self.client.post(f'/solver/new', data=sudoku_board_data)
        new_board = SudokuBoard.objects.first()

        self.assertRedirects(response, f'/solver/{new_board.id}/')

