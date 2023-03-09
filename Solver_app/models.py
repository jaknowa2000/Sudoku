from django.db import models

# Create your models here.


class SudokuBoard(models.Model):
    fields = [models.IntegerField] * 81
