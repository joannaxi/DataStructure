//
//  main.cpp
//  E3
//
//  Created by WENXI LU on 2/11/19.
//  Copyright © 2019 WENXI LU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "json.hpp"
#include "insertionsort.h"
//#include "insertionsort.cpp"
#include "quicksort.h"
//#include "quicksort.cpp"
#include "mergesort.h"
//#include "mergesort.cpp"

using namespace std;
extern int InsertionSortCompareCount;
extern int InsertionSortMemoryCount;
extern int MergeSortCompareCount;
extern int MergeSortMemoryCount;
extern int QuickSortCompareCount;
extern int QuickSortMemoryCount;

int main(int argc, char** argv) {
    void InsertionSort(std::vector<int>* numbers);
    void MergeSort(std::vector<int>* numbers);
    void MergeSortRecurse(std::vector<int>* numbers, int i, int k);
    void Merge(std::vector<int>* numbers, int i, int j, int k);
    void QuickSort(std::vector<int>* numbers);
    int Partition(std::vector<int>* numbers, int i, int k);
    int countComp(std::vector<int>* numbers);
    using json = nlohmann::json;

    string str(argv[1]);
//    string filename = "/Users/wenxilu/Desktop/p2/p2_files/Autograder/TestCases/" + str;
 //   string filename = "/Users/wenxilu/Desktop/p2/p2_files/" + str;
    string filename = str;
    std::ifstream file;
    file.open(filename);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }
    int size = jsonObject["metadata"]["numSamples"];
    int time1[size];
    int compare1[size];
    int memory1[size];
    int time2[size];
    int compare2[size];
    int memory2[size];
    int time3[size];
    int compare3[size];
    int memory3[size];
    string name[size];

//    InsertionSort
    clock_t time_req1;
    int i = 0;
    int p = 0;
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        string sample = itr.key();
        name[i] = sample;
        i++;
        if(sample == "metadata") {
            continue;
        }
        vector<int> vec1;
        for (auto arrayItr = jsonObject[sample].begin();
             arrayItr != jsonObject[sample].end();
             ++arrayItr) {
            vec1.push_back(*arrayItr);
        }
//        int size = (int)vec1.size();
//        int i = 0;
        time_req1 = clock();
        InsertionSortCompareCount = 0;
        InsertionSortMemoryCount = 0;
        //int ctem1 = 0;
	//int mtem1 = 0;
	InsertionSort(&vec1);
        time_req1 = clock() - time_req1;
        time1[p] = (float)time_req1/CLOCKS_PER_SEC;
        compare1[p] = InsertionSortCompareCount;
        memory1[p] = InsertionSortMemoryCount;
       // ctem1 = InsertionSortCompareCount;
	//mtem1 = InsertionSortMemoryCount;
	//compare1[p] = ctem1;
	//memory1[p] = mtem1;
       	p++;
//        cout << (float)time_req1/CLOCKS_PER_SEC  << "," << InsertionSortCompareCount << "," << InsertionSortMemoryCount << endl;
        
    }
    
//    MergeSort
    int j = 0;
    clock_t time_req2;
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        string sample = itr.key();
        if(sample == "metadata") {
            continue;
        }
        vector<int> vec2;
        for (auto arrayItr = jsonObject[sample].begin();
             arrayItr != jsonObject[sample].end();
             ++arrayItr) {
            vec2.push_back(*arrayItr);
        }
//        int size = (int)vec2.size();

//        int i = 0;
        time_req2 = clock();
        MergeSortCompareCount = 0;
        MergeSortMemoryCount = 0;
        MergeSort(&vec2);
        time_req2 = clock() - time_req2;
        time2[j] = (float)time_req2/CLOCKS_PER_SEC;
        compare2[j] = MergeSortCompareCount;
        memory2[j] = MergeSortMemoryCount;
        j++;
//        cout << (float)time_req2/CLOCKS_PER_SEC  << "," << MergeSortCompareCount << "," << MergeSortMemoryCount << endl;
    }
    
//    QuickSort
    int k = 0;
    clock_t time_req3;
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        string sample = itr.key();
        if(sample == "metadata") {
            continue;
        }
        vector<int> vec3;
        for (auto arrayItr = jsonObject[sample].begin();
             arrayItr != jsonObject[sample].end();
             ++arrayItr) {
            vec3.push_back(*arrayItr);
        }
//        int size = (int)vec3.size();

//         int i = 0;
        time_req3 = clock();
        QuickSortCompareCount = 0;
        QuickSortMemoryCount = 0;
        QuickSort(&vec3);
        time_req3 = clock() - time_req3;
        time3[k] = (float)time_req3/CLOCKS_PER_SEC;
        compare3[k] = QuickSortCompareCount;
        memory3[k] = QuickSortMemoryCount;
        k++;
//        cout << (float)time_req3/CLOCKS_PER_SEC  << "," << QuickSortCompareCount << "," << QuickSortMemoryCount << endl;
    }
    
    
    // create an ofstream for the file output (see the link on streams for
    // more info)
    ofstream outputFile;
    // create a name for the file output
    std::string outputfilename = "Output.csv";
    
    // create some variables for demonstration

    // create and open the .csv file
    outputFile.open(outputfilename);
    
    // write the file headers
    outputFile << "Sample" << "," << "InsertionSortTime" << "," << "InsertionSortCompares" << "," << "InsertionSortMemaccess" << "," << "MergeSortTime" << "," << "MergeSortCompares" << "," << "MergeSortMemaccess" << "," << "QuickSortTime" << "," << "QuickSortCompares" << "," << "QuickSortMemaccess" << std::endl;
    
    // i is just a variable to make numbers with in the file

    
    // write data to the file
    for (int count = 0; count < size; count++)
    {
        
        // write the data to the output file
        outputFile << name[count] << "," << time1[count] << "," << compare1[count] << "," << memory1[count] << "," << time2[count] << "," << compare2[count] << "," << memory2[count] << "," << time3[count] << "," << compare3[count] << "," << memory3[count] << std::endl;
        

    }
    
    // close the output file
    outputFile.close();
}
