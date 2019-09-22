#TIMING
chmod +x timing.sh
fs setacl clock bart rl
fs setacl clock_gettime bart rl
fs setacl rdtsc bart rl

#FOR CLOCK
cd clock
gcc -o clock_precision clock_precision.c
gcc -o clock_getpid clock_getpid.c
gcc -o clock_getuid clock_getuid.c

./clock_precision
./clock_getpid
./clock_getuid

cd ..

#FOR CLOCK_GETTIME
cd clock_gettime
gcc -o clock_gettime clock_gettime.c
gcc -o clock_gettime_pid clock_gettime_pid.c
gcc -o clock_gettime_uid clock_gettime_uid.c

./clock_gettime
./clock_gettime_pid
./clock_gettime_uid

cd ..

#FOR RDTSC
cd rdtsc
gcc -o rdtsc_precision rdtsc_precision.c
gcc -o rdtsc_getpid rdtsc_getpid.c
gcc -o rdtsc_getuid rdtsc_getuid.c

./rdtsc_precison
./rdtsc_getpid
./rdtsc_getuid

#RDTSC displayed more accuracy and precision, when compared to CLOCK and CLOCK_GETTIME
