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
    //字符集不能小于1
    if(charNum<1){
        rootP = nullptr;
        return;
    }
    //初始化优先队列和数组
    codeV.resize(charNum);
    for(int i=0;i<charNum;i++){
        auto *t = new HuffmanNode((char)i, charPower[i]);
        hq.push(t);
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
            codeV[(int)node->nodeChar] = prefix;
        }else{ //只有一种字符的特殊情况需要这样吗？
            codeV[(int)node->nodeChar] = "0";
        }
    }else{
        constructCode(node->left, prefix+"0");
        constructCode(node->right, prefix+"1");
    }
}
void HuffmanTree::printCodeV() const {
    for(auto i=0;i<codeV.size();i++){
        std::cout<<i<<":"<<codeV[i]<<std::endl;
    }
}

HuffmanTree::~HuffmanTree() {
    deleteNode(rootP);
}
