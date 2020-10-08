//
// Created by tao on 18-11-28.
//

#ifndef UNIXSTUDYCPP_PEOPLE_HPP
#define UNIXSTUDYCPP_PEOPLE_HPP

#include <string>

using namespace std;
class People {
  public:
  People() = default;

  People(const std::string &name, const int &age, const double &score) {
    this->name = name;
    this->age = age;
    this->score = score;
  }

  public:
  std::string name;
  int age;
  double score;

  public:
  //右值引用如何返回？？ 还有问题，不能使用！！！
  std::string &&to_string_r() {
    string result =
        "" + name + "\t" + std::to_string(age) + "\t" + std::to_string(score);
    return std::move(result);
  }

  std::string to_string() {
    string result =
        "" + name + "\t" + std::to_string(age) + "\t" + std::to_string(score);
    return result;
  }

  //    int &&get_temp(){
  //        return 0;
  //    }
};

#endif  // UNIXSTUDYCPP_PEOPLE_HPP
