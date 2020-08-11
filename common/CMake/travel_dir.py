# !conding=utf8

import os
import sys
import pathlib
import re
import subprocess

PROTOC = "protoc"


def travel_dir(path: str):
    g = os.walk(path)
    dir_names = []
    proto_names = []
    proto_dirs = set()
    for path, d, file_list in g:
        dir_names.append(os.path.abspath(path))
        for file in file_list:
            if re.search(".*\.proto", file, re.I):
                proto_names.append(os.path.abspath(file))
                proto_dirs.add(os.path.abspath(path))
    return dir_names, proto_names, proto_dirs


def print_path(path_str):
    tmp_path = pathlib.Path(path_str)
    result = tmp_path.as_posix()
    print(f"{result};", end="")


def build_protoc(proto_dirs, proto_file, out_dir):
    print(f"build proto in python : {proto_dirs}   {proto_file}   {out_dir}")
    for build_file in proto_file:
        execute_list = []
        execute_list.append(PROTOC)
        for include_dir in proto_dirs:
            execute_list.append(f"-I={include_dir.replace(';', '')}")
        execute_list.append(f"--cpp_out={out_dir}")
        execute_list.append(f"{build_file}")

        execute_str = f"execute_list"
        print(f"will run cmd :  {execute_str}")
        ret = subprocess.run(execute_list)
        print(f"run result is {str(ret)}")
        if ret.returncode != 0:
            raise Exception(f"execute fail {execute_str}, ret if {str(ret)}")


if __name__ == '__main__':
    dirs, proto_list, proto_dir_set = travel_dir(sys.argv[1])
    operate_type = sys.argv[2].lower()
    if operate_type.lower() == "d":
        for dir_name in dirs:
            print_path(dir_name)
    if operate_type.lower() == "proto":
        for proto in proto_list:
            print_path(proto)
    if operate_type.lower() == "proto_dir":
        for proto_dir in proto_dir_set:
            print_path(proto_dir)
    if operate_type.lower() == "build_proto":
        out_dir = sys.argv[3]
        print(f"build proto {out_dir}")
        out_path = os.path.abspath(out_dir)
        build_protoc(proto_dir_set, proto_list, out_path)
