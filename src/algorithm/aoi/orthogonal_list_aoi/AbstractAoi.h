/********************************************************************

 * @time 2019/12/2 : 14:13
 * @version 1.0
 * @author khalidzhang
 * @e-mail khalidzhang@tencent.com
 * @description: 2纬aoi基类,demo版，不负责内存管理，指针最好用sharepointer
 *
 ********************************************************************/
#include <iostream>
#include <vector>

#include "stdio.h"

#ifndef CPP_STUDY_ALL_ABSTRACT_AOI_H
#define CPP_STUDY_ALL_ABSTRACT_AOI_H

template <typename NumberT>
class IPoint {
  public:
  typedef NumberT Number;

  public:
  Number x;
  Number y;
  Number halfXLen;
  Number halfYLen;
};

template <typename NumberT, typename ObjectT, bool AutoDelete>
class IBaseNode {
  public:
  typedef NumberT Number;
  typedef ObjectT Object;

  public:
  IPoint<NumberT> point;
  Object obj;

  public:
  friend std::ostream &operator<<(std::ostream &oss, const IBaseNode &node) {
    oss << node.obj << ":{p:[" << node.point.x << "," << node.point.y << "],r:["
        << node.point.halfXLen << "," << node.point.halfYLen << "]}";
    return oss;
  }
};

template <typename NumberT, typename ObjectT, typename Node, bool AutoDelete>
class IAoi {
  public:
  typedef NumberT Number;
  typedef ObjectT Object;
  typedef IPoint<NumberT> Point;
  typedef IBaseNode<NumberT, ObjectT, AutoDelete> BaseNode;

  public:
  virtual bool Add(const BaseNode &object) = 0;

  virtual bool Move(Node *pnode, const Point &point) = 0;

  virtual bool Leave(Node *pnode, bool autoDelete = true) = 0;

  // todo change to iterator
  virtual std::vector<std::pair<Node *, bool>> QueryInsideRegion(
      Node *pnode, NumberT xSize, NumberT ySize) = 0;
  virtual std::vector<std::pair<Node *, bool>> QueryInsidespace(
      NumberT xStart, NumberT yStart, NumberT xSize, NumberT ySize) = 0;

  //    virtual int GetSize() const;
  //    virtual bool IsEmpty() const;
  //    virtual void Clear();
  virtual void Print(std::ostream &oss) = 0;
};

#endif  // CPP_STUDY_ALL_ABSTRACT_AOI_H
