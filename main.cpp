#include <fstream>
#include <string>
#include "bridge.h"

int main(int argc, char* argv[]){
    //-----------------------------------------------------store order of nodes sending messages
    vector<int> msg_order;
    for (int i = 2; i < argc; i++){
        msg_order.push_back(stoi(argv[i]));
    }

    //------------------------------------------------------------------------Read in LAN file (data processing)
    // and store bridge information in class Bridge
    string filename = argv[1];
    ifstream lanfile;
    lanfile.open(filename);	
    vector<Bridge> bridgesList;
    vector<Port> portsList;
    string temp;
    if(lanfile.is_open()){
        while(!lanfile.eof()){		
            getline(lanfile, temp);
            if (temp != ""){
                // cout << temp << endl;
                //parse string for ports
                string token;	
                size_t pos = 0;	
                string delimiter = " ";
                int counter = 0;
                int temp_id = 0;
                vector<Port> connections;
                while ((pos = temp.find(delimiter)) != string::npos) {
                    token = temp.substr(0, pos);
                    if (counter == 0){
                        temp_id = stoi(token);		
                        //cout << "id: " << temp_id << endl;	
                    } else {
                        bool alreadyCreated = false;
                        for (auto portsit = portsList.begin(); portsit != portsList.end(); portsit++){ 
                            if (portsit->id == token){
                                alreadyCreated = true;
                                portsit->addBridge(temp_id);
                                connections.push_back(*portsit);
                            }
                        }
                        if (!alreadyCreated){ //create new port
                            intTuple temp_config (temp_id, 0, temp_id);
                            Port temp_port(token,temp_config);
                            temp_port.addBridge(temp_id);
                            portsList.push_back(temp_port);
                            connections.push_back(temp_port);
                        }

                    }
                    temp.erase(0, pos + delimiter.length()); //erase processed data
                    counter++;	
                }
                //process the last character
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
                pair <int, string> temp_config(temp_id, "A");		
                        
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
        //get the message from the bridges list
        intTuple message;
        vector<Port> sending_node_configs;
        for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
            if (bridgeit->id == *it){
                message = bridgeit->best_config;

            }
        }
        for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){
                // get<2>(message) = *it;
                //for each port connected to the bridge
                for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                    // //process the message
                    // cout << portsit->id << " " << bridgeit->id << endl;
                    // cout << get<0>(portsit->best_config) << " " << get<0>(message) << " " << get<1>(portsit->best_config) << " " << get<1>(message) << " " << get<2>(portsit->best_config) << " " << get<2>(message) << endl;
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
                //update this node's config
                for (auto portsit = bridgeit->connected_ports.begin(); portsit != bridgeit->connected_ports.end(); portsit++){
                        intTuple this_ports_config = portsit->best_config;
                        if (portsit->compareRoots(message) == -1){
                            bridgeit->best_config = this_ports_config;
                        } else if (portsit->compareRoots(message) == 0){
                            if (portsit->compareDistance(message) == -1){
                                bridgeit->best_config = this_ports_config;
                            } else if (portsit->compareDistance(message) == 0){
                                if(portsit->compareSendingNode(message) == -1){
                                    bridgeit->best_config = this_ports_config;
                                }
                            }
                    }
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



    //     for (auto it = bridgesList.begin(); it != bridgesList.end(); it++){ 
    //    (*it).printBestConfigs();	
    // }		 
    //---------------------------------------Spanning Tree Algorithm
    // for (auto it = msg_order.begin(); it != msg_order.end(); it++){ //for each node that sends a message
    //     vector<string> node_ports;
    //     intTuple message;
    //     // cout << *it << endl;
    //     //find the node in the bridges list
    //     for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){ 
    //         if (*it == (*bridgeit).id){
    //             //save the node's current message
    //             message = (*bridgeit).best_config;
    //            for (auto portit = (*bridgeit).ports.begin(); portit != (*bridgeit).ports.end(); portit++){ 
    //                //find which ports its connected to
    //                node_ports.push_back(*portit);
    //            }
    //            break;
    //         }
    //     }

    //     //see what other nodes each port is connected to
    //     for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){ //for each node
    //    // cout << "made it" << endl;
    //             for (auto nportit = node_ports.begin(); nportit != node_ports.end(); nportit++){ 
    //             int cur_port_num = 0;
    //                 for (auto portit = (*bridgeit).ports.begin(); portit != (*bridgeit).ports.end(); portit++){ //check its ports to see if it's connected to the messaging node
    //                 if (*portit == *nportit){ //these ports are the same
    //                     // cout << *portit << " " << *nportit << endl;
    //                     //now check if this configuration is better than the current one at the port
    //                     intTuple cur_config = (*bridgeit).port_configs[cur_port_num];
    //                     //---------------------------------------------------------------------------------update best config for port
    //                     if (get<0>(cur_config) == get<0>(message)){ //if the roots are the same
    //                         if (get<1>(cur_config) == get<1>(message)){ //and the distance is the same 
    //                             if (get<2>(cur_config) > get<2>(message)){ //but sending node has smaller id
    //                             intTuple new_config (get<0>(message), get<1>(message), *it); //change config
    //                             bridgeit->port_configs[cur_port_num] = new_config;
    //                             cout << get<0>(cur_config) << " " << get<0>(message) << endl;
    //                             } 
    //                         } 
    //                         if (get<1>(cur_config)+1 > get<1>(message)){ //and this message's distance is less
    //                             intTuple new_config (get<0>(message), get<1>(message), *it); //change config
    //                             bridgeit->port_configs[cur_port_num] = new_config;
                               
    //                         }
    //                     }
    //                     if (get<0>(cur_config) > get<0>(message)){ //if the root has a smaller id, this is a better config
    //                         intTuple new_config (get<0>(message), get<1>(message), *it);
    //                         bridgeit->port_configs[cur_port_num] = new_config;
    //                     }
                        
    //                 }    
                
    //             }
    //             cur_port_num++;
    //         }
    //     }
    //     //update best config for each bridge
    //     for (auto bridgeit = bridgesList.begin(); bridgeit != bridgesList.end(); bridgeit++){ 
    //         int cur_port_num = 0;
    //         for (auto portit = (*bridgeit).ports.begin(); portit != (*bridgeit).ports.end(); portit++){ 
    //             intTuple port_config = (*bridgeit).port_configs[cur_port_num]; 
    //             intTuple bridge_config = (*bridgeit).best_config;
    //             //compare the bridge's config with the port's config
    //             if (get<0>(port_config) == get<0>(bridge_config)){ //if the roots are the same
    //                 if (get<1>(port_config) == get<1>(bridge_config)){ //and the distance is the same 
    //                     if (get<2>(port_config) < get<2>(bridge_config)){ //but sending node has smaller id
    //                         intTuple new_config (get<0>(port_config), get<1>(port_config), get<2>(port_config));
    //                         bridgeit->port_configs[cur_port_num] = new_config;
    //                     } 
    //                 }
    //                 if (get<1>(port_config) < get<1>(bridge_config)){ //and this message's distance is less
    //                     intTuple new_config (get<0>(port_config), get<1>(port_config), get<2>(port_config));
    //                     bridgeit->port_configs[cur_port_num] = new_config;
    //                 }
    //             }
    //             if (get<0>(port_config) < get<0>(bridge_config)){ //if the root has a smaller id, this is a better config
    //                 intTuple new_config (get<0>(port_config), get<1>(port_config), get<2>(port_config));
    //                 bridgeit->port_configs[cur_port_num] = new_config;
    //             }
    //             cur_port_num++;
    //         }
    //     }
    //     //close ports appropriately
    // }

    // for (auto it = bridgesList.begin(); it != bridgesList.end(); it++){ 
    //    (*it).printBestConfigs();	
    // }		 

    return 0;
}
						