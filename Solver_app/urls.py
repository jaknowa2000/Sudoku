from django.urls import path, include
from . import views

app_name = 'Solver_app'

urlpatterns = [
    path('', views.solver, name='solver')
]
