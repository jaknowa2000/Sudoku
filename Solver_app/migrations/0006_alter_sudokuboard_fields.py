# Generated by Django 4.1.7 on 2023-03-13 08:06

import Solver_app.models
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Solver_app', '0005_alter_sudokuboard_fields'),
    ]

    operations = [
        migrations.AlterField(
            model_name='sudokuboard',
            name='fields',
            field=models.JSONField(default=Solver_app.models.get_default_data),
        ),
    ]
