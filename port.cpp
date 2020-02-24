/*-----------------------------------------------
Filename: port.cpp
Author: Kelsey Cole
Purpose: implement class Port
------------------------------------------------*/
#include "port.h"

 Port :: Port(string port_id, intTuple port_config){

    id = port_id;
    best_config = port_config;
 }

//----------------------------------addBridge
// add bridge to the connected bridges list
 void Port :: addBridge(int bridge_id){
    this->connected_bridges.push_back(bridge_id);
 }

//----------------------------------isConnected
// determine whether a port is connected to a bridge given the bridge id
bool Port :: isConnected(int bridge_id){
    for (auto it = this->connected_bridges.begin(); it != this->connected_bridges.end(); it++){ 
        if (*it == bridge_id){
            return true;
        }
    }
    return false;
 }
//----------------------------------printPoty
 void Port :: printPort(){
    cout << "port " << this->id << ": <" << get<0>(best_config) << ", " 
    << get<1>(best_config) << ", " << get<2>(best_config) << "> " << this->open_or_closed << endl;
 }

//----------------------------------updateConfig
//update the best configuration for this port
 void Port :: updateConfig(intTuple port_config){
    get<0>(this->best_config) = get<0>(port_config);
    get<1>(this->best_config) = get<1>(port_config);
    get<2>(this->best_config) = get<2>(port_config);
 }

//----------------------------------compareRoots
//compare root IDs with this port given a message
int Port :: compareRoots(intTuple message){
    if(get<0>(this->best_config) > get<0>(message)){
        return 1;
    }
    if(get<0>(this->best_config) == get<0>(message)){
        return 0;
    }
    return -1;
 }

//----------------------------------compareDistance
//compare distance with this port given a message
 int Port :: compareDistance(intTuple message){
    if(get<1>(this->best_config) > get<1>(message)){
        return 1;
    }
    if(get<1>(this->best_config) == get<1>(message)){
        return 0;
    }
    return -1;
 }

//----------------------------------compareSendingNode
//compare the ID of a sending node with this port given a message
  int Port :: compareSendingNode(intTuple message){
    if(get<2>(this->best_config) > get<2>(message)){
        return 1;
    }
    if(get<2>(this->best_config) == get<2>(message)){
        return 0;
    }
    return -1;
  }