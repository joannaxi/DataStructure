//
//  AVL.cpp
//  AVL
//
//  Created by WENXI LU on 3/14/19.
//  Copyright © 2019 wenxi. All rights reserved.
//


#include "AVL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cassert>


AVLTree::AVLTree() : root_(nullptr), size_(0) {}

void AVLTree::Insert(int key) {
    
    if (root_ == nullptr) {
        root_ = std::make_shared<BSTNode>(key);
        size_++;
        return;
    }
    std::shared_ptr<BSTNode> node = root_;
    //    std::shared_ptr<BSTNode> currentNode = root_, lastNode = nullptr;
    node = Insert(node, node->parent_, key);
    size_++;
}
//AVLTree::AVLTree() : root_(nullptr), size_(0) {}
/*
bool AVLTree::Delete(int key) {
    std::shared_ptr<BSTNode> currentNode = root_;
    while (currentNode != nullptr) {
        if (currentNode->key_ == key) {
            if (currentNode->IsLeaf()) {
                DeleteLeaf(currentNode);
            } else if (currentNode->left_ == nullptr) {
                assert(currentNode->right_ != nullptr);
                std::shared_ptr<BSTNode> parent = currentNode->parent_.lock();
                parent->ReplaceChild(currentNode, currentNode->right_);
                size_--; assert(size_ >= 0);
            } else if (currentNode->right_ == nullptr) {
                assert(currentNode->left_ != nullptr);
                std::shared_ptr<BSTNode> parent = currentNode->parent_.lock();
                parent->ReplaceChild(currentNode, currentNode->left_);
                size_--; assert(size_ >= 0);
            } else {
                currentNode->key_ = DeleteMin(currentNode);
            }
        }
        currentNode = (key < currentNode->key_) ?
        currentNode->left_ : currentNode->right_;
    }
    return false;
}
*/

int AVLTree::DeleteMin() {
    return DeleteMin(root_);
}


void AVLTree::DeleteLeaf(std::shared_ptr<BSTNode> currentNode) {
    std::shared_ptr<BSTNode> parent = currentNode->parent_.lock();
    if (parent == nullptr) {
        // Delete root
        root_ = nullptr;
        size_--; assert(size_ == 0);
    } else {
        if (parent->right_ == currentNode) {
            parent->right_ = nullptr;
        } else if (parent->left_ == currentNode) {
            parent->left_ = nullptr;
        } else {
            std::cerr << "BST::DeleteLeaf Error: inconsistent state\n";
        }
        size_--; assert(size_ >= 0);
    }
}

int AVLTree::DeleteMin(std::shared_ptr<BSTNode> currentNode) {
    std::shared_ptr<BSTNode> lastNode = nullptr;
    while (currentNode != nullptr) {
        lastNode = currentNode;
        currentNode = currentNode->left_;
    }
    int result = lastNode->key_;
    std::shared_ptr<BSTNode> parent = lastNode->parent_.lock();
    if (parent == nullptr) {
        // lastNode is root
        if (lastNode->right_ != nullptr) {
            root_ = lastNode->right_;
            lastNode->right_->parent_.reset();
        } else {
            root_ = nullptr;
        }
    } else {
        // lastNode under the root
        if (lastNode->right_ != nullptr) {
            parent->left_ = lastNode->right_;
            lastNode->right_->parent_ = parent;
        } else {
            parent->left_ = nullptr;
        }
    }
    size_--; assert(size_ >= 0);
    return result;
}

size_t AVLTree::size() const {
    return size_;
}

bool AVLTree::empty() const {
    return size_ == 0;
}

bool AVLTree::Find(int key) const {
    std::shared_ptr<BSTNode> currentNode = root_;
    while (currentNode != nullptr) {
        if (currentNode->key_ == key) {
            return true;
        }
        currentNode = (key < currentNode->key_) ?
        currentNode->left_ : currentNode->right_;
    }
    return false;
}

int AVLTree::getHeight(std::shared_ptr<BSTNode> currentNode){
    //    if (currentNode == NULL)
    //        return 0;
    //    return currentNode->height_;
    if(currentNode == nullptr) {
        return 0;
    }
    return currentNode->height_;
    //    int leftHeight = getHeight(currentNode->left_);
    //    int rightHeight = getHeight(currentNode->right_);
    //    return std::max(leftHeight, rightHeight) + 1;
}

int AVLTree::getBalanceFactor(std::shared_ptr<BSTNode> currentNode){
    if(currentNode == nullptr) {
        return 0;
    }
    //    std::cout << "currentNode->right_: " << getHeight(currentNode->right_) << std::endl;
    //    std::cout << "currentNode->left_: " << getHeight(currentNode->left_) << std::endl;
    int factor = int(getHeight(currentNode->right_) - getHeight(currentNode->left_));
    return factor;
}

std::string AVLTree::JSON() {
    nlohmann::json result;
    std::queue< std::shared_ptr<BSTNode> > nodes;
    if (root_ != nullptr) {
        result["height"] = getHeight(root_) - 1;
        result["root"] = root_->key_;
        nodes.push(root_);
        while (!nodes.empty()) {
            auto v = nodes.front();
            std::string key = std::to_string(v->key_);
            int height = getHeight(v) - 1;
            result[key]["height"] = height;
            int balance = getBalanceFactor(v);
            result[key]["balance factor"] = balance;
            nodes.pop();
            //            std::string key = std::to_string(v->key_);
            if (v->left_ != nullptr) {
                result[key]["left"] = v->left_->key_;
                nodes.push(v->left_);
            }
            if (v->right_ != nullptr) {
                result[key]["right"] = v->right_->key_;
                nodes.push(v->right_);
            }
            if (v->parent_.lock() != nullptr) {
                result[key]["parent"] = v->parent_.lock()->key_;
            } else {
                result[key]["root"] = true;
            }
        }
    }
    //    result["height"] = getHeight(root_);
    result["size"] = size_;
    return result.dump(2) + "\n";
}

void AVLTree::Insert_original(int key) {
    if (root_ == nullptr) {
        root_ = std::make_shared<BSTNode>(key);
        size_++;
        return;
    }
    std::shared_ptr<BSTNode> currentNode = root_, lastNode = nullptr;
    while (currentNode != nullptr) {
        lastNode = currentNode;
        currentNode = (key < currentNode->key_) ?
        currentNode->left_ : currentNode->right_;
    }
    if (key < lastNode->key_) {
        lastNode->left_ = std::make_shared<BSTNode>(key, lastNode);
    } else {
        lastNode->right_ = std::make_shared<BSTNode>(key, lastNode);
    }
    //    lastNode->height_ = 1 + std::max(getHeight(lastNode->left_),
    //                                 getHeight(lastNode->right_));
    size_++;
}

int AVLTree::getHeight_original(std::shared_ptr<BSTNode> currentNode){
    //    if (currentNode == NULL)
    //        return 0;
    //    return currentNode->height_;
    if(currentNode == nullptr) {
        return 0;
    }
    //    return currentNode->height_;
    int leftHeight = getHeight_original(currentNode->left_);
    int rightHeight = getHeight_original(currentNode->right_);
    return std::max(leftHeight, rightHeight) + 1;
}

int AVLTree::getBalanceFactor_original(std::shared_ptr<BSTNode> currentNode){
    if(currentNode == nullptr) {
        return 0;
    }
    //    std::cout << "currentNode->right_: " << getHeight(currentNode->right_) << std::endl;
    //    std::cout << "currentNode->left_: " << getHeight(currentNode->left_) << std::endl;
    int factor = int(getHeight_original(currentNode->right_) - getHeight_original(currentNode->left_));
    return factor;
}

std::string AVLTree::originalJSON() {
    nlohmann::json result;
    std::queue< std::shared_ptr<BSTNode> > nodes;
    if (root_ != nullptr) {
        result["height"] = getHeight_original(root_) - 1;
        result["root"] = root_->key_;
        nodes.push(root_);
        while (!nodes.empty()) {
            auto v = nodes.front();
            std::string key = std::to_string(v->key_);
            int height = getHeight_original(v) - 1;
            result[key]["height"] = height;
            int balance = getBalanceFactor_original(v);
            result[key]["balance factor"] = balance;
            nodes.pop();
            //            std::string key = std::to_string(v->key_);
            if (v->left_ != nullptr) {
                result[key]["left"] = v->left_->key_;
                nodes.push(v->left_);
            }
            if (v->right_ != nullptr) {
                result[key]["right"] = v->right_->key_;
                nodes.push(v->right_);
            }
            if (v->parent_.lock() != nullptr) {
                result[key]["parent"] = v->parent_.lock()->key_;
            } else {
                result[key]["root"] = true;
            }
        }
    }
    //    result["height"] = getHeight(root_);
    result["size"] = size_;
    return result.dump(2) + "\n";
}

/*
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
            }
            if(iitr.key() == "operation") {
                op = iitr.value();
            }
        }
        if(op == "Insert") {
            AVLTree.Insert_original(keyValue);
        } else if(op == "Delete") {
            AVLTree.Delete(keyValue);
        } else if(op == "DeleteMin") {
            AVLTree.DeleteMin();
        }
    }
    output = AVLTree.originalJSON();
    result = json::parse(output);
    cout << result;
    
}
*/
