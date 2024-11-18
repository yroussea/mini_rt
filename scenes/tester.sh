#!/usr/bin/env bash

APP=${APP:-../rt}
OK="$(tput setaf 2)✓$(tput sgr0)"
FAIL="$(tput setaf 1)✗$(tput sgr0)"
VALGRIND=0

# if the user passed a -v flag, enable valgrind
if [ $# -gt 0 ]; then
	if [ "$1" == "-v" ]; then
		VALGRIND=1
	fi
fi


FAILS=()
echo ""
echo "[*] Running invalid scenes..."
for scene in ./invalid/*.rt; do
	if [ $VALGRIND -eq 1 ]; then
		valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -q $APP $scene -p # >/dev/null 2>&1
	else
		$APP $scene -p >/dev/null 2>&1
	fi
	if [ $? -eq 0 ]; then
		printf "$FAIL"
		FAILS+=("$scene")
	else
		printf "$OK"
	fi
done
printf "\n"

if [ ${#FAILS[@]} -gt 0 ]; then
	echo "[!] Failed scenes:"
	for fail in "${FAILS[@]}"; do
		echo "    $fail"
	done
fi


FAILS=()
echo ""
echo "[*] Running valid scenes..."
for scene in ./valid/*.rt; do
	if [ $VALGRIND -eq 1 ]; then
		valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -q $APP $scene -p # >/dev/null 2>&1
	else
		$APP $scene -p >/dev/null 2>&1
	fi
	if [ $? -eq 0 ]; then
		printf "$OK"
	else
		printf "$FAIL"
		FAILS+=("$scene")
	fi
done
printf "\n"

if [ ${#FAILS[@]} -gt 0 ]; then
	echo "[!] Failed scenes:"
	for fail in "${FAILS[@]}"; do
		echo "    $fail"
	done
fi
