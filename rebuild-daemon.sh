#!/usr/bin/env bash

MAKE=make
COMMUNICATE_PIPE=$1
ALIVE_FILE=$2

# if the daemon is already alive, exit
if [ -f $ALIVE_FILE ]; then
	echo "! Daemon already alive, exiting"
	exit 0
fi

shopt -s globstar

SCRIPT_NAME=$($MAKE -s print_DAEMON_SCRIPT)

# if the command is not found
if ! command -v inotifywait &> /dev/null; then
	# check for nix-shell
	if ! command -v nix-shell &> /dev/null; then
		echo "! inotifywait not found, please install inotify-tools."
		exit 1
	fi
	# if we're already in a re-run and it's still not found, fail
	if [ -n "$__DAEMON_RERUN" ]; then
		echo "! inotifywait not found after nix-shell rerun, exiting"
		exit 1
	fi

	echo "@ inotifywait not found, trying to run with nix-shell"
	# Try to run with no command to prefetch it and check if the package is found.
	# If the system's nix channels are not setup properly, this will fail.
	#TODO: Maybe add a fallback using the new nix commands? `nix develop` or `nix run`
	nix-shell -p inotify-tools --run "exit"

	if [ $? -eq 0 ]; then
		echo "@ nix-shell succeeded, re-running script"
		export __DAEMON_RERUN=1
		nix-shell -p inotify-tools --run "bash $SCRIPT_NAME $COMMUNICATE_PIPE $ALIVE_FILE"
		exit $?
	else
		echo "! nix-shell failed, exiting"
	fi
	exit 1
fi

clear
echo
echo "> Hi, I'm the rebuild daemon."
echo

function cleanup {
	rm -rf $COMMUNICATE_PIPE
	rm -rf $ALIVE_FILE
}
cleanup

touch $ALIVE_FILE

sleep 1

trap cleanup EXIT INT TERM QUIT

while true; do
	if [ ! -f $ALIVE_FILE ]; then
		echo "! Daemon not alive, exiting"
		exit 0
	fi
	echo "[*] Watching for changes..."
	# wait for inotify events (any file changes)
	FILE=$(inotifywait Makefile ./submodules/submodule.mk ./submodules/*/Makefile ./submodules/**/*.{c,h} -r -e modify,move,create,delete,attrib,close_write,moved_to,moved_from 2>/dev/null)
	if [ $? -ne 0 ]; then
		break
	fi

	clear

	# get the first before " "
	FILE=${FILE%% *}
	echo "> File changed: $FILE"
	FILENAME=${FILE##*/}

	if [[ $FILENAME == "Makefile" ]]; then
		echo "> Makefile changed, running \`remake\`"
		$MAKE remake || true
	else
		echo "> Source file changed, running \`make\`"
		$MAKE MAKE_MULTITHREAD=0 || true
	fi

	# is rt/miniRT running?
	ps -aux | grep -v grep | grep -E "\./rt|\./miniRT" > /dev/null
	if [ $? -eq 0 ]; then
		touch $COMMUNICATE_PIPE
		# wait for the program to acknowledge the change
		echo "> Waiting for acknowledge..."
		inotifywait $COMMUNICATE_PIPE -t 5
		rm -rf $COMMUNICATE_PIPE
		echo "> ACK'd"
	fi
done
