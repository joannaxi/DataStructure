//
//  main.cpp
//  json
//
//  Created by WENXI LU on 2/10/19.
//  Copyright © 2019 WENXI LU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"

int main(int argc, char** argv) {
    using json = nlohmann::json;
    using namespace std;
    string str(argv[1]);
    string filename = str;
    std::ifstream file;
    file.open(filename);
    nlohmann::json jsonObject;
    nlohmann::json jResult;
    nlohmann::json jSample;
    if (file.is_open()) {
        file >> jsonObject;
    }
//    vector<string> sstr;
    int count = 0;
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        json Sample = json::object();
        json ConsecutiveInversions = json::object();
        json metadata = json::object();
//        jResult = {
//            {sample, Sample},
//            {sample, metadata}
//        };
        if(itr.key() == "metadata") {
            continue;
        }
        vector<int> vec;
        bool flag = false;
//        int index = 0;
        string sample = itr.key();
//        sstr.push_back(sample);
        for (auto arrayItr = jsonObject[sample].begin();
             arrayItr != jsonObject[sample].end();
             ++arrayItr) {
            //            cout << *arrayItr << endl;
            vec.push_back(*arrayItr);
            //            cout << vec1[0][0] << endl;
        }
        for(int i = 0; i < vec.size() - 1; ++i) {
            if(vec.at(i + 1) < vec.at(i)) {
                flag = true;
                ConsecutiveInversions += {to_string(i), {vec.at(i), vec.at(i + 1)}};
//                Sample = {{"ConsecutiveInversions", ConsecutiveInversions}, {"sample", jsonObject[sample]}};
//                jResult[sample] += Sample;
                flag = true;
//                index++;
            }
        }
        
        if(flag) {
            Sample = {{"ConsecutiveInversions", ConsecutiveInversions}, {"sample", jsonObject[sample]}};
            jResult[sample] = Sample;

            count ++;
    }
//
//    int index1 = 0;
//    int index2 = 0;
//    bool flag = false;
//    int count = 0;
//    for(int i = 0; i < sample1.size() - 1; ++i) {
//        if(sample1.at(i + 1) < sample1.at(i)) {
//            flag = true;
//            index1++;
////            jResult = {
////                {"Sample1", {"ConsecutiveInversions", {to_string(index1), {sample1.at(i), sample1.at(i + 1)}}}},
////                {"Sample"},
////                {"metadata"}
////            };
//        }
//    }
//    if(flag) {
//        count ++;
//        //        jSample += jsonObject["Sample2"];
//        json Sample1 = json::object();
//        json ConsecutiveInversions = json::object();
//        json metadata = json::object();
//        jResult = {
//            {"Sample1", Sample1},
//            //            {"ConsecutiveInversions", ConsecutiveInversions},
//            {"metadata", metadata}
//        };
//
//        Sample1 = {"ConsecutiveInversions", ConsecutiveInversions};
//        ConsecutiveInversions = {{"1",jSample[0]}, {"2", jSample[1]}};
//        jResult["Sample1"]["ConsecutiveInversions"] = ConsecutiveInversions;
////        jResult["Sample2"]["ConsecutiveInversions"] = ConsecutiveInversions;
//        jResult["Sample1"]["sample"] = jsonObject["Sample1"];
////        jResult["metadata"] = jsonObject["metadata"];
////        jResult["metadata"]["file"] = "SampleExample.json";
////        jResult["metadata"]["samplesWithInversions"]= count;
//    }
//    flag = false;
//    for(int i = 0; i < sample2.size() - 1; ++i) {
//        if(sample2.at(i + 1) < sample2.at(i)) {
//            flag = true;
//            index2++;
//            jSample += {sample2.at(i), sample2.at(i + 1)};
//        }
//    }
//    if(flag) {
//        count++;
////        jSample += jsonObject["Sample2"];
//        json Sample2 = json::object();
//        json ConsecutiveInversions = json::object();
//        json metadata = json::object();
//        jResult = {
//            {"Sample2", Sample2},
////            {"ConsecutiveInversions", ConsecutiveInversions},
//            {"metadata", metadata}
//        };
//
//        Sample2 = {"ConsecutiveInversions", ConsecutiveInversions};
//        ConsecutiveInversions = {{"1",jSample[0]}, {"2", jSample[1]}};
//        jResult["Sample2"]["ConsecutiveInversions"] = ConsecutiveInversions;
//        jResult["Sample2"]["sample"] = jsonObject["Sample2"];
//        jResult["metadata"] = jsonObject["metadata"];
//        jResult["metadata"]["file"] = "SampleExample.json";
//        jResult["metadata"]["samplesWithInversions"]= count;
//    }
//    jResult["Sample2"] = jSample;
//    jResult["Sample2"] = Sample2;
//    jResult["Sample2"]["sample"] = jsonObject["Sample2"];
//    jResult["metadata"] = jsonObject["metadata"];
//    jResult["metadata"]["file"] = "SampleExample.json";
//    jResult["metadata"]["samplesWithInversions"]= 1;
//    cout << jSample << " ";
        

//    jsonObject["metadata"]["filename"] = "SampleExample.json";
//    std::cout << jsonObject.dump(2) << "\n";
//    cout << sample1.size() << endl;
//    cout << sample2.size() << endl;
}
    jResult["metadata"] = jsonObject["metadata"];
    jResult["metadata"]["file"] = str;
    jResult["metadata"]["samplesWithInversions"]= count;
    cout << jResult << " ";
}
