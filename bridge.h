/*-----------------------------------------------
Filename: bridge.h
Author: Kelsey Cole
Purpose: Define class Bridge
------------------------------------------------*/

#ifndef BRIDGE_H
#define BRIDGE_H
#include "port.h"
typedef tuple <int, int, int> intTuple;

class Bridge {
	public : 
		Bridge(int bridge_id, pair <int, string> csource, intTuple bconfig, vector<Port> port_connections);
		int getId();
		void printBridge();
		void addPort(Port new_port);
		vector<Port>::iterator findPort(string port_id); 
		//node identity information
		int id;
		//node state information
		pair <int, string> config_source; //which node/port gave the best config info
		vector<Port> connected_ports; //the ports this bridge is connected to
		// ID of identified root - distance to root - ID of sending bridge
		intTuple  best_config; //best configuration for this bridge
};
#endif
