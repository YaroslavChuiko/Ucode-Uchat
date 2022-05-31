# Uchat-Ucode
A REST API for a chat application, implemented in C. 

## Compiling and building
If you use MacOS, follow the next steps: 
1. Uncomment lines 34 and 31 in `client/Makefile` and `server/Makefile` respectively.
2. Do `brew update`, `brew install gtk+3`.
3. Do `make font` to install the required font.
4. Do `make`.

Otherwise, do `make install` and `make`.

## Executing
First, run `./uchat_server [port]`. This process will work as a daemon and you can kill it by doing `kill [pid]`, where pid is the process id, that will be shown in the beginning of execution.

Then, run the app:
`./uchat [ip_address] [port]`.

You can use standard 8080 port, and 127.0.0.1 for running on localhost.
