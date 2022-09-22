//
// Created by fireb on 4/26/2022.
//

#include "../include/json.hpp"
#include <fstream>
#include <queue>
#include <stack>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <limits>
#include <functional>
#include <utility>
#include <chrono>

using namespace std::chrono;

std::unordered_map<std::string, double> shortestPath(std::string startingPoint, std::unordered_map<std::string, std::vector<std::pair<double, std::string>>> adjacencyList);


int main(int argc, char **argv) {

        std::unordered_map<std::string, std::vector<std::pair<double, std::string>>> adjacencyList;

    std::ifstream ifs("../data/RC_2019-02-01_edges.ndjson");
    //std::ifstream ifs("test.json");
    std::string line;
    size_t record_count{0};

    while (std::getline(ifs, line)) {

        record_count++;

        auto json = nlohmann::json::parse(line);
        std::string firstVertex = json["i"];
        std::string secondVertex = json["j"];
        double weight = json["w"];

        if(adjacencyList.find(firstVertex) == adjacencyList.end()) {
            adjacencyList.insert({firstVertex, {{weight, secondVertex}}});
        }
        else {
            adjacencyList[firstVertex].push_back({weight, secondVertex});
        }

        if (adjacencyList.find(secondVertex) == adjacencyList.end()) {
            adjacencyList.insert({secondVertex, {{weight, firstVertex}}});
        }
        else {
            adjacencyList[secondVertex].push_back({weight, firstVertex});
        }

    }
    auto start = high_resolution_clock::now();

    std::unordered_map<std::string, double> currentPath = shortestPath("tacticalnuclearsloth", adjacencyList);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << duration.count() << std::endl;

}

// first add elements(pairs from vector) from chosen/specified key to priority queue
// after adding elements connected to chosen element to queue check all elements in queue for connections
// pop around after finishing the counting of elements
// after adding all elements from next element continue and check that queue does not already include that item
// if same element is found compare weights

using Pair = std::pair<double, std::string>;
class Compare {
public:
    int operator() (const Pair& left, const Pair& right) {
        return left > right;
    }
};

std::unordered_map<std::string, double> shortestPath(std::string startingPoint, std::unordered_map<std::string, std::vector<std::pair<double, std::string>>> adjacencyList) {


    std::priority_queue<Pair, std::vector<Pair>, Compare> compareQueue;

    std::unordered_map<std::string, double> distanceMap;

    auto it = adjacencyList.begin();

    double distance = std::numeric_limits<double>::max();

    while(it != adjacencyList.end()) {
        compareQueue.push(std::make_pair(distance, it->first));

        distanceMap.insert({it->first, distance});

        it++;
    }

    compareQueue.push(std::make_pair(0.0, startingPoint));
    distanceMap[startingPoint] = 0.0;


    int counter = 0;

    while(compareQueue.size() != 0) {

        std::string shortest = compareQueue.top().second;
        double compareValue = compareQueue.top().first;

        compareQueue.pop();

        if(compareValue == distanceMap[shortest]) {

            for (size_t i = 0; i < adjacencyList[shortest].size(); i++) {

                double alt = distanceMap[shortest] + adjacencyList[shortest][i].first;

                std::string currentNeighbourName = adjacencyList[shortest][i].second;

                if (alt < distanceMap[currentNeighbourName]) {
                    distanceMap[currentNeighbourName] = alt;
                    compareQueue.push({alt, currentNeighbourName});
                }
            }
        }
        counter++;
    }

    return distanceMap;

}
