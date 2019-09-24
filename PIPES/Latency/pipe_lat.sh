chmod +x pipe_lat.sh

#LATENCY TESTING FOR PIPE
gcc pipe_lat.c -o pipe_lat

#Running on royal-10
#Usage: ./pipe_lat <message_size> <roundtrip_count>
#The below command considers 4 bytes message size
#The message size to be tested can be specified by changing the first argument
./pipe_lat 4 10000
