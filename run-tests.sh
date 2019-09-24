#MAIN SCRIPT
chmod +x run-tests.sh

#Set permissions
fs setacl TCP/Latency bart rlidw
fs setacl TCP/Throughput bart rlidw

fs setacl UDP/Latency bart rlidw
fs setacl UDP/Throughput bart rlidw

fs setacl ClockPrecision bart rlidw
fs setacl ClockPrecision/clock bart rlidw
fs setacl ClockPrecision/clock_gettime bart rlidw
fs setacl ClockPrecision/rdtsc bart rlidw

fs setacl PIPES bart rlidw
