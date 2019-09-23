chmod +x run_tcp.sh
#LATENCY TESTING FOR TCP LOCAL AND REMOTE
cd Latency
make
#Running on rockhopper-05
#Local:
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./server -p 9005 -b 4
./client -a 128.105.37.195 -p 9005 -b 4

#Remote: Running on rockhopper-03 and rockhopper-06
#Client: rockhopper-03 and Server rockhopper-06
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b

./server -p 9005 -b 4
./client -a 128.105.37.196 -p 9005 -b 4

#THROUGHPUT TESTING FOR TCP LOCAL AND REMOTE
cd ..
cd Throughput
make
#Running on rockhopper-05
#Local:
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./server_thr -p 9006 -b 4
./client_thr -a 128.105.37.195 -p 9006 -b 4

#Remote: Running on rockhopper-03 and rockhopper-06
#Client: rockhopper-03 and Server rockhopper-06
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b

./server_thr -p 9006 -b 4
./client_thr -a 128.105.37.196 -p 9006 -b 4
