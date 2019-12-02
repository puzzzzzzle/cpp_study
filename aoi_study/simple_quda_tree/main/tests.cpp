//
// Created by khalidzhang on 2019/11/29.
//

#include "common_includes.h"
#include "QuadTree.h"



TEST(simple,1){
    int max = 1000;
    vertex origin (0, 0);
    vertex axis (max, max);
    auto qtree = new QuadTree <int> (origin, axis, 1,16);
    INFO("simple Test")

    for(int i=0;i<5;++i){
        vertex newpoint((long double)(rand()%max),(long double)(rand()%max));
        std::cout<<newpoint.x<<","<<newpoint.y<<std::endl;
        qtree->insert(newpoint,1);
    }
    qtree->print(std::cout);
}
