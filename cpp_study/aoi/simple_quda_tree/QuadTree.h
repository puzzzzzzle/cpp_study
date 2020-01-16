#ifndef QUADTREE_H
#define QUADTREE_H

#include <queue>
#include <sstream>
#include <stack>
#include <string>

#include "QTNode.h"
#include "Vertex.h"
using namespace std;

#define LOWER_LEFT_QUAD 0
#define UPPER_LEFT_QUAD 1
#define LOWER_RIGHT_QUAD 2
#define UPPER_RIGHT_QUAD 3

enum enclosure_status { NODE_NOT_IN_REGION, NODE_PARTIALLY_IN_REGION, NODE_CONTAINED_BY_REGION };

template <typename T>
class QuadTree {
public:
    QuadTree<T>(vertex center, vertex range, unsigned bucketSize = 1, unsigned depth = 16);
    ~QuadTree();

    void                    insert(vertex v, T data);
    bool                    contains(vertex v);
    bool                    remove(vertex v);
    void                    print(ostream& ss);
    vector<pair<vertex, T>> getObjectsInRegion(vertex minXY, vertex maxXY);

private:
    QTNode<T>*       childNode(const vertex& v, QTNode<T>* node);
    vertex           newCenter(int direction, QTNode<T>* node);
    int              direction(const vertex& point, QTNode<T>* node);
    void             insert(vertex v, T data, QTNode<T>* node, unsigned depth);
    void             reduce(stack<QTNode<T>*>& node);
    void             print(QTNode<T>* node, ostream& ss);
    void             addAllPointsToResults(QTNode<T>* node, vector<pair<vertex, T>>& results);
    bool             pointInRegion(const vertex& point, const vertex& minXY, const vertex& maxXY);
    enclosure_status getEnclosureStatus(const vertex& center, const vertex& range, const vertex& minXY, const vertex& maxXY);

    QTNode<T>* root;
    unsigned   maxDepth, maxBucketSize;
};

#include "QuadTree.tpp"

#endif  //#ifdef QUADTREE_H