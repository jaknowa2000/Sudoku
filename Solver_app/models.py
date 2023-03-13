from django.db import models

# Create your models here.


def get_default_data():
    return [0] * 81


class SudokuBoard(models.Model):
    fields = models.JSONField(default=get_default_data)
