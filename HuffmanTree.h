//
// Created by 86189 on 2020/12/20.
//

#ifndef TAR_SIMU2_HUFFMANTREE_H
#define TAR_SIMU2_HUFFMANTREE_H
#include <iostream>
#include <queue>
#include <map>
class HuffmanNode{
public:
    HuffmanNode *parent;
    HuffmanNode *left;
    HuffmanNode *right;
    char nodeChar;
    int power;
    HuffmanNode(){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        nodeChar = '\0';
        power = 0;
    };
    HuffmanNode(char c,int p){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        power = p;
        nodeChar = c;
        //std::cout<<"create: p="<<power<<" char="<<nodeChar<<std::endl;
    }
    //会设置子节点的父节点
    HuffmanNode(HuffmanNode *l, HuffmanNode *r){
        parent = nullptr;
        left = l;
        l->parent = this;
        right = r;
        r->parent = this;
        nodeChar = '\0';
        power = l->power + r->power;
    }
    bool isLeaf(){return (left == nullptr && right == nullptr); }
    bool operator>(const HuffmanNode &h) const{ return power>h.power; }
    bool operator<(const HuffmanNode &h) const{ return power<h.power; }
};
//一个函数对象，用于从小到大排序存放指针的pq
template<typename Type, typename Compare = std::greater<Type> >
class p_greater : public std::binary_function<Type *, Type *, bool> {
public:
    bool operator()(const Type *x, const Type *y) const
    { return Compare()(*x, *y); }
};


class HuffmanTree {
public:
    //优先队列，用于选出权值最小的节点
    HuffmanNode *rootP;
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, p_greater<HuffmanNode>> hq;
    //std::vector<std::string> codeV;
    std::map<char, std::string> codeM;
    HuffmanTree() = default;
    HuffmanTree(int charPower[], int charNum);
    HuffmanTree(const std::map<char, int> &m);
    void construct(int charPower[], int charNum);
    void construct(const std::map<char, int> &m);
    void printTree() const;
    void printCodeV() const;
    void deleteNode(HuffmanNode *node);
    void constructCode(HuffmanNode *node, const std::string &prefix);
    ~HuffmanTree();
};
void testQueue();

#endif //TAR_SIMU2_HUFFMANTREE_H
