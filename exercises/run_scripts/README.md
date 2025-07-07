# Sequential Script Executor

This project contains a simple C program that sequentially executes one or more bash scripts using `fork()` and `execlp()`.

## Features

* Spawns a child process for each script
* Executes scripts using `/bin/bash`
* Waits for each child to finish before proceeding
* Reports exit status or signal termination

## Usage

### Build

```bash
make
```

### Run with example scripts

```bash
make run
```

### Run manually

```bash
./run_scripts script1.sh script2.sh
```

### Run with Valgrind

```bash
make valgrind
```

### Clean build

```bash
make clean
```

## Project Structure

```
run_scripts/             # Root project folder
├── main.c               # Main source code
├── Makefile             # Build automation
├── README.md            # Project documentation
└── tests/             # Example bash scripts for testing
    ├── hello.sh
    └── fail.sh
```

## Example Output

```sh
execute script 1: test1.sh
script test1.sh exited with code 0
execute script 2: test2.sh
script test2.sh exited with code 0
```

## Notes

* You can add as many scripts as needed in the command-line arguments.
* This tool can be used to batch test or automate shell scripts.

## License

MIT License

