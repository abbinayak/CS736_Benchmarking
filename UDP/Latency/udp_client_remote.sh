chmod +x udp_client_remote.sh

gcc -o udp_client udp_client.c

#Usage: ./udp_client -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>

#Considering 4 bytes of data, that can be changed with the -b flag.

#REMOTE: snares - 02, connecting to server in snares - 05
./udp_client -a 128.105.37.225 -b 4 -p 8995
