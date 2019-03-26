//
//  AVL.hpp
//  AVL
//
//  Created by WENXI LU on 3/14/19.
//  Copyright © 2019 wenxi. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <stdio.h>
#include "BST.h"
#include "json.hpp"



class AVLTree {
public:
    //    BSTNode* currentNode;
    AVLTree();
    int getHeight(std::shared_ptr<BSTNode> currentNode);
    int getHeight_original(std::shared_ptr<BSTNode> currentNode);
    int getBalanceFactor(std::shared_ptr<BSTNode> currentNode);
    int getBalanceFactor_original(std::shared_ptr<BSTNode> currentNode);
    void Insert(int key);
    void Insert_original(int key);
    bool Delete(int key);
    bool Find(int key) const;
    std::string JSON();
    std::string originalJSON();
    size_t size() const;
    bool empty() const;
    int DeleteMin();
    std::shared_ptr<BSTNode> Insert(std::shared_ptr<BSTNode> root, std::weak_ptr<BSTNode> parentNode, int key);
    //    void Insert(std::shared_ptr<BSTNode> root, int key);
    
    std::shared_ptr<BSTNode> rightRotate(std::shared_ptr<BSTNode>y);
    std::shared_ptr<BSTNode> leftRotate(std::shared_ptr<BSTNode>x);
    //    std::std::shared_ptr<BSTNode> AVLTree::AVLRotate(std::shared_ptr<BSTNode> lastNode);
/*
    bool IsLeaf() const;
    bool IsMissingChild() const;
    bool HasLeftChild() const;
    bool HasRightChild() const;
    void DeleteChild(std::shared_ptr<BSTNode> v);
    void ReplaceChild(std::shared_ptr<BSTNode> v, std::shared_ptr<BSTNode> u);
   // int height(std::shared_ptr<BSTNode> node);
*/

private:
    void DeleteLeaf(std::shared_ptr<BSTNode> currentNode);
    int DeleteMin(std::shared_ptr<BSTNode> currentNode);
    std::shared_ptr<BSTNode> root_;
    size_t size_;
};




#endif /* AVL_hpp */

