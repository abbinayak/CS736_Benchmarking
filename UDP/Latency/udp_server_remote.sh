chmod +x udp_server_remote.sh

gcc -o udp_server udp_server.c

#Usage: ./udp_server -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

#REMOTE: client in snares -02, and server in snares - 05
./udp_server -b 4 -p 8995
