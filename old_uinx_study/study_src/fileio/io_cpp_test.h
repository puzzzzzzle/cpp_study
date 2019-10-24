//
// Created by tao on 18-11-28.
//

#ifndef UNIXSTUDYCPP_IO_CPP_TEST_H
#define UNIXSTUDYCPP_IO_CPP_TEST_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "people.hpp"
#include "log_macro.h"

#define FILE_NAME "io_temp.data"
#define FILE_NAME_BINARY "io_temp_binary.data"

using namespace std;

void io_cpp_test() {
    People p1("zhang", 20, 80.0);

    //file out txt
    ofstream f_out;
    f_out.open(FILE_NAME, fstream::trunc);
    f_out << p1.to_string() << endl;
    f_out.close();


    //file TXT read
    ifstream f_in(FILE_NAME);
    string word;
    f_in >> word;

    TRACE("word:\t" << word);

    char line[100];

    f_in.getline(line, sizeof(line));

    TRACE("line:\t" << line);

    f_in.seekg(0, ios::beg);

    f_in.getline(line, sizeof(line));

    TRACE("line after seekg:\t" << line);

    f_in.close();


    // binary output

    ofstream bin_f_out;
    bin_f_out.open(FILE_NAME_BINARY, ios::binary | ios::trunc);

    bin_f_out.write((const char *) &p1, sizeof(People));

    bin_f_out.close();

    //binary input

    ifstream bin_f_in;
    bin_f_in.open(FILE_NAME_BINARY, ios::binary);
    People p2;
    bin_f_in.read((char *) &p2, sizeof(People));
    TRACE("read from binary :\t" << p2.to_string());
    bin_f_in.close();
}

#endif //UNIXSTUDYCPP_IO_CPP_TEST_H
