#!/usr/bin/env bash

RULE="${RULE:-all}"
MAKE="${MAKE:-make -j MLX_DIR=\"../MacroLibX\"}"
DEPS=(libft MacroLibX tocard-ui)
SESSION_NAME="minirt-deps"

tmux new-session -d -s $SESSION_NAME
tmux rename-window -t $SESSION_NAME "minirt-deps"

COUNT=0
for dep in "${DEPS[@]}"; do
	# if count is not 0
	if [ $COUNT -ne 0 ]; then
		if (( COUNT % 2 )); then
			tmux split-window -h -t $SESSION_NAME
		else
			tmux split-window -v -t $SESSION_NAME
		fi
    fi
	COUNT=$((COUNT+1))

	tmux send-keys "clear; echo \">>> $dep\"; $MAKE --no-print-directory -C $dep $RULE; sleep 2; exit" 'C-m'
done

tmux -2 attach-session -t $SESSION_NAME
