/*-----------------------------------------------
Filename: bridge.cpp
Author: Kelsey Cole
Purpose: implement class Bridge
------------------------------------------------*/
#include "bridge.h"

Bridge :: Bridge(int bridge_id, pair <int, string> csource, intTuple bconfig, vector<Port> port_connections){
	id = bridge_id;
	config_source = csource;
	best_config = bconfig;
	for (auto portsit = port_connections.begin(); portsit != port_connections.end(); portsit++){
		connected_ports.push_back(*portsit);
	}
}
//----------------------------------getId
//get the bridge's id
int Bridge :: getId(){
	return this->id;
}
//----------------------------------addPort
// add a port to the connected ports vector
void Bridge :: addPort(Port new_port){
	this->connected_ports.push_back(new_port);
}

//----------------------------------findPort
//find a port in the connected ports list given an id
//and return and iterator to it
vector<Port>::iterator Bridge :: findPort(string port_id){
		for (auto portsit = connected_ports.begin(); portsit != connected_ports.end(); portsit++){
			if(portsit->id == port_id){
				return portsit;
			}
	}
}

//----------------------------------printBridge
void Bridge :: printBridge(){
	cout << "Bridge " << this->id << ": best configuration <" << get<0>(this->best_config) 
	<< ", " << get<1>(this->best_config) << ">, from " << get<2>(this->best_config);
	if (this->config_source.second != ""){
		cout << " via " << this->config_source.second;
	}
	cout << endl;
}