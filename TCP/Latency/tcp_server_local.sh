chmod +x run_tcp.sh
#LATENCY TESTING FOR TCP LOCAL AND REMOTE
make
#Remote: Running on rockhopper-05 and rockhopper-06
#Client: rockhopper-05 and Server rockhopper-06
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./server -p 9005 -b 4


