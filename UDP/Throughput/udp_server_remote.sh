gcc -o udp_server_throughput udp_server_throughput.c

#Usage: ./udp_server_throughput -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

#REMOTE: client in snares - 02 connecting to server in snares - 05
./udp_server_throughput -b 4 -p 8995
