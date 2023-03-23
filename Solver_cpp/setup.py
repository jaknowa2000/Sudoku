import ctypes
import ctypes as cts
import sys

import nt

def set_up():
    #sudoku_library = ctypes.WinDLL("sudokuLib.so", winmode=0)
    #arr = sudoku_library.getArray()
    #print(arr)

    DLL_NAME = "./sudokuLib.{:s}".format("dll" if sys.platform[:3].lower() == "win" else "so")


    dll = cts.WinDLL(DLL_NAME)
    print(dll.getArray())

set_up()