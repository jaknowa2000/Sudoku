from django.test import TestCase


class HomePageTest(TestCase):
    def test_uses_home_template(self):
        response = self.client.get('/')
        self.assertTemplateUsed(response, 'home.html')


class SolverPageTest(TestCase):
    def test_uses_solver_template(self):
        response = self.client.get('/solver/')
        self.assertTemplateUsed(response, 'solver.html')
