//
//  AVLCommands.cpp
//  AVL
//
//  Created by WENXI LU on 3/14/19.
//  Copyright © 2019 wenxi. All rights reserved.
//

#include <stdio.h>
#include "AVL.h"
#include <fstream>
#include <iostream>
#include <cmath>


std::shared_ptr<BSTNode> AVLTree::Insert(std::shared_ptr<BSTNode> node, std::weak_ptr<BSTNode> parentNode, int key) {
    if(node == nullptr) {
//        std:: cout << "nodeParentKey: " << parentNode.lock()->key_ << std::endl;
        node = std::make_shared<BSTNode>(key, parentNode);
        return std::shared_ptr<BSTNode>(node);
    }

    if (key < node->key_) {
//        std:: cout << "nodeKey: " << node->key_ << std::endl;
        node->left_ = Insert(node->left_, node, key);
        int balance = getBalanceFactor(node);
//        std::cout << "balanceLeft: " << balance << std::endl;
//        std::cout << "balanceRight: " << balance << std::endl;
//        std::cout << "keyLeft: " << key << std::endl;
//        std::cout << "nodeKeyleft: " << node->key_ << std::endl;
        // Left Left Case
        if (balance < -1 && key < node->left_->key_) {
//            std::shared_ptr<BSTNode> parent1 = parentNode.lock();
//            std::shared_ptr<BSTNode> parent2 = node;
            node = rightRotate(node);
//            parent2->left_->right_->parent_ = parent2;
//            parent2->parent_ = node;
//            node->right_ = parent2;
//            node->parent_ = parent1;
        }
        
        // Left Right Case
        else if (balance < -1 && key > node->left_->key_)
        {
//            std::weak_ptr<BSTNode> parent1 = parentNode;
//            std::weak_ptr<BSTNode> parent2 = node;
//            std::shared_ptr<BSTNode> leftNode = node->left_;
            node->left_ =  leftRotate(node->left_);
//            leftNode->parent_ = node->left_;
//            node->left_->parent_ = parent2;
//            parent2.lock()->left_ = node->left_;
            node = rightRotate(node);
//            parent2.lock()->parent_ = node;
//            node->right_ = parent2.lock();
//            node->parent_ = parent1;
            
        }
    }
    else if (key > node->key_) {
        node->right_ = Insert(node->right_, node, key);
        int balance = getBalanceFactor(node);
//        std::cout << "balanceRight: " << balance << std::endl;
//        std::cout << "keyRight: " << key << std::endl;
//        std::cout << "nodeKeyRight: " << node->key_ << std::endl;
        // Left Left Case
        if (balance > 1 && key > node->right_->key_){
//            std::weak_ptr<BSTNode> parent1 = parentNode;
//            std::weak_ptr<BSTNode> parent2 = node;
            node = leftRotate(node);
//            parent2.lock()->parent_ = node;
//            node->left_ = parent2.lock();
//            node->parent_ = parent1;
        }
        
        // Left Right Case
        else if (balance > 1 && key < node->right_->key_)
        {
//            std::weak_ptr<BSTNode> parent1 = parentNode;
////            std::cout << "Rparent1: " << parent1.lock()->key_ << std::endl;
//            std::weak_ptr<BSTNode> parent2 = node;
////            std::cout<< "error" << std::endl;
//            std::shared_ptr<BSTNode> rightNode = node->right_;
//            std::cout << "Rparent2: " << parent2.lock()->key_ << std::endl;
            node->right_ =  rightRotate(node->right_);
//            rightNode->parent_ = node->right_;
//            node->right_->right_ = rightNode;
//            node->right_->parent_ = parent2;
//            parent2.lock()->right_ = node->right_;
//            std::cout << "node->rigt: " << node->right_->key_ << std::endl;
            node = leftRotate(node);
//            parent2.lock()->parent_ = node;
//            node->left_ = parent2.lock();
//            node->parent_ = parent1;
        }
        
    }
    
    node->height_ = 1 + std::max(getHeight(node->left_),
                                 getHeight(node->right_));
//    std::cout << "finalNodeParent: " << parentNode.lock()->key_ << std::endl;
    return node;
}

std::shared_ptr<BSTNode> AVLTree::leftRotate(std::shared_ptr<BSTNode> t)
{
    std::shared_ptr<BSTNode> grandparent = t;
    std::shared_ptr<BSTNode> parent = t->right_;
    grandparent->right_ = parent->left_;
    if(parent->left_ != nullptr) {
        parent->left_->parent_ = grandparent;
    }
    parent->parent_ = grandparent->parent_;
    if(grandparent->parent_.lock() == nullptr) {
        root_ = parent;
    }
    else if(grandparent == grandparent->parent_.lock()->left_) {
        grandparent->parent_.lock()->left_ = parent;
    }
    else if(grandparent == grandparent->parent_.lock()->right_) {
        grandparent->parent_.lock()->right_ = parent;
    }
    parent->left_ = grandparent;
    grandparent->parent_ = parent;
    t = parent;
    

    grandparent->height_ = std::max(getHeight(grandparent->left_), getHeight(grandparent->right_)) + 1;
    parent->height_ = std::max(getHeight(parent->left_), getHeight(parent->right_)) + 1;
    return t;
    
}

std::shared_ptr<BSTNode> AVLTree::rightRotate(std::shared_ptr<BSTNode> t)
{
//    std::shared_ptr<BSTNode> topgrandparent = t->parent_.lock();
    std::shared_ptr<BSTNode> grandparent = t;
    std::shared_ptr<BSTNode> parent = t->left_;
    grandparent->left_ = parent->right_;
    if(parent->right_ != nullptr) {
        parent->right_->parent_ = grandparent;
    }
    parent->parent_ = grandparent->parent_;
    if(grandparent->parent_.lock() == nullptr) {
        root_ = parent;
    }
    else if(grandparent == grandparent->parent_.lock()->left_) {
        grandparent->parent_.lock()->left_ = parent;
    }
    else if(grandparent == grandparent->parent_.lock()->right_) {
        grandparent->parent_.lock()->right_ = parent;
    }
    parent->right_ = grandparent;
    grandparent->parent_ = parent;
    t = parent;


    grandparent->height_ = std::max(getHeight(grandparent->left_), getHeight(grandparent->right_)) + 1;
    parent->height_ = std::max(getHeight(parent->left_), getHeight(parent->right_)) + 1;
    return t;
    
}

int main(int argc, char** argv) {
    using json = nlohmann::json;
    using namespace std;
    string str(argv[1]);
    string filename = str;
    std::ifstream file;
    file.open(filename);
    json jsonObject;
    string output;
    json result;
    if (file.is_open()) {
        file >> jsonObject;
    }
//    cout << jsonObject;
    AVLTree AVLTree;
//    std::shared_ptr<BSTNode> node;
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        if(itr.key() == "metadata") {
            continue;
        }
        int keyValue;
        string op;
        string operation = itr.key();
        for(auto iitr = jsonObject[operation].begin(); iitr != jsonObject[operation].end(); ++iitr) {
            if(iitr.key() == "key") {
                keyValue = iitr.value();
//                std::cout << keyValue << std::endl;
            }
            if(iitr.key() == "operation") {
                op = iitr.value();
                AVLTree.Insert(keyValue);
            }
        }
    }
    output = AVLTree.JSON();
    result = json::parse(output);
    cout << result;
}
