#MAIN SCRIPT
chmod +x run-tests.sh

#Set permissions
fs setacl TCP bart rl
fs setacl UDP bart rl
fs setacl ClockPrecision bart rl
fs setacl PIPES bart rl
