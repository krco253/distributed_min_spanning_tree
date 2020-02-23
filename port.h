#ifndef PORT_H
#define PORT_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <tuple>
#include <utility>
using namespace std;
typedef tuple <int, int, int> intTuple;
class Port {
    public: 
        Port (string port_id, intTuple port_config);
        void addBridge(int bridge_id);
        bool isConnected(int bridge_id);
        void printPort();
        void updateConfig(intTuple port_config);
        int compareRoots(intTuple message);
        int compareDistance(intTuple message);
        int compareSendingNode(intTuple message);
        string id;
        intTuple best_config;
        vector<int> connected_bridges;

};

#endif