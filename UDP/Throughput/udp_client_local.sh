chmod +x udp_client_local.sh

gcc -o udp_client_throughput udp_client_throughput.c

#Usage: ./udp_client_throughput -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>

#Considering 4 bytes of data, that can be changed with the -b flag.

#LOCAL: snares - 02
./udp_client_throughput -a 128.105.37.222 -b 4 -p 8985
