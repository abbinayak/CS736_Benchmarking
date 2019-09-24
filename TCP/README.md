# Latency Calculation:

Latency was calculated by sending and receiving the message multiple times(around 1M iterations) and choosing the minimum latency from the results.

# Instructions to run the scripts for TCP Local and Remote:

Note: Always run the server script before the client script or else connection will be refused.

For testing local connection, client is on rockhopper-05 and server is also in the same host.
To run the script, 1 terminal should run tcp_client_local.sh and another terminal should run tcp_server_local.sh.

Similarly, for testing remote connection, client is on rockhopper-05 and server is on rockhopper-06.
To run the script, 1 terminal should run tcp_client_remote.sh and another terminal should run tcp_server_remote.sh in the respective Linux terminals.
