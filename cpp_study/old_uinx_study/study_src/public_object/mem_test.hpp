//
// Created by tao on 18-11-30.
//

#ifndef UNIXSTUDYCPP_MEM_TEST_HPP
#define UNIXSTUDYCPP_MEM_TEST_HPP

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#define NAME_LENGTH 100

class null_class {};
class char_people {
private:
    char name[NAME_LENGTH];

public:
    char_people() = default;

    char_people(const char *const _name) { strncpy(this->name, _name, NAME_LENGTH); }
};

class str_people {
private:
    string name;

public:
    str_people() = default;

    str_people(const string &_name) { this->name = _name; }
};

int mem_test_main() {
    cout << "null:\t" << sizeof(null_class) << endl;
    cout << "char:\t" << sizeof(char_people) << endl;
    cout << "str:\t" << sizeof(str_people) << endl;
    char_people cp("tao");
    str_people  sp(
        "taosssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
        "ss"
        "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");
    cout << "char:\t" << sizeof(cp) << endl;
    cout << "str:\t" << sizeof(sp) << endl;
    cout << "string:\t" << sizeof(string) << endl;
    return 0;
}

#endif  // UNIXSTUDYCPP_MEM_TEST_HPP
