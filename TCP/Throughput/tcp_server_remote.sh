chmod +x tcp_server_remote.sh
make
#Usage: ./server_thr -b <NUM OF BYTES> -p <PORT NUMBER>

#Remote: Running on rockhopper-05 and rockhopper-06
#Client: rockhopper-05 and Server rockhopper-06

#The below commands are for 4 bytes message size
#The message size to be tested can be specified by changing the argument for -b
#Considering a data block of 1 GB in the code

./server_thr -b 4 -p 8975

