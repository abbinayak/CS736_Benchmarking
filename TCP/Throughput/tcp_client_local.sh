chmod +x tcp_client_local.sh
make
#Usage: ./client_thr -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>

#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB

#LOCAL: client - rockhopper-05

./client_thr -a 128.105.37.195 -b 4 -p 8965
