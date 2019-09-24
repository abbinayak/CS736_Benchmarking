# Instructions to run the scripts for UDP Local and Remote:

1. For testing local connection, client is on snares-02 and server is also in the same host.
To run the script, 1 terminal should run udp_client_local.sh and another terminal should run udp_server_local.sh.

2. Similarly, for testing remote connection, client is on snares-02 and server is on snares-05.
To run the script, 1 terminal should run udp_client_remote.sh and another terminal should run udp_server_remote.sh in the respective Linux terminals.

3. Under folder Packet Loss, udp_packetloss_client.c and udp_packetloss_server.c illustrates the working of packet loss in udp. It just take care of sequence number in order to assure the data is totally arrived and with the right order. If not, server just stops to receive data. We ask the client to resend pieces and rebuild the data despite thw wrong order with the help of the sequence numbers
