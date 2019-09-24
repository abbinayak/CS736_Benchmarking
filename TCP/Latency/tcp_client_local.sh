chmod +x tcp_client_local.sh
#LATENCY TESTING FOR TCP LOCAL
make
#Usage: ./client_thr -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>

#Local: Running on rockhopper-05

#The below command considers 4 bytes message size
#The message size to be tested can be specified by changing the argument for -b

./client -a 128.105.37.195 -p 9005 -b 4

