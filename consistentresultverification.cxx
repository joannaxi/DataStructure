//
//  main.cpp
//  E2
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
    string str1(argv[1]);
    string str2(argv[2]);
    string filename1 = str1;
    string filename2 = str2;
    std::ifstream file1;
    std::ifstream file2;
    file1.open(filename1);
    file2.open(filename2);
    nlohmann::json jsonObject1;
    nlohmann::json jsonObject2;
//    nlohmann::json jResult;
//    nlohmann::json jSample;
    if (file1.is_open() && file2.is_open()) {
        file1 >> jsonObject1;
        file2 >> jsonObject2;
    }
    vector<vector<int>> vec1;
    vector<string> str;

    for (auto itr = jsonObject1.begin(); itr != jsonObject1.end(); ++itr) {
        if(itr.key() == "metadata") {
            continue;
        }
        vector<int> row;
        string sample1 = itr.key();
        str.push_back(sample1);
        for (auto arrayItr = jsonObject1[sample1].begin();
             arrayItr != jsonObject1[sample1].end();
             ++arrayItr) {
//            cout << *arrayItr << endl;
            row.push_back(*arrayItr);
//            cout << vec1[0][0] << endl;
        }
        vec1.push_back(row);
//        cout << vec1[0][0] << endl;
    }
//    for(int m = 0; m < vec1.size(); ++m) {
//        for(int n = 0; n < vec1[m].size(); ++n){
//            cout << vec1[m][n] << endl;
//        }
//    }
    vector<vector<int>> vec2;

    for (auto itr = jsonObject2.begin(); itr != jsonObject2.end(); ++itr) {
        if(itr.key() == "metadata") {
            continue;
        }
        vector<int> row;
        string sample2 = itr.key();
        for (auto arrayItr = jsonObject2[sample2].begin();
             arrayItr != jsonObject2[sample2].end();
             ++arrayItr) {
            row.push_back(*arrayItr);
        }
        vec2.push_back(row);

    }


    json result;
    int count = 0;
    for(int p = 0; p < vec1.size(); ++p) {
        json Mismatches = json::object();
        json Sample = json::object();
        int count1 = 0;
        bool flag = false;
        for(int q = 0; q < vec1[p].size(); ++q) {
//            cout << vec1[p][q] << "," << vec2[p][q] << endl;
            if(vec1[p][q] != vec2[p][q]) {
                flag = true;
                Mismatches += {to_string(count1), {vec1[p][q], vec2[p][q]}};
                count1++;
            }
        }
        if(flag){
            count++;
            Sample = {{argv[1], vec1[p]}, {argv[2], vec2[p]}, {"Mismatches", Mismatches}};
            result[str[p]] = Sample;
//            result += {str[p], Sample};
        }
//        if(sample1.at(i) != sample3.at(i)) {
////            count++;
//            flag1 = true;
//            count1++;
//            Mismatches1 += {to_string(count1), {sample1.at(i), sample3.at(i)}};
//        }
    }
//    if(flag1) {
//        count++;
//        Sample1 = {{argv[1], jsonObject1["Sample1"]}, {argv[2], jsonObject2["Sample1"]}, {"Mismatches", Mismatches1}};
//        result = {"Sample1", Sample1};
//    }
    
//    json Mismatches2 = json::object();
//    json Sample2 = json::object();
//    int count2 = 0;
//    bool flag2 = false;
//    for(int i = 0; i < size; ++i) {
//        if(sample2.at(i) != sample4.at(i)) {
////            count++;
//            flag2 = true;
//            count2++;
//            Mismatches1 += {to_string(count2), {sample2.at(i), sample4.at(i)}};
//        }
//    }
//    if(flag2) {
//        count++;
//        Sample2 = {{argv[1], jsonObject1["Sample2"]}, {argv[2], jsonObject2["Sample2"]}, {"Mismatches", Mismatches2}};
//        result += {"Sample2", Sample2};
//    }
//    cout << result;
    json File1;
    json File2;
    json metadata;
    int s1, n1, s2, n2;
//    cout << jsonObject1["metadata"]["arraySize"];
    s1 = jsonObject1["metadata"]["arraySize"];
    n1 = jsonObject1["metadata"]["numSamples"];
    s2 = jsonObject2["metadata"]["arraySize"];
    n2 = jsonObject2["metadata"]["numSamples"];
    File1["arraySize"] = s1;
    File1["numSamples"] = n1;
    File1["name"] = argv[1];
    File2["arraySize"] = s2;
    File2["numSamples"] = n2;
    File2["name"] = argv[2];
    metadata = {
        {"File1", File1},
        {"File2", File2},
        {"samplesWithConflictingResults", count}
    };
    result["metadata"] = metadata;

    cout << result << endl;
}
