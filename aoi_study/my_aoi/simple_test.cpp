//
// Created by khalidzhang on 2019/12/2.
//

#include "AbstractAoi.h"
#include "common_includes.h"
#include "OrthogonalListAoi.hpp"

typedef OrthogonalListAoi<int, int, false> AOI;
typedef AOI::Node Node;
TEST(zero, zero)
{
    INFO("zero:" << 0)
    ASSERT_EQ(0, 0);
}
//std::ostream& operator<<(std::ostream &oss,std::pair<const Node*,false> & node){
//    oss<<*(node.first);
//}
TEST(OrthogonalListAoi, 1)
{

    const int max = 100;
    AOI aoi;
    for (int i = 0; i < 10; ++i)
    {
        Node node;
//        node.point.x = rand()%max;
//        node.point.y = rand()%max;
        node.point.x = 10+i;
        node.point.y = 11+i;
        node.obj = 5 + i;
        aoi.Add(node);
    }
    aoi.Print(std::cout);
    auto find = aoi.QueryInsidespace(10,10,30,30);
    for(auto it : find){
        std::cout << "{" << *(it.first) << "} -> ";
    }
    std::cout<<"end\n";

    aoi.Move(find[0].first,{8,8});
    aoi.Print(std::cout);

    find = aoi.QueryInsidespace(10,10,30,30);
    aoi.Leave(find[0].first,true);
    aoi.Print(std::cout);

    find = aoi.QueryInsidespace(10,10,30,30);
    aoi.Print(std::cout);
    find = aoi.QueryInsideRegion(find[0].first,5,5);
    for(auto it : find){
        std::cout << "{" << *(it.first) << "} -> ";
    }
    std::cout<<"end\n";

}

