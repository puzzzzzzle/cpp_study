//
// Created by tao on 18-11-25.
//

#ifndef UNIXSTUDYCPP_ARR_TEST_HPP
#define UNIXSTUDYCPP_ARR_TEST_HPP

#include <array>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <netinet/in.h>
#include "log_macro.h"

using namespace std;

namespace tao_stl {

//    template<typename _RAIter, typename _Compare>
//    void
//    m_sort(_RAIter l, _RAIter r, _Compare c){
//        _RAIter tmp = l;
//        while (tmp!=r){
//            TRACE(*tmp)
//            tmp++;
//        }
//    }

    void test_arr() {
        std::array<int, 100> l_arr0;//没有初始化
        std::array<int, 100> l_arr1{};//初始化为0

        auto ap_arr2 = make_shared<array<int, 42>>();
        auto ap_arr3 = make_shared<array<int, 42>>();


        std::cout << l_arr0.begin() << std::endl;
//        print_it(l_arr0.begin(),l_arr0.end());
        printf("arr test end!\n");
    }


    static int m_cmp(char a, char b){
        TRACE(to_string(a)<<"\t?\t"<<to_string(b));
        return a<b;
    }
    void test_sort() {
        vector<char> v1;
        v1.push_back('a');
        v1.push_back('b');
        v1.push_back('c');
        v1.insert(v1.cbegin(),'0');
        vector<char>::iterator b = v1.begin();
        sort(v1.begin(),v1.end(),m_cmp);
//        m_sort(v1.begin(),v1.end(),m_cmp);
    }

}


#endif //UNIXSTUDYCPP_ARR_TEST_HPP
