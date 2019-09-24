#MAIN SCRIPT
chmod +x permissions.sh

#Set permissions
fs setacl TCP/README.md bart rlidw
fs setacl TCP/Latency bart rlidw
fs setacl TCP/Throughput bart rlidw

fs setacl UDP/README.md bart rlidw
fs setacl UDP/Latency bart rlidw
fs setacl UDP/Throughput bart rlidw

fs setacl ClockPrecision/README.md bart rlidw
fs setacl ClockPrecision bart rlidw
fs setacl ClockPrecision/clock bart rlidw
fs setacl ClockPrecision/clock_gettime bart rlidw
fs setacl ClockPrecision/rdtsc bart rlidw

fs setacl PIPES/README.md bart rlidw
fs setacl PIPES/Latency bart rlidw
fs setacl PIPES/Throughput bart rlidw
