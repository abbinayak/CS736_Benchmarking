chmod +x run_pipe.sh
#LATENCY TESTING FOR PIPE
cd Latency
gcc pipe_lat.c -o pipe_lat
#Running on royal-10
#Usage: ./pipe_lat <message_size> <roundtrip_count>
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the first argument
./pipe_lat 4 10000


