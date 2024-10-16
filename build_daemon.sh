#!/usr/bin/env bash

TARGET_FILE="$1"
RETURN_FILE="$2"
KILL_FILE="$3"
ALIVE_FILE="$4"
ACK_FILE="$5"
if [ -z "$TARGET_FILE" ] || [ -z "$RETURN_FILE" ] || [ -z "$KILL_FILE" ] || [ -z "$ALIVE_FILE" ] || [ -z "$ACK_FILE" ]; then
	echo "usage: $0 <target_file> <return_file> <kill_file> <alive_file> <ack_file>"
	exit 1
fi

if [ -e "$ALIVE_FILE" ]; then
	echo "[@] daemon is already alive"
	exit 0
fi

echo "[@] watching $TARGET_FILE"
echo "[@] return file: $RETURN_FILE"
echo "[@] kill file: $KILL_FILE"
echo "[@] alive file: $ALIVE_FILE"
echo "[@] ack file: $ACK_FILE"

rm -f "$TARGET_FILE"
rm -f "$RETURN_FILE"
rm -f "$KILL_FILE"
rm -f "$ACK_FILE"
touch "$ALIVE_FILE"

# remove the alive file when the daemon exits at all costs
trap "rm -f $TARGET_FILE $RETURN_FILE $KILL_FILE $ALIVE_FILE $ACK_FILE" EXIT SIGINT SIGTERM

# watch for creation of the target file in a loop
# and run the build command when it is created
while true; do
	if [ -e "$TARGET_FILE" ]; then
		rm -f "$TARGET_FILE"
		make
		echo "return" > "$RETURN_FILE"
	fi
	if [ -e "$ACK_FILE" ]; then
		rm -f "$ACK_FILE"
		rm -f "$RETURN_FILE"
	fi
	if [ -e "$KILL_FILE" ]; then
		rm -f "$KILL_FILE"
		rm -f "$ALIVE_FILE"
		exit 0
	fi
	sleep 0.1
done
