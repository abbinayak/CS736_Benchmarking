chmod +x tcp_server_local.sh
#LATENCY TESTING FOR TCP LOCAL
make
#Running on rockhopper-05
#Local:
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./server -p 9005 -b 4


