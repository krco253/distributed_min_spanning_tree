#include "port.h"

 Port :: Port(string port_id, intTuple port_config){

    id = port_id;
    best_config = port_config;
 }

 void Port :: addBridge(int bridge_id){
    this->connected_bridges.push_back(bridge_id);
 }

bool Port :: isConnected(int bridge_id){
    for (auto it = this->connected_bridges.begin(); it != this->connected_bridges.end(); it++){ 
        if (*it == bridge_id){
            return true;
        }
    }
    return false;
 }

 void Port :: printPort(){
    cout << "port " << this->id << ": <" << get<0>(best_config) << ", " 
    << get<1>(best_config) << ", " << get<2>(best_config) << "> " << this->open_or_closed << endl;
 }

 void Port :: updateConfig(intTuple port_config){
    get<0>(this->best_config) = get<0>(port_config);
    get<1>(this->best_config) = get<1>(port_config);
    get<2>(this->best_config) = get<2>(port_config);
 }

int Port :: compareRoots(intTuple message){
    if(get<0>(this->best_config) > get<0>(message)){
        return 1;
    }
    if(get<0>(this->best_config) == get<0>(message)){
        return 0;
    }
    return -1;
 }

 int Port :: compareDistance(intTuple message){
    if(get<1>(this->best_config) > get<1>(message)){
        return 1;
    }
    if(get<1>(this->best_config) == get<1>(message)){
        return 0;
    }
    return -1;
 }
  int Port :: compareSendingNode(intTuple message){
        // cout << get<0>(this->best_config) << " " << get<0>(message) << " " << get<1>(this->best_config) << " " << get<1>(message) << " " << get<2>(this->best_config) << " " << get<2>(message) << endl;
    if(get<2>(this->best_config) > get<2>(message)){
        return 1;
    }
    if(get<2>(this->best_config) == get<2>(message)){
        return 0;
    }
    return -1;
  }