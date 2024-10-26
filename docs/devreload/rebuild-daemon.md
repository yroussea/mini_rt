# [rebuild_daemon.sh](../../rebuild-daemon.sh)

The rebuild script is a watch daemon that checks for changes in the source directory.

## How it works

It is launched via `make daemon`, and killed via `make daemon-stop`. The script generates an alive file (`.rebuild-daemon.alive`), so that it cannot be launched twice.

Under the hood, it uses `inotifywait` to wait for file changes (creations, modifications, attribute changes, etc.), and simply runs `make`. Note that when a `Makefile` or `*.mk` file is changed, it instead calls `make remake`, which clears the object cache (located at `.cache` in the project root) to force recompilation of each object file, ensuring an added entry or compilation setting changes don't get missed.

It's possible that `inotifywait` is not available on your system, in which case the script will use `nix-shell` to re-run itself.

### Communication with rt

When the daemon has finished rebuilding, it will create a file (defaults to `.rebuild-daemon.done`) in the project root, which the program can look for to process (unload/reload) the new compiled files.
