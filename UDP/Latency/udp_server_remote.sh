gcc -o udp_server udp_server.c

#Usage: ./udp_server -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

./udp_server -b 4 -p 8995
