// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k);
int Partition(std::vector<int>* numbers, int i, int k);
//extern int QuickSortCompareCount;
//extern int QuickSortMemoryCount;
//int QuickSortCompareCountFunc(std::vector<int>* numbers, int QuickSortCompareCount);
