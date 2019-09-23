chmod +x run_udp.sh
#LATENCY TESTING FOR UDP LOCAL AND REMOTE
cd Latency
make
#Running on royal-19
#Local:
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./server -p 9005 -b 4
./client -a 128.105.37.159 -p 9005 -b 4

#Remote: Running on snares-02 and snares-05
#Client: snares-02 and Server snares-05
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b

./server -p 9006 -b 4
./client -a 128.105.37.225 -p 9006 -b 4

#THROUGHPUT TESTING FOR UDP LOCAL AND REMOTE
cd ..
cd Throughput
make
#Running on royal-19
#Local:
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b
./server_thr -p 9007 -b 4
./client_thr -a 128.105.37.159 -p 9007 -b 4

#Remote: Running on snares-02 and snares-05
#Client: snares-02 and Server snares-05
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b

./server_thr -p 9008 -b 4
./client_thr -a 128.105.37.225 -p 9008 -b 4
