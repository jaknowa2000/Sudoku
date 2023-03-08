from selenium import webdriver
from django.contrib.staticfiles.testing import StaticLiveServerTestCase
import sys
import os
from time import sleep


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

        self.assertIn("Sudoku", self.browser.title, "Wrong title of home page")
        self.assertIn("Znajdujesz się na stronie", header_text, "There is no basic info on the website")

        # he decided to solve his sudoku puzzle and selects this option
        button_solve = self.browser.find_element(by="name", value="solve")
        button_solve.click()

        # he sees new page with empty sudoku board and new title
        user_url = self.browser.current_url
        self.assertRegex(user_url, '/solver/', "Wrong URL for sudoku solver")
        self.assertIn("Solver", self.browser.title, "Wrong title of solver page")
            # how to check whether is there sudoku

        # he inserts his data into board

    # he selects a button solve sudoku

    # he sees solved sudoku
