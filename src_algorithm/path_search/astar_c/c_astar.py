import os
from ctypes import *
import platform
import cv2
import logging
import array

if platform.system() == "Windows":
    # windows
    dll_path = f"{os.path.abspath(os.path.dirname(os.path.abspath(__file__)))}/c_src/shared_lib/astar_ctype_bind_win_x64.dll"
    dll = WinDLL(dll_path)
else:
    raise RuntimeError(f"not support this platform {platform.system()}")


class AstarPoint(Structure):
    _fields_ = [("x", c_int),
                ("y", c_int),
                ]


class AstarResult(Structure):
    _fields_ = [("result", c_int),
                ("len", c_int),
                ("path", POINTER(AstarPoint)),
                ]


version_info = dll.version_info
version_info.restype = c_char_p
version_info.argtypes = []

astar_new = dll.astar_new
astar_new.restype = c_void_p
astar_new.argtypes = [c_int32, c_int32, POINTER(c_ubyte)]

astar_delete = dll.astar_delete
astar_delete.restype = None
astar_delete.argtypes = [c_void_p]

astar_dump_map = dll.astar_dump_map
astar_dump_map.restype = c_char_p
astar_dump_map.argtypes = [c_void_p]

astar_search = dll.astar_search
astar_search.restype = AstarResult
astar_search.argtypes = [c_void_p, AstarPoint, AstarPoint]

astar_free_result = dll.astar_free_result
astar_free_result.restype = None
astar_free_result.argtypes = [AstarResult]


class AstarSearchFail(Exception):
    pass


class Astar:
    def __init__(self, width: int, height: int, arr: POINTER(c_ubyte)):
        self.handle = astar_new(width, height, arr)
        pass

    def __del__(self):
        astar_delete(self.handle)

    def dump_map(self):
        c_str = astar_dump_map(self.handle)
        return c_str.decode("utf-8")

    def search(self, src_x, src_y, end_x, end_y):
        src = AstarPoint()
        src.x = src_x
        src.y = src_y
        dest = AstarPoint()
        dest.x = end_x
        dest.y = end_y
        astar_ret = astar_search(self.handle, src, dest)
        if astar_ret.result != 0:
            raise AstarSearchFail("path search fail")
        path = []
        for i in range(astar_ret.len):
            p = astar_ret.path[i]
            path.append((p.x, p.y))
        astar_free_result(astar_ret)
        return path
        pass


if __name__ == '__main__':
    import time

    rate = 100
    arr_len = 10 * rate
    arr = bytearray(b'\x01') * (arr_len ** 2)
    for i in range(arr_len):
        arr[3 * rate * arr_len + i] = 0
    raw_bytes = (c_ubyte * len(arr)).from_buffer_copy(arr)
    astar = Astar(arr_len, arr_len, raw_bytes)
    print(astar.dump_map())


    def search(src_x, src_y, end_x, end_y):
        start_time = time.time()
        success = True
        try:
            ret = astar.search(src_x, src_y, end_x, end_y)
        except AstarSearchFail as e:
            ret = []
            success = False
            pass
        end_time = time.time()
        print(f"{(src_x, src_y)} -> {(end_x, end_y)}, success:{success}, time: {end_time - start_time}s, path: {ret}")
        print()


    search(0, 0, 2 * rate, 2 * rate)
    search(0, 0, 9 * rate, 9 * rate)

    pass
