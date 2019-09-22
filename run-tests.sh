#MAIN SCRIPT
fs setacl TCP bart rl
fs setacl UDP bart rl
fs setacl ClockPrecision bart rl
fs setacl PIPES bart rl
fs setacl README.md bart rl
chmod +x run-tests.sh

#For TCP
cd TCP/Latency
make

#Usage: ./client -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>
#Usage: ./server -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

#LOCAL: rockhopper-05
./client -a 128.105.37.195 -b 4 -p 8945
./server -b 4 -p 8945

#REMOTE: client: rockhopper-03, server: rockhopper-06
./client -a 128.105.37.196 -b 4 -p 8955
./server -b 4 -p 8955

cd ..

cd TCP/Throughput
make

#Usage: ./client_thr -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>
#Usage: ./server_thr -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB

#LOCAL: rockhopper-05
./client_thr -a 128.105.37.195 -b 4 -p 8965
./server_thr -b 4 -p 8965

#REMOTE: client: rockhopper-03, server: rockhopper-06
./client_thr -a 128.105.37.196 -b 4 -p 8975
./server_thr -b 4 -p 8975

cd ../..

#For UDP 

cd UDP/Latency
gcc -o udp_client udp_client.c
gcc -o udp_server udp_server.c

#Usage: ./udp_client -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>
#Usage: ./udp_server -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.

#LOCAL: royal-19
./udp_client -a 128.105.37.159 -b 4 -p 8985
./udp_server -b 4 -p 8985

#REMOTE: client: snares-02, server: snares-05
./udp_client -a 128.105.37.225 -b 4 -p 8995
./udp_server -b 4 -p 8995

cd ..

cd UDP/Throughput
gcc -o udp_client_throughput udp_client_throughput.c
gcc -o udp_server_throughput udp_server_throughput.c

#Usage: ./udp_client_throughput -a <IP-ADDRESS> -b <NUM OF BYTES> -p <PORT NUMBER>
#Usage: ./udp_server_throughput -b <<NUM OF BYTES> -p <PORT NUMBER>
#Considering 4 bytes of data, that can be changed with the -b flag.
#Considering a data block of 1 GB

#LOCAL: royal-19
./udp_client_throughput -a 128.105.37.159 -b 4 -p 8985
./udp_server_throughput -b 4 -p 8985

#REMOTE: client: snares-02, server: snares-05
./udp_client_throughput -a 128.105.37.225 -b 4 -p 8995
./udp_server_throughput -b 4 -p 8995


#FOR PIPES
cd ../..

cd PIPES/Latency
gcc -o pipe_lat pipe_lat.c

#Usage: ./pipe_lat <message size> <round trip count>
#Considering 4 bytes of data, that can be changed here.

./pipe_lat 4 10000

cd ..

cd PIPES/Throughput
gcc -o pipe_thr pipe_thr.c

#Usage: ./pipe_thr <message size> 
#Considering 4 bytes of data, that can be changed here.
#Considering a data block of 1 GB

./pipe_thr 4
