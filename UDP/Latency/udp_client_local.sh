gcc -o udp_client udp_client.c

#Usage: ./udp_client -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>

#Considering 4 bytes of data, that can be changed with the -b flag.

#LOCAL: snares - 02
./udp_client -a 128.105.37.222 -b 4 -p 8985

