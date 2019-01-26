//
//  main.cpp
//  SearchNewBooks
//
//  Created by WENXI LU on 1/20/19.
//  Copyright © 2019 WENXI LU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>// NOLINT (build/c++11)

class Books{
 public:
    int ISNB;
    std::string type;
    static bool before(const Books& c1, const Books& c2)
    {return c1.ISNB < c2.ISNB || (c1.ISNB == c2.ISNB && c1.type < c2.type);}
    friend std::ostream& operator<<(std::ostream& os, const Books& book);
};

bool operator<( const Books& c1, const Books& c2 ) { return c1.ISNB > c2.ISNB; }

std::ostream& operator<<(std::ostream& os, const Books& book) {
    os << book.ISNB << ',' << book.type;
    return os;
}


std::vector<Books> readFile(std::ifstream & myfile) {
    if (!myfile) {
        std::cout << "Error: cannot open file" << &myfile << std::endl;
        exit(1);
    }
    std::string str;
    std::vector<Books> books;
    // Read the next line from File untill it reaches the end.
    while (getline(myfile, str)) {
        Books book;
        int pos = str.find(",", 0);
        std::string token1 = str.substr(0, pos);
        int token = std::stoi(token1);
        std::string token2 = str.substr(pos+1, str.size()-1);
        book.ISNB = token;
        book.type = token2;
        books.push_back(book);
    }
    myfile.close();
    return books;
}
int linearSearch(std::vector<Books> newBook, std::vector<Books> request);
int binarySearch(std::vector<Books> newBook, std::vector<Books> request);
int linearSearch(std::vector<Books> newBook, Books book) {
    int location = -1;
    for (int i = 0; i < static_cast<int>(newBook.size()); ++i) {
        if (book.ISNB == newBook[i].ISNB && book.type == newBook[i].type) {
            return location = i;
        }
    }
    return location = -1;
}
int binarySearch(std::vector<Books> newBook, Books book) {
    int l = 0;
    int r = static_cast<int>(newBook.size()) - 1;
    while (l < r) {
        int m = (l + r)/2;
        if (book.ISNB > newBook[m].ISNB) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    int location;
    if (book.ISNB == newBook[l].ISNB && book.type == newBook[l].type) {
        location = l;
    } else {
        location = -1;
    }
    return location + 1;
}
int main(int argc, const char * argv[]) {
    const char * f1 = argv[1];
    const char * f2 = argv[2];
  // std:: string path = "/Users/wenxilu/Desktop/ECS36C/ECS36C/p1/";
    if(argc < 3){
        std::cout << "Usage:" << argv[0] << std::endl;
        exit(1);
    }
    std::ifstream myfile_newBook;
    myfile_newBook.open(f1);
    std::ifstream myfile_requested;
    myfile_requested.open(f2);
    std::vector<Books> newBook;
    std::vector<Books> request;
    newBook = readFile(myfile_newBook);
    request = readFile(myfile_requested);
    int count = 0;
    bool flag = true;
    while (flag) {
        std::cout << "Choice of search method ([l]inear, [b]inary)?" << "\n";
        char in;
        std::cin >> in;
        if (in == 'l') {
            std::chrono::high_resolution_clock::time_point start;
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < static_cast<int>(request.size()); ++i) {
                int location = linearSearch(newBook, request[i]);
                if (location != -1) {
                    count = count + 1;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>
(end - start).count();
            std::cout << "CPU time: " << elapsed_us <<
" microseconds" << std::endl;
            flag = !flag;
        } else if (in == 'b') {
            std::chrono::high_resolution_clock::time_point start;
            start = std::chrono::high_resolution_clock::now();
            std::sort(newBook.begin(), newBook.end());
            std::sort(newBook.begin(), newBook.end(), Books::before);
            for (int i = 0; i < static_cast<int>(request.size()); ++i) {
                int location = binarySearch(newBook, request[i]);
                if (location != -1) {
                    count = count + 1;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>
 (end - start).count();
std::cout << "CPU time: " << elapsed_us <<
" microseconds" << std::endl;
flag = !flag;
    } else {
            std::cerr << "Incorrect choice" << std::endl;
        }
    }
  //        Phase 4: Writing the result;
    std::ofstream myfile;
    const char* fileName = argv[3];
    myfile.open(fileName);
    myfile << count << "\n";
    myfile.close();
    return 0;
}
