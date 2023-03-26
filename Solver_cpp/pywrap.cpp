#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>

#include "sudoku_board.h"


namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MODULE(solver, m) {
    m.doc() = "Module for solving Sudoku Puzzle";

    m.def("solve_sudoku", &fun_solve_sudoku);
}