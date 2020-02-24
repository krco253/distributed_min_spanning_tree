#include "bridge.h"

Bridge :: Bridge(int bridge_id, pair <int, string> csource, intTuple bconfig, vector<Port> port_connections){
	id = bridge_id;
	config_source = csource;
	best_config = bconfig;
	for (auto portsit = port_connections.begin(); portsit != port_connections.end(); portsit++){
		connected_ports.push_back(*portsit);
	}
}

int Bridge :: getId(){
	return this->id;
}
void Bridge :: addPort(Port new_port){
	this->connected_ports.push_back(new_port);
}

vector<Port>::iterator Bridge :: findPort(string port_id){
		for (auto portsit = connected_ports.begin(); portsit != connected_ports.end(); portsit++){
			if(portsit->id == port_id){
				return portsit;
			}
	}
}
void Bridge :: printBridge(){
	cout << "Bridge " << this->id << ": best configuration <" << get<0>(this->best_config) << ", " << get<1>(this->best_config) << ">, from " << get<2>(this->best_config) << endl;
}