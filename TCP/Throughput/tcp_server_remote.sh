chmod +x tcp_server_remote.sh
make
#Usage: ./server_thr -b <NUM OF BYTES> -p <PORT NUMBER>

#Remote: Running on rockhopper-05 and rockhopper-06
#Client: rockhopper-05 and Server rockhopper-06

#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB in the code

./server_thr -b 4 -p 8975
