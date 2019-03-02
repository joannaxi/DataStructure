#include "priorityqueue.h"
//#include "priorityqueue.cpp"
#include <iostream>
#include "json.hpp"
#include <fstream>

//#include "priorityqueue.h"
//#include "priorityqueue.cpp"
//#include <iostream>
////#include "json.hpp"
//#include <fstream>
#include <cmath>
#include <set>
#include <vector>

int main(int argc, char** argv) {
    using json = nlohmann::json;
    using namespace std;
    string str(argv[1]);
    string filename = str;
    std::ifstream file;
    file.open(filename);
    json jsonObject;
    //    json HeapResult;
    if (file.is_open()) {
        file >> jsonObject;
    }
//    int numplayers = jsonObject["metadata"]["numPlayers"];
    size_t max_size = jsonObject["teamStats"].size();
    //    cout << max_size;
    //    PriorityQueue team(max_size_):
    PriorityQueue team(max_size);
    //    std::vector<KeyValuePair> nodes_;
    //    PriorityQueue::PriorityQueue(std::size_t max_size) :
    
    //    vector<KeyValuePair> nodes_(max_size + 1, KeyValuePair());
    
    set<int> players;
    for(auto itr = jsonObject["teamStats"].begin(); itr != jsonObject["teamStats"].end(); ++itr) {
        //        cout << itr.value() << endl;
        
        json temp = itr.value();
        int id = temp["playerOne"];
        //        cout << i << endl;
        int jd = temp["playerTwo"];
        //        cout << j << endl;
        double winPercentage = temp["winPercentage"];
        Key key = abs(winPercentage - 50) * 100;
        //        cout << key << endl;
        Value value = make_pair(id, jd);
        KeyValuePair kv = make_pair(key, value);
        //        cout << kv.first << endl;
        //        cout << kv.second.first << endl;
        team.insert(kv);
        
    }
    
    KeyValuePair min = team.removeMin();
    //    cout << min.first << endl;
    json result;
    players.insert(min.second.first);
    players.insert(min.second.second);
    Value first = min.second;
    result["teams"] += first;
    //    cout << min.first <<endl;
    //    cout << result << endl;
    vector<int> vec;
    while(!team.isEmpty()) {
        min = team.removeMin();
        //        cout << min.first <<endl;
        if(!players.count(min.second.first)) {
            players.insert(min.second.first);
            vec.push_back(min.second.first);
        }
        if(!players.count(min.second.second)) {
            players.insert(min.second.second);
            vec.push_back(min.second.second);
        }
    }
    //    cout << vec.size() << endl;
    for(int in = 0; in < vec.size() - 1; in = in + 2) {
        //    cout << vec.at(in) << "," << vec.at(in + 1) << endl;
        Value value = make_pair(vec.at(in), vec.at(in + 1));
        result["teams"] += value;
    }
    
    cout << result << endl;
}
