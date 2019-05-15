# KeyValueStore
KeyValueStore is a command line tool to provide clients with putting a key-value management system. It allows client to add, update key-value pairs & to get a value for corresponding key. Further, it exposes a watch functionality on a key, which informs the client about any update on the value of the key under consideration. It is a multithreaded application with TCP/IP protocol based sockets built for Server-Client communication and Reader-Writer locks on keys for concurrent transaction management. 

#Build
Building Server:
* cd src/bin
* g++ -std=c++11 server.cpp -o server

Building Client:
* cd src/bin
* g++ client.cpp -o kv

#Run
Server:
  ./server
  
Client:
  ./kv <command> <arguements>
  
**Note: Enter the same port no. on client & server side for application to run the application smoothly.
