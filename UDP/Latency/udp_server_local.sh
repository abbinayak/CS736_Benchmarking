chmod +x udp_server_local.sh

gcc -o udp_server udp_server.c

#Usage: ./udp_server -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

#LOCAL: snares - 02
./udp_server -b 4 -p 8985
