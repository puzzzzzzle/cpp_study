//
// Created by khalidzhang on 2019/12/2.
//

#include "../tower_aoi/tower_aoi.h"
#include "AbstractAoi.h"
#include "OrthogonalListAoi.hpp"
#include "common_includes.h"
#define INFO(msg) LOG_DEBUG(msg)
typedef OrthogonalListAoi<int, int, false> AOI;
typedef AOI::Node Node;
TEST(zero, zero) {
  INFO("zero:" << 0)
  ASSERT_EQ(0, 0);
}
// std::ostream& operator<<(std::ostream &oss,std::pair<const Node*,false> &
// node){
//    oss<<*(node.first);
//}
void printV(std::ostream &oss, std::vector<std::pair<Node *, bool>> &find) {
  std::cout << "{ ";
  for (auto it : find) {
    std::cout << *(it.first) << " } , s: " << it.second << " } -> ";
  }
  std::cout << "} end" << std::endl;
}
TEST(OrthogonalListAoi, 1) {
  //    const int max = 100;
  AOI aoi;
  for (int i = 0; i < 100; ++i) {
    Node node;
    //        node.point.x = rand()%max;
    //        node.point.y = rand()%max;
    node.point.x = 10 + i;
    node.point.y = 11 + i;
    node.point.halfXLen = 5;
    node.point.halfYLen = 5;

    node.obj = 5 + i;
    aoi.Add(node);
  }
  aoi.Print(std::cout);
  auto find = aoi.QueryInsidespace(10, 10, 5, 5);
  printV(std::cout, find);

  aoi.Move(find[0].first, {8, 8});
  aoi.Print(std::cout);

  find = aoi.QueryInsidespace(0, 0, 100, 100);
  aoi.Print(std::cout);
  find = aoi.QueryInsideRegion(find[3].first, 5, 5);
  printV(std::cout, find);
}
