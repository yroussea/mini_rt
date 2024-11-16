#!/usr/bin/env bash

APP=${APP:-../rt}
OK="$(tput setaf 2)✓$(tput sgr0)"
FAIL="$(tput setaf 1)✗$(tput sgr0)"

FAILS=()
echo ""
echo "[*] Running invalid scenes..."
for scene in ./invalid/*.rt; do
	$APP $scene -p >/dev/null 2>&1
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
	$APP $scene -p >/dev/null 2>&1
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
