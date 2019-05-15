# KeyValueStore
KeyValueStore is a command line tool to provide a key-value management system. It allows client to add, update key-value pairs & to get a value for corresponding key. Further, it exposes a watch functionality on a key, which informs the client about any update on the value of the key under consideration. It is a multithreaded application with TCP/IP protocol based sockets built for Server-Client communication and Reader-Writer locks on keys for concurrent transaction management. 

# Build
Building Server:
* cd src/bin
* g++ -std=c++11 server.cpp -o server

Building Client:
* cd src/bin
* g++ client.cpp -o kv

# Run
Server:
  ./server
  
Client:
  ./kv command arguements
  
# Client Commands
* put key value
* get key
* watch key
  
**Note: Enter the same port no. on client & server side for application to run the application smoothly.


# Design
* KeyValueStore - It gives a HashMap implementation for key-value pair storage. Exposes put & get methods for adding or updating a key-value pair & to get a value for a key respectively.
* KeyValueStoreManager - It gives a Reader Writer lock based control on get & put commands for concurrent execution of commands by multiple clients.
* Parser - Server-client communicate via string buffer. Parser provides capability to validate the string buffer command & edits an array of strings for appropriate command handling by the ClientHandler in Server.
* ClientServerUtilities - Exposes functionalities to enhance the string & character buffer management for server & client.
* server & client - Communicate via TCP/IP based sockets for reliable data transfer via character buffer with limit of
 1024 characters. server is a multithreaded endpoint to serve the reqests by multiple clients by continuos thread management by clientHandler & watch command is handled on the client side by this mechanism smoothly.
 
# Future Design Improvement & Implementation
* In memory store of key-value pair. Constructor & Destructors to read to the keyPair HashMap from a file & to write respectively. To enhance memory management & failover handling.
* Code refactoring for 'client.cpp' & 'server.cpp' for code redundancy reduction & code cleanup.
* Server - client communication limited to a packet size of 1024 characters (including the commandtype followed by its arguements). To refactor and increase packet size for large sized key & value .  
* Addition of configuration class or configuration file to store configurable values like PACKET_SIZE, PORT, etc.
