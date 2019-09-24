chmod +x tcp_server_local.sh
#LATENCY TESTING FOR TCP LOCAL
make
#Usage: ./server -b <NUM OF BYTES> -p <PORT NUMBER>

#Running on rockhopper-05
#Local:
#The below commands considers 4 bytes message size
#The message size to be tested can be specified by changing the argument for -b
./server -p 9005 -b 4
