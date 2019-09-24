#THROUGHPUT TESTING FOR PIPE
chmod +x pipe_thr.sh
gcc pipe_thr.c -o pipe_thr

#Running on royal-10
#Usage: ./pipe_thr <message_size> 

#We consider a data block of size 1GB and the rounds are calculated based on that
#The below command considers 4 bytes message size
#The message size to be tested can be specified by changing the first argument

./pipe_thr 4


