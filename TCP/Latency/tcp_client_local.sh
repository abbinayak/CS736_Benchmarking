chmod +x tcp_client_local.sh
#LATENCY TESTING FOR TCP LOCAL AND REMOTE
make
#Running on rockhopper-05
#Local:
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./client -a 128.105.37.195 -p 9005 -b 4

