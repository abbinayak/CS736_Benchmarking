make
#Usage: ./client_thr -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>
#Usage: ./server_thr -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB

#LOCAL: rockhopper-05
#Open 2 terminals of rockhopper-05, one for the server and one for the client
./server_thr -b 4 -p 8965
./client_thr -a 128.105.37.195 -b 4 -p 8965
