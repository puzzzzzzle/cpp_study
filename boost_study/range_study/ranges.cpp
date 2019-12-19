//
// Created by khalidzhang on 2019/12/11.
//

#include "common_includes.h"
#include <boost/range.hpp>
#include <boost/range/as_array.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/any_range.hpp>
#include <boost/range/istream_range.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/adaptors.hpp>

TEST(irange, 1) {
    std::cout << (
            boost::counting_range(0, 10) |
            boost::adaptors::transformed([](int i) -> char { return 'a' + i; })
    );
}