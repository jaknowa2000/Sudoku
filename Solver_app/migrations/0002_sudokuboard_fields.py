# Generated by Django 4.1.7 on 2023-03-12 21:54

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Solver_app', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='sudokuboard',
            name='fields',
            field=models.JSONField(default=[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]),
        ),
    ]
