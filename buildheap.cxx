//
//  main.cpp
//  buildheap
//
//  Created by WENXI LU on 2/24/19.
//  Copyright © 2019 wenxi. All rights reserved.
//

#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <string>
#include "priorityqueue.h"
//#include "priorityqueue.cpp"

int main(int argc, char** argv) {
    using json = nlohmann::json;
    using namespace std;
    string str(argv[1]);
    string filename = str;
    std::ifstream file;
    file.open(filename);
    json jsonObject;
    json HeapResult;
    if (file.is_open()) {
        file >> jsonObject;
    }
    //    cout << jsonObject;
    size_t max_size = jsonObject["metadata"]["maxHeapSize"];
    PriorityQueue heap(max_size);
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        if(itr.key() == "metadata") {
            continue;
        }
        Key keyValue = 0.0;
        string op;
        string operation = itr.key();
        for(auto iitr = jsonObject[operation].begin(); iitr != jsonObject[operation].end(); ++iitr) {
            //            cout << itr.key() << endl;
            if(iitr.key() == "key") {
                keyValue = iitr.value();
                //                heap.insert(key);
                //                cout << keyValue << endl;
            }
            if(iitr.key() == "operation") {
                op = iitr.value();
            }
        }
        //        cout << "change" << endl;
        if(op == "insert") {
            //            cout << "insert before: " << heap.size() << endl;
            heap.insert(keyValue);
            
            //            cout << "insert after: " << heap.size() << endl;
            //            cout << keyValue << endl;
        } else if(op == "removeMin") {
            heap.removeMin();
            //            KeyValuePair min = heap.removeMin();
            //            cout << "remove size: " << min.first << endl;
            //            cout << min.first << endl;
        }
    }
    
    //    heapSize = max_size + 1;
    HeapResult = heap.JSON();
    //    cout << HeapResult << endl;
    HeapResult["metadata"]["numOperations"] = jsonObject["metadata"]["numOperations"];
    //    HeapResult["metadata"]["max_size"] = jsonObject["metadata"]["maxHeapSize"];
    cout << HeapResult << endl;
}

