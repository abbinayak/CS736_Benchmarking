gcc -o udp_server_throughput udp_server_throughput.c

#Usage: ./udp_server_throughput -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

#LOCAL: snares - 02
./udp_server_throughput -b 4 -p 8985
