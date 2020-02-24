/*-----------------------------------------------
            Program Name: Spanning Tree
--------------------------------------------------
Filename: main.cpp
Author: Kelsey Cole
Compilation: Use the provided makefile.
Purpose: Use classes Bridge and Port to implement
the distributed minimum spanning tree algorithm
given a LAN file. 
------------------------------------------------*/
#include <fstream>
#include <string>
#include "bridge.h"

int main(int argc, char* argv[]){
    //-----------------------------------------------------parse command line arguments
    vector<int> msg_order;
    for (int i = 2; i < argc; i++){
        msg_order.push_back(stoi(argv[i]));
    }

    //------------------------------------------------------------------------Read in LAN file (data processing)
    // and store bridge information in class Bridge
    string filename = argv[1];
    ifstream lanfile;
    lanfile.open(filename);	 //open the filename provided by the command line
    vector<Bridge> bridgesList; //list of all the bridges
    vector<Port> portsList; //keeps track of ports creation, to ensure consistency of copies
    string temp; //used as temporary storage for data processing
    if(lanfile.is_open()){
        while(!lanfile.eof()){		
            //retrieve one line of file for parsing
            getline(lanfile, temp);

            if (temp != ""){
                //parse string for ports
                string tok;	
                size_t pos = 0;	
                string delimiter = " "; //distinguish port ids by spaces
                int counter = 0;
                int temp_id = 0;
                vector<Port> connections; 
                //parse string by the delimiter
                while ((pos = temp.find(delimiter)) != string::npos) {
                    tok = temp.substr(0, pos); //split string into tokens
                    if (counter == 0){ //if the counter is 0, this is the first token
                        temp_id = stoi(tok); //so this is the bridge ID, which is an int . . . so we convert it			
                    } else {
                        bool alreadyCreated = false; //check if this port has already been created for another node
                        for (auto portsit = portsList.begin(); portsit != portsList.end(); portsit++){ 
                            if (portsit->id == tok){
                                alreadyCreated = true; //if so, add the same copy of that port to this node
                                portsit->addBridge(temp_id);
                                connections.push_back(*portsit);
                            }
                        }
                        if (!alreadyCreated){ //create new port
                            intTuple temp_config (temp_id, 0, temp_id);
                            Port temp_port(tok,temp_config);
                            temp_port.addBridge(temp_id);
                            portsList.push_back(temp_port);
                            connections.push_back(temp_port);
                        }

                    }
                    temp.erase(0, pos + delimiter.length()); //erase processed data
                    counter++;	
                }
                //process the last token
                bool alreadyCreated = false;
                for (auto portsit = portsList.begin(); portsit != portsList.end(); portsit++){ 
                    if (portsit->id == temp){
                        alreadyCreated = true;
                        portsit->addBridge(temp_id);
                        connections.push_back(*portsit);
                    }
                }
                if (!alreadyCreated){ //create new port
                    intTuple temp_config (temp_id, 0, temp_id);
                    Port temp_port(temp,temp_config);
                    temp_port.addBridge(temp_id);
                    portsList.push_back(temp_port);
                    connections.push_back(temp_port);
                }

                //create the bridge
                intTuple temp_tuple (temp_id, 0, temp_id);
                pair <int, string> temp_config(temp_id, "");		
                
                //add the bridge to the Bridges list
                Bridge temp_bridge(temp_id, temp_config, temp_tuple, connections);
                bridgesList.push_back(temp_bridge);	
            }
        }	
    }

    lanfile.close();
    //------------------------------------------------------------------END DATA PROCESSING

    //------------------------------------------------------------------SPANNING TREE ALGORITHM

    //PROCESS EACH MESSAGE
    for (auto it = msg_order.begin(); it != msg_order.end(); it++){ 
        //-----------------------------------------get the current message of the sending node
        intTuple message;
        vector<Port> sending_node_configs;
        for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
            if (bridgeit->id == *it){ //this is the sending node if true
                message = bridgeit->best_config;
                if(bridgeit->id != get<0>(bridgeit->best_config)){
                    get<1>(message)++;
                }
                get<2>(message) = *it;
                //for each port connected to this node
                for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                    //-----------------------------------------------------------send the message
                        if (portsit->compareRoots(message) == 1){ //if the root is smaller
                            portsit->updateConfig(message); //change best config
                        } else if (portsit->compareRoots(message) == 0){ //if the root is the same
                            if (portsit->compareDistance(message) == 1){ //and the distance is smaller
                                portsit->updateConfig(message); //change config
                            } else if (portsit->compareDistance(message) == 0){ //and the distance is the same
                                if(portsit->compareSendingNode(message) == 1){ //but sending node is smaller
                                    portsit->updateConfig(message); //change best config
                                }
                            }
                    }
                    //if none of the criteria was met, this is not a better message
                    //so we ignore it
                }
                //keep track of port changes in order to sync all other copies of the port
                for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                    sending_node_configs.push_back(*portsit);
                }
            }
        }
        //--------------------------------------sync all the other copies of the port with this node's copy
        for (auto conit = sending_node_configs.begin(); conit != sending_node_configs.end(); conit++){
            for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
                if(conit->isConnected(bridgeit->id)){
                    vector<Port>::iterator found_port = bridgeit->findPort(conit->id);
                    intTuple found_port_msg = conit->best_config;
                    found_port->updateConfig(found_port_msg);
                }
            }
        }

        //-----------------------------------------------update nodes' best configs according to their ports
        for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
                for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                        intTuple this_ports_config = portsit->best_config;
                         //if(get<2>(message) != bridgeit->id){ 
                            // get<1>(message)++;
                        //}
                        if (portsit->compareRoots(bridgeit->best_config) == -1){
                            (bridgeit->config_source).second = portsit->id;
                            bridgeit->best_config = this_ports_config;
                        } else if (portsit->compareRoots(bridgeit->best_config) == 0){
                            if (portsit->compareDistance(bridgeit->best_config) == -1){
                                (bridgeit->config_source).second = portsit->id;
                                bridgeit->best_config = this_ports_config;
                            } else if (portsit->compareDistance(bridgeit->best_config) == 0){
                                if(portsit->compareSendingNode(bridgeit->best_config) == -1){
                                    (bridgeit->config_source).second = portsit->id;
                                    bridgeit->best_config = this_ports_config;
                                }
                            }
                    }
                }
        }
        //--------------------------------------------update each port according to their updated node configs
        for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
                for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                    message = bridgeit->best_config;
                    get<1>(message)++;
                    get<2>(message) = bridgeit->id;
                    // process the message
                        if (portsit->compareRoots(message) == 1){
                            portsit->updateConfig(message);
                        } else if (portsit->compareRoots(message) == 0){
                            if (portsit->compareDistance(message) == 1){
                                portsit->updateConfig(message);
                            } else if (portsit->compareDistance(message) == 0){
                                if(portsit->compareSendingNode(message) == 1){
                                    portsit->updateConfig(message);
                                }
                            }
                    }
                
                }
        }       

    }
    //determine which ports should be open 
        for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
            for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                if (get<2>(portsit->best_config) == bridgeit->id){
                    portsit->open_or_closed = "open";
                    
                }
                else if(bridgeit->config_source.second == portsit->id){
                    portsit->open_or_closed = "open";
                    
                } else {
                portsit->open_or_closed = "closed";
                }
            }
        }
    //------------------------------------------------------------------END SPANNING TREE ALGORITHM
    //-----------------------------------------------------------------------print results
    for (auto it = bridgesList.begin(); it != bridgesList.end(); it++){
        it->printBridge();
        for (auto portsit = it->connected_ports.begin(); portsit != it->connected_ports.end(); portsit++){
                portsit->printPort();
        }
    }

    return 0;
}
						