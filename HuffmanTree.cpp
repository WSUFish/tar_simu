//
// Created by 86189 on 2020/12/20.
//

#include "HuffmanTree.h"

void testQueue(){
    int testPower[4] = {3,1,2,1};
    HuffmanTree t(testPower, 4);
    t.printCodeV();
}

HuffmanTree::HuffmanTree(int charPower[], int charNum) {
    rootP = nullptr;
    construct(charPower, charNum);
    deP = rootP;
}

HuffmanTree::HuffmanTree(const std::map<char, int> &m){
    rootP = nullptr;
    construct(m);
    deP = rootP;
}

void HuffmanTree::printTree() const {
    std::queue<HuffmanNode*> printQueue;
    HuffmanNode newLine('\n',-1);
    printQueue.push(rootP);
    printQueue.push(&newLine);
    while(printQueue.size()>1){
        HuffmanNode *temp = printQueue.front();
        printQueue.pop();
        if(temp->power==-1){
            printf("\n");
            printQueue.push(&newLine);
        }else if(temp->isLeaf()){
            printf("%d:%d  ",temp->nodeChar,temp->power);
        }else{
            printQueue.push(temp->left);
            printQueue.push(temp->right);
            printf(" :%d     ",temp->power);
        }
    }
}
void HuffmanTree::deleteNode(HuffmanNode *node) {
    if(node->left!= nullptr){
        deleteNode(node->left);
    }
    if(node->right!= nullptr){
        deleteNode(node->right);
    }
    delete node;
}


void HuffmanTree::constructCode(HuffmanNode *node, const std::string &prefix) {
    if(node->isLeaf()){
        if(prefix.length()!=0){
            codeM[node->nodeChar] = prefix;
        }else{ //只有一种字符的特殊情况需要这样吗？
            codeM[node->nodeChar] = prefix;
        }
    }else{
        constructCode(node->left, prefix+"0");
        constructCode(node->right, prefix+"1");
    }
}

bool HuffmanTree::decode(bool bit, char &result) {
    if(bit){
        deP = deP->right;
    }else{
        deP = deP->left;
    }
    if(deP->isLeaf()){
        result = deP->nodeChar;
        deP = rootP;
        return true;
    }else{
        return false;
    }
}

void HuffmanTree::printCodeV() const {
    for(const auto &iter: codeM){
        std::cout << (int)iter.first << ":" << iter.second << std::endl;
    }
}

void HuffmanTree::construct(int charPower[], int charNum){
    //字符集不能小于1
    if(charNum<1){
        rootP = nullptr;
        return;
    }
    //初始化优先队列
    for(int i=0;i<charNum;i++){
        if(charPower[i]==0){
            continue;
        }
        auto *node = new HuffmanNode((char)i, charPower[i]);
        hq.push(node);
    }
    //循环生成
    while(hq.size()>=2){
        HuffmanNode *l = hq.top();
        hq.pop();
        HuffmanNode *r = hq.top();
        hq.pop();
        auto *temp = new HuffmanNode(l,r);
        hq.push(temp);
    }
    //得到根节点
    rootP = hq.top();
    deP = rootP;
    //构建编码表
    constructCode(rootP,"");

}
void HuffmanTree::construct(const std::map<char, int> &m){
    if(m.size()<1){
        rootP = nullptr;
        std::cerr << "error! map too small" << std::endl;
        return;
    }
    //初始化优先队列
    for(const auto &iter : m){
        auto *node = new HuffmanNode(iter.first, iter.second);
        hq.push(node);
    }
    //循环生成
    while(hq.size()>=2){
        HuffmanNode *l = hq.top();
        hq.pop();
        HuffmanNode *r = hq.top();
        hq.pop();
        auto *temp = new HuffmanNode(l,r);
        hq.push(temp);
    }
    //得到根节点
    rootP = hq.top();
    //构建编码表
    constructCode(rootP,"");
}


HuffmanTree::~HuffmanTree() {
    deleteNode(rootP);
}
