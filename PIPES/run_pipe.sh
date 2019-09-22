chmod +x run_pipe.sh
#LATENCY TESTING FOR PIPE
cd Latency
make
#Running on royal-10
#Usage: ./pipe_lat <message_size> <roundtrip_count>
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the first argument
./pipe_lat 4 10000


#THROUGHPUT TESTING FOR PIPE
cd ..
cd Throughput
make
#Running on royal-10
#Usage: ./pipe_thr <message_size> 
#We consider a data block of size 1M and the rounds are calculated based on that
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the first argument
./pipe_thr 4


