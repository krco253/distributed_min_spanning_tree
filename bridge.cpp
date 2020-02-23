#include "bridge.h"

Bridge :: Bridge(int bridge_id, pair <int, string> csource, intTuple bconfig, vector<Port> port_connections){
	id = bridge_id;
	config_source = csource;
	best_config = bconfig;
	for (auto portsit = port_connections.begin(); portsit != port_connections.end(); portsit++){
		connected_ports.push_back(*portsit);
	}
}
// Overload = operator
// Bridge Bridge :: operator+(const Bridge& b) {
//          Bridge bridge;
//          	id = bridge_id;
// 	for (auto it = this->ports.begin(); it != this->ports.end(); it++){ 
//         	bridge.ports.push_back(*it); 	
// 	}
// 	bridge.config_source = this->config_source;
// 	bridge.best_config = this->best_config;
// 	bridge.config_source = this->config_source;
// 	for (auto it = this->port_configs.begin(); it != this->port_configs.end(); it++){ 
//         	bridge.port_configs.push_back(*it); 	
// 	}
// 	for (auto it = this->port_openings.begin(); it != this->port_openings.end(); it++){ 
//         	bridge.port_openings.push_back(true); 	
// 	}	

//     return bridge;
// }

int Bridge :: getId(){
	return this->id;
}
void Bridge :: addPort(Port new_port){
	this->connected_ports.push_back(new_port);
}
void Bridge :: printBridge(){
	cout << "Bridge " << this->id << ": best configuration <" << get<0>(this->best_config) << ", " << get<1>(this->best_config) << ">, from " << get<2>(this->best_config) << endl;
}
// void Bridge :: printBestConfigs(){
// 	cout << "Bridge " << this->id << ": best configuration <" << get<0>(this->best_config) << ", " << get<1>(this->best_config) << ">, from " << get<2>(this->best_config) << endl;
// 	int port_count = 0;
// 	for (auto it = this->ports.begin(); it != this->ports.end(); it++){ 
//         	cout << "Port " << *it << ": <" << get<0>(this->port_configs[port_count]) << ", " << get<1>(this->port_configs[port_count]) << ", " << get<2>(this->port_configs[port_count]) << "> ";
// 		if(this->port_openings[port_count] == true)
// 			cout << "open" << endl;
// 		else 
// 			cout << "closed" << endl;
// 		port_count++;
// 	}
// }	
