chmod +x tcp_client_remote.sh
make
#Usage: ./client_thr -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>


#Remote: Running on rockhopper-05 and rockhopper-06
#Client: rockhopper-05 and Server rockhopper-06

#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB

./client_thr -a 128.105.37.196 -b 4 -p 8975
