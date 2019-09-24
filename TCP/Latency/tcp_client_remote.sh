chmod +x tcp_client_remote.sh
#LATENCY TESTING FOR TCP REMOTE
make
#Remote: Running on rockhopper-05 and rockhopper-06
#Client: rockhopper-05 and Server rockhopper-06
#The below commands are for 4 bytes
#The message size to be tested can be specified by changing the argument for -b


./client -a 128.105.37.196 -p 9005 -b 4

