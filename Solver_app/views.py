from django.shortcuts import render


def home(request):
    return render(request, 'home.html')


def solver(request):
    return render(request, 'solver.html')
