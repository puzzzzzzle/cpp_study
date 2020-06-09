//
// Created by khalidzhang on 2019/12/2.
//

#ifndef CPP_STUDY_ALL_ORTHOGONALLISTAOI_HPP
#define CPP_STUDY_ALL_ORTHOGONALLISTAOI_HPP

#include <cmath>
#include <iostream>
#include <list>

#include "AbstractAoi.h"

// 双链表（对象）
template <typename NumberT, typename ObjectT, bool AutoDelete>
class IDoubleNode : public IBaseNode<NumberT, ObjectT, AutoDelete> {
  public:
  typedef NumberT Number;
  typedef ObjectT Object;
  typedef IPoint<NumberT> Point;

  public:
  IDoubleNode() {
    xPrev = xNext = nullptr;
    yPrev = yNext = nullptr;
  };

  IDoubleNode *xPrev;
  IDoubleNode *xNext;

  IDoubleNode *yPrev;
  IDoubleNode *yNext;
};

template <typename NumberT, typename ObjectT>
class IDoubleNodePoint : public IDoubleNode<NumberT, ObjectT, true> {
  ~IDoubleNodePoint() { delete IBaseNode<NumberT, ObjectT, true>::obj; }
};

template <typename NumberT, typename ObjectT>
class IDoubleNodeNoPoint : public IDoubleNode<NumberT, ObjectT, false> {};

template <typename NumberT, typename ObjectT, bool AutoDelete>
class OrthogonalListAoi
    : public IAoi<NumberT, ObjectT, IDoubleNode<NumberT, ObjectT, AutoDelete>,
                  AutoDelete> {
  public:
  typedef NumberT Number;
  typedef ObjectT Object;
  typedef IDoubleNode<NumberT, ObjectT, AutoDelete> DoubleNode;

  typedef
      typename IAoi<NumberT, ObjectT, IDoubleNode<NumberT, ObjectT, AutoDelete>,
                    AutoDelete>::Point Point;
  typedef
      typename IAoi<NumberT, ObjectT, IDoubleNode<NumberT, ObjectT, AutoDelete>,
                    AutoDelete>::BaseNode BaseNode;
  typedef IDoubleNode<NumberT, ObjectT, AutoDelete> Node;

  public:
  OrthogonalListAoi() {
    this->_head = new DoubleNode();  // 带头尾的双链表(可优化去掉头尾)
    _head->point.x = 0;
    _head->point.y = 0;

    this->_tail = new DoubleNode();
    _tail->point.x = 0;
    _tail->point.y = 0;

    _head->xNext = _tail;
    _head->yNext = _tail;
    _tail->xPrev = _head;
    _tail->yPrev = _head;
  }

  public:
  // 调试代码
  virtual void Print(std::ostream &oss) override  // 打印链表(从头开始)
  {
    //        using std::cout;
    //        using std::endl;

    // 打印x轴链表
    DoubleNode *cur = _head->xNext;
    oss << "x -> { ";
    while (cur != _tail) {
      oss << "{" << *cur << "} -> ";
      cur = cur->xNext;
    }
    oss << " ] end\n";

    // 打印y轴链表
    oss << "y -> ";

    cur = _head->yNext;
    while (cur != _tail) {
      oss << "{" << *cur << "} -> ";
      cur = cur->yNext;
    }
    oss << "end\n";
  };

  public:
  virtual bool Add(const BaseNode &object) override {
    auto *node = new DoubleNode();
    node->point = object.point;
    node->obj = object.obj;
    _add(node);
    return true;
  }

  virtual bool Move(Node *pnode, const Point &point) override {
    Leave(pnode, false);
    pnode->point.x = point.x;
    pnode->point.y = point.y;
    _add(pnode);
    return true;
  }

  virtual bool Leave(Node *pnode, bool autoDelete) override {
    pnode->xPrev->xNext = pnode->xNext;
    pnode->xNext->xPrev = pnode->xPrev;
    pnode->yPrev->yNext = pnode->yNext;
    pnode->yNext->yPrev = pnode->yPrev;

    pnode->xPrev = NULL;
    pnode->xNext = NULL;
    pnode->yPrev = NULL;
    pnode->yNext = NULL;
    if (autoDelete) {
      delete pnode;
    }
    return true;
  }

  virtual std::vector<std::pair<Node *, bool>> QueryInsideRegion(
      Node *pnode, NumberT xSize, NumberT ySize) override {
    std::vector<std::pair<Node *, bool>> result;
    // 往后找
    DoubleNode *cur = pnode->xNext;
    while (cur != _tail) {
      if ((cur->point.x - cur->point.halfXLen - pnode->point.x) > xSize) {
        break;
      } else {
        int yDiff = abs(pnode->point.y - cur->point.y) - cur->point.halfYLen;
        bool IsOnSide = abs(pnode->point.y - cur->point.y) > ySize ||
                        abs(pnode->point.x - cur->point.x) > xSize;
        if (yDiff <= ySize) {
          result.push_back({cur, IsOnSide});
        }
      }
      cur = cur->xNext;
    }

    // 往前找
    cur = pnode->xPrev;
    while (cur != _head) {
      if ((pnode->point.x - cur->point.x - cur->point.halfXLen) > xSize) {
        break;
      } else {
        int yDiff = abs(pnode->point.y - cur->point.y) - cur->point.halfYLen;
        bool IsOnSide = abs(pnode->point.y - cur->point.y) > ySize ||
                        abs(pnode->point.x - cur->point.x) > xSize;
        if (yDiff <= ySize) {
          result.push_back({cur, IsOnSide});
        }
      }
      cur = cur->xPrev;
    }

    return result;
  }

  virtual std::vector<std::pair<Node *, bool>> QueryInsidespace(
      NumberT xStart, NumberT yStart, NumberT xSize, NumberT ySize) override {
    std::vector<std::pair<Node *, bool>> result;
    // 往后找
    DoubleNode *cur = _head->xNext;
    while (cur != _tail) {
      if ((abs(cur->point.x - xStart) - cur->point.halfXLen) > xSize) {
        break;
      } else {
        int yDiff = abs(cur->point.y - yStart) - cur->point.halfYLen;
        bool IsOnSide = abs(ySize - cur->point.y) > ySize ||
                        abs(xStart - cur->point.x) > xSize;
        if (yDiff <= ySize) {
          result.push_back({cur, IsOnSide});
        }
      }
      cur = cur->xNext;
    }

    return result;
  }

  private:
  DoubleNode *_head;
  DoubleNode *_tail;

  void _add(DoubleNode *node) {
    // x轴处理
    DoubleNode *cur = _head->xNext;
    while (cur != NULL) {
      if ((cur->point.x > node->point.x) || cur == _tail)  // 插入数据
      {
        node->xNext = cur;
        node->xPrev = cur->xPrev;
        cur->xPrev->xNext = node;
        cur->xPrev = node;
        break;
      }
      cur = cur->xNext;
    }

    // y轴处理
    cur = _head->yNext;
    while (cur != NULL) {
      if ((cur->point.y > node->point.y) || cur == _tail)  // 插入数据
      {
        node->yNext = cur;
        node->yPrev = cur->yPrev;
        cur->yPrev->yNext = node;
        cur->yPrev = node;
        break;
      }
      cur = cur->yNext;
    }
  }
};

#endif  // CPP_STUDY_ALL_ORTHOGONALLISTAOI_HPP
