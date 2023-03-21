from selenium import webdriver
from django.contrib.staticfiles.testing import StaticLiveServerTestCase
import sys
import os
from time import sleep


EXAMPLE_SUDOKU_BOARD = [0, 0, 3, 5, 6, 8, 0, 0, 0,
                        0, 0, 7, 3, 0, 0, 0, 1, 0,
                        0, 0, 0, 0, 9, 7, 0, 0, 6,
                        4, 7, 0, 0, 0, 5, 2, 0, 0,
                        1, 0, 0, 0, 0, 0, 8, 0, 5,
                        0, 0, 0, 0, 0, 0, 4, 0, 7,
                        0, 2, 0, 0, 0, 0, 0, 4, 3,
                        0, 4, 0, 9, 2, 6, 1, 0, 0,
                        8, 9, 0, 0, 0, 3, 0, 0, 0]

RESULT_EXAMPLE = [9, 1, 3, 5, 6, 8, 7, 2, 4,
                  6, 8, 7, 3, 4, 2, 5, 1, 9,
                  2, 5, 4, 1, 9, 7, 3, 8, 6,
                  4, 7, 9, 6, 8, 5, 2, 3, 1,
                  1, 6, 2, 7, 3, 4, 8, 9, 5,
                  5, 3, 8, 2, 1, 9, 4, 6, 7,
                  7, 2, 6, 8, 5, 1, 9, 4, 3,
                  3, 4, 5, 9, 2, 6, 1, 7, 8,
                  8, 9, 1, 4, 7, 3, 6, 5, 2]


class NewVisitorTest(StaticLiveServerTestCase):
    @classmethod
    def setUpClass(cls):
        for arg in sys.argv:
            if 'liveserver' in arg:
                cls.server_ulr = 'http://' + arg.split('=')[1]
                return
        staging_server = os.environ.get('STAGING_SERVER')
        if staging_server:
            cls.server_url = 'http://' + staging_server
            return
        super().setUpClass()
        cls.server_url = cls.live_server_url

    def setUp(self) -> None:
        # self.browsers = (webdriver.Firefox(), webdriver.Chrome(), webdriver.Edge())
        self.browser = webdriver.Firefox()
        # self.browser.implicitly_wait(3)

    def tearDown(self) -> None:
        self.browser.quit()

    # schema of testing
    def test_work_home_page_and_show_info(self):
        # first user visit the home page with information about functionality of this page
        self.browser.get(self.server_url)
        header_text = self.browser.find_element(by="tag name", value="h2").text

        self.assertEqual("Sudoku", self.browser.title, "Wrong title of home page")
        self.assertIn("Znajdujesz się na stronie", header_text, "There is no basic info on the website")

        # he decided to solve his sudoku puzzle and selects this option
        button_solve = self.browser.find_element(by="name", value="solve")
        button_solve.click()

        # he sees new page with empty sudoku board and new title
        user_url = self.browser.current_url
        self.assertRegex(user_url, '/solver/', "Wrong URL for sudoku solver")
        self.assertEqual("Sudoku solver", self.browser.title, "Wrong title of solver page")

        # he inserts his data into board
        input_fields = self.browser.find_elements(by="name", value="sudoku_field")
        self.assertEqual(len(EXAMPLE_SUDOKU_BOARD), len(input_fields),
                         "Lengths of example and input fields are different")
        for field_value in zip(input_fields, EXAMPLE_SUDOKU_BOARD):
            if field_value[1]:
                field_value[0].send_keys(field_value[1])

        # he selects a button solve sudoku
        button_solve = self.browser.find_element(by="name", value="solve")
        self.assertNotEqual(button_solve, "There is no button")
        button_solve.click()

        # he sees solved sudoku
        result_board = self.browser.find_elements(by='tag name', value='td')

        self.assertEqual(result_board, RESULT_EXAMPLE, "Wrong result of Sudoku")
