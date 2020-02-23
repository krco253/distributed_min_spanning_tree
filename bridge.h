#ifndef BRIDGE_H
#define BRIDGE_H
#include "port.h"
typedef tuple <int, int, int> intTuple;

class Bridge {
	public : 
		Bridge(int bridge_id, pair <int, string> csource, intTuple bconfig, vector<Port> port_connections);
		// Bridge operator=(const Bridge&);
		int getId();
		void printBridge();
		void addPort(Port new_port);
		// void printBestConfigs();
		//node identity information
		int id;
		//node state information
		pair <int, string> config_source; //which node/port gave the best config info
		vector<Port> connected_ports;
		// ID of identified root - distance to root - ID of sending bridge
		intTuple  best_config;
};
#endif
