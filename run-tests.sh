#MAIN SCRIPT
chmod +x run-tests.sh

#Set permissions
fs setacl TCP bart rlidw
fs setacl UDP bart rlidw
fs setacl ClockPrecision bart rlidw
fs setacl PIPES bart rlidw
