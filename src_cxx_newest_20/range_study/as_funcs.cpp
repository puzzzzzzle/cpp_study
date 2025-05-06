//
// Created by khalidzhang on 2019/12/11.
//

#include <boost/range.hpp>
#include <boost/range/as_array.hpp>
#include <boost/range/as_literal.hpp>
#include <vector>

#include "common_includes.h"

const char *const csptr = "csptr";
const char csarr[] = "csarr";
const int caarr[]{0, 1, 2, 3, 4};
const int *cparr = new int[5]{0, 1, 2, 3, 4};

TEST(as_arr, row) {
  //    EXPECT_EQ(boost::size(csptr),strlen(csptr));      //compile wrong
  //    EXPECT_EQ(boost::size(csarr),strlen(csarr));        //wrong
  EXPECT_EQ(boost::size(caarr), sizeof(caarr) / sizeof(caarr[0]));
  LOG_INFO("based on system, this size of ptr/sizeof(int) "
       << (sizeof(cparr) / sizeof(cparr[0])))
}

TEST(as_arr, as_arr) {  // used for arr that can get size
                        //    EXPECT_EQ(boost::size(boost::as_array(csptr)),strlen(csptr));
                        //    //compile wrong
                        //    EXPECT_EQ(boost::size(boost::as_array(csarr)),strlen(csarr));
                        //    //wrong
  EXPECT_EQ(boost::size(boost::as_array(caarr)),
            sizeof(caarr) / sizeof(caarr[0]));
}

TEST(as_literal, literal) {  // used for str
  EXPECT_EQ(boost::size(boost::as_array(boost::as_literal(csptr))),
            strlen(csptr));
  EXPECT_EQ(boost::size(boost::as_array(boost::as_literal(csarr))),
            strlen(csarr));
}