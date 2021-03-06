/*-----------------------------------------------
Filename: port.h
Author: Kelsey Cole
Purpose: define class Port
------------------------------------------------*/
#ifndef PORT_H
#define PORT_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <tuple>
#include <utility>
#include <algorithm>
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

        //port information
        string id; //port id
        intTuple best_config; //port best configuration
        vector<int> connected_bridges; //bridges this port is connected to
        string open_or_closed; //whether the port is opened or closed

};

#endif