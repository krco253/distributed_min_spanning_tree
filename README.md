# README: spanning tree
## a program implemented in C++
## Author: Kelsey Cole

## Running the code 
The code can be compiled using the provided makefile. 

To run, use the following syntax:
`./spanning_tree <lan file name> <order of messages>`

For example, 

`./spanning_tree exampleLAN.txt 1 3 4 6 2 3 1 5`

runs Example #1 provided in the assignment description appendix. 

## LAN file input format
This program assumes that the LAN file will be formatted as specified in the project assignment
description, with each line of the file representing a bridge and its connected ports. It is assumed
that the beginning of each line contains the bridge ID followed by the IDs of the ports it is connected to.

## main.cpp
Reads a LAN file, Implements the distributed spanning tree algorithm using the classes Bridge and Port, then prints out the results.

## bridge.cpp
Defines a class Bridge. This class is used to create instances of Bridges. 
Bridges keep track of their id, connected Ports best configurations, their own best configurations, and  
the sources of this configuration. 

As implemented in main.cpp, multiple Bridges may contain "duplicate" copies of ports (i.e., if Bridge 1 and Bridge 2 are both connected to port A, both Bridge 1 and Bridge 2 will keep separate instances of Port A in their inner member "connected_ports" although it is meant to represent the same port). These are synced when a message is sent to ensure no confusion arises.

## port.cpp
Defines a class Port. This class is used to create instances of Ports. 
Ports keep track of their id, best configuration, list of bridges they're connected to, and whether they're opened or closed.