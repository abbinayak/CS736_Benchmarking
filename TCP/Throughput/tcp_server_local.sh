chmod +x tcp_server_local.sh
make
#Usage: ./server_thr -b <NUM OF BYTES> -p <PORT NUMBER>

#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB

#LOCAL: server - rockhopper-05

./server_thr -b 4 -p 8965
