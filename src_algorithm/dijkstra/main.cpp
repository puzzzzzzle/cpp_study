//
// Created by tao on 19-1-17.
//

#include "common_includes.h"
#include "path_search/path_find_common.h"

enum VertexTypeEnum {
  VERTEX_TYPE_UNKNOWN = 0,
  VERTEX_TYPE_AREA = 1,
  VERTEX_TYPE_COL = 2,
};

#include "DynamicMatrix.h"
using namespace Dijkstra;

TEST(enum, 1) {
  LOG_DEBUG("\t" << INT_INF << "\t" << LEN_UNDEFINED)
  ASSERT_EQ(INT_INF, std::numeric_limits<int>::max());
  ASSERT_EQ(LEN_UNDEFINED, -100);
}

class DijkstraTestBase : public testing::Test {
  protected:
  std::shared_ptr<DynamicDijkstra::VertexType> vexArrPtr;
  std::shared_ptr<DynamicDijkstra::MatrixType> matrixArrPtr;
    std::shared_ptr<DynamicDijkstra> dijkstraPtr{};
  void SetUp() override {
#include "temp_init.inc"
    vexArrPtr = std::make_shared<DynamicDijkstra::VertexType>(vexArr);
    matrixArrPtr = std::make_shared<DynamicDijkstra::MatrixType>(matrixArr);
    dijkstraPtr = std::make_shared<DynamicDijkstra>(*vexArrPtr);
  }
  void TearDown() override {}

  int ColPathFindPlan(const Point2d& start, int fromIndex, const Point2d& end,
                      int targetIndex, const std::vector<int>& openGate,
                      std::vector<DijkstraResultType>* result) {
    // 进行动态修正并初始化关隘与区域间的连接
    DynamicDijkstra ::MatrixType outMatrix(matrixArrPtr->m_raw,
                                           matrixArrPtr->m_col);
    CALL_IF_TRUE_RETURN(DynamicMatrixHelper::DynamicCalc(
        *vexArrPtr, *matrixArrPtr, fromIndex, start, targetIndex, end, openGate,
        &outMatrix))
    LOG_DEBUG("after dynamic operate matrix \n" << outMatrix.ToString())
    // 进行最短路径查找
    CALL_IF_TRUE_RETURN(
        dijkstraPtr->dijkstra(fromIndex, result, outMatrix, targetIndex))
    CALL_IF_TRUE_RETURN(result->size() != 1)
    CALL_IF_TRUE_RETURN((*result)[0].m_shortestPath.empty())
    LOG_DEBUG("dijkstra result is "
                << (*result)[0].ToString("\t", &dijkstraPtr->m_vertex))
    return 0;
  }
};
TEST_F(DijkstraTestBase, print) {
  vexArrPtr->Print();
  matrixArrPtr->Print();
}
TEST_F(DijkstraTestBase, find1) {}

int main(int argc, char** argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}