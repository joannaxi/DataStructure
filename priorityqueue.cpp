#include <iostream>
#include "json.hpp"
#include <algorithm>
#include <limits>

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
nodes_(max_size + 1, KeyValuePair()),
max_size_(max_size),
size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
    
}

void PriorityQueue::insert(KeyValuePair kv) {
    // TODO: complete this function
//    if(size_ <= max_size_) {
//    nodes_.push_back(kv);
//    size_++;
//    for (size_t i = size_; i >= size_ / 2; i--) {
//        heapifyUp(i);
//    }
    if(size_ == nodes_.size() - 1 && size_ < max_size_) {
        nodes_.push_back(kv);
        size_++;
        heapifyUp(size_);
        
//        size_++;
//        nodes_[size_] = kv;
////        nodes_.push_back(kv);
//
//        heapifyUp(size_);
    } else if(size_ < nodes_.size() - 1 && size_ < max_size_) {
        size_++;
        nodes_[size_] = kv;
//        std::cout << size_ << " , " << nodes_[size_].first << std::endl;
        heapifyUp(size_);
//        for(int i = 1; i <= size_; ++i) {
//            std::cout << nodes_[i].first << std::endl;
//        }
        
    }

//    }

}

KeyValuePair PriorityQueue::min() {
    // TODO: complete this function

    return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
//    std::cout << "remove" << std::endl;
    // TODO: complete this function
    KeyValuePair ans = nodes_[ROOT];
    std::swap(nodes_[ROOT], nodes_[size_]);
    nodes_.erase(nodes_.begin() + size_);
    size_--;
    for (size_t i = size_ / 2; i >= 1; i--) {
        heapifyDown(i);
    }
    
//    KeyValuePair ans = nodes_[ROOT];
//    KeyValuePair temp = nodes_[nodes_.size()];
//    nodes_[nodes_.size()] = nodes_[ROOT];
//    nodes_[ROOT] = temp;
//    nodes_.pop_back();
//    heapifyDown(ROOT);

    return ans;
}

bool PriorityQueue::isEmpty() const {
    // TODO: complete this function
    return size_;
}

size_t PriorityQueue::size() const {
    // TODO: complete this function
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    // TODO: complete this function
//    if(i < ROOT || i > nodes_.size()) {
//        std::cout << "heapifyUp ERROR" << std::endl;
//    }
//    while(i > 0 && nodes_[i].first < nodes_[i / 2].first) {
//        KeyValuePair temp = nodes_[i / 2];
//        nodes_[i / 2] = nodes_[i];
//        nodes_[i] = temp;
//        i = i / 2;
//    }
    while (i > 1) {
        size_t index = i / 2;
        if (nodes_[i].first < nodes_[index].first) {
            std::swap(nodes_[i], nodes_[index]);
            i = index;
        } else {
            return;
        }
        
    }
}

void PriorityQueue::heapifyDown(size_t i) {
    // TODO: complete this function
//    if(i < ROOT || i > nodes_.size() - 1 || 2 * i > nodes_.size() - 1) {
//        std::cout << "heapifyDown ERROR" << std::endl;
//    }
//    while(2 * i < nodes_.size() - 1) {
////        if(2 * i == nodes_.size()) {
////            if(nodes_[i].first > nodes_[2 * i].first) {
////                KeyValuePair temp = nodes_[i];
////                nodes_[i] = nodes_[2 * i];
////                nodes_[2 * i] = temp;
////                i = 2 * i;
////            }
////        }
//
//        if(nodes_[i].first > nodes_[2 * i].first && nodes_[i].first < nodes_[2 * i + 1].first) {
//            KeyValuePair temp = nodes_[i];
//            nodes_[i] = nodes_[2 * i];
//            nodes_[2 * i] = temp;
//            i = 2 * i;
//        }
//        else if(nodes_[i].first > nodes_[2 * i + 1].first && nodes_[i].first < nodes_[2 * i].first) {
//            KeyValuePair temp = nodes_[i];
//            nodes_[i] = nodes_[2 * i + 1];
//            nodes_[2 * i + 1] = temp;
//            i = 2 * i + 1;
//        }
//        else if(nodes_[i].first > nodes_[2 * i].first && nodes_[i].first > nodes_[2 * i + 1].first) {
//            if(nodes_[2 * i].first <= nodes_[2 * i + 1].first) {
//                KeyValuePair temp = nodes_[i];
//                nodes_[i] = nodes_[2 * i];
//                nodes_[2 * i] = temp;
//                i = 2 * i;
//            }
//            else {
//                KeyValuePair temp = nodes_[i];
//                nodes_[i] = nodes_[2 * i + 1];
//                nodes_[2 * i + 1] = temp;
//                i = 2 * i + 1;
//            }
//        }
//
//    }
    size_t index = i * 2;
    KeyValuePair val = nodes_[i];
    while (index <= size_) {
        KeyValuePair min = val;
        size_t minIndex = -1;
        for (size_t j = 0; j < 2 && j + index <= size_; j++) {
            if (nodes_[j + index].first < min.first) {
                min.first = nodes_[j + index].first;
                min.second.first = nodes_[j + index].second.first;
                min.second.second = nodes_[j + index].second.second;
                minIndex = j + index;
            }
        }
        if (min.first == val.first) {
            return;
        } else {
            std::swap(nodes_[i], nodes_[minIndex]);
            i = minIndex;
            index = 2 * i;
        }
    }

}

void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
//    if(i < ROOT || i > nodes_.size()) {
//        std::cout << "removeNode ERROR" << std::endl;
//    }
    nodes_.erase(nodes_.begin() + i);
    size_--;
    for (size_t j = size_ / 2; j >= 1; j--) {
        heapifyDown(j);
    }
    
}

Key PriorityQueue::getKey(size_t i) {
    // TODO: complete this function
    return nodes_[i].first;
}

