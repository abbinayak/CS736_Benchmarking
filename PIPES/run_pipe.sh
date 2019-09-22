chmod +x run_pipe.sh
#LATENCY TESTING FOR PIPE
cd Latency
make
#Running on royal-10
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./client -a 128.105.37.150 -p 9010 -b 4
./server -p 9010 -b 4

#THROUGHPUT TESTING FOR PIPE
cd ..
cd Throughput
make
#Running on royal-10
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./client_thr -a 128.105.37.150 -p 9012 -b 4
./server_thr -p 9012 -b 4

