#include <pybind11/pybind11.h>

#include "sudoku_board.h"


namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MODULE(MyLib, m) {
    m.doc() = "Module for solving Sudoku Puzzle";

    m.def("solve_sudoku", &dudu, "aa");
}