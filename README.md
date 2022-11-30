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

## Preview

#### Login
|![login](https://user-images.githubusercontent.com/32570823/204894177-738aa205-eaf9-46b6-a53d-5c741be6189f.png)|![login-error](https://user-images.githubusercontent.com/32570823/204894301-d0e4c281-a86e-423f-9187-10cdb4aa8b0f.png)|
| :----: | :----: |

#### Register
|![register](https://user-images.githubusercontent.com/32570823/204894815-93932777-b110-413f-8064-5bdee825a52f.png)|![register-error](https://user-images.githubusercontent.com/32570823/204894887-0b656b22-a6f1-475c-bc30-6df8ad288efb.png)|
| :----: | :----: |

#### Main window
![main-window](https://user-images.githubusercontent.com/32570823/204895402-737f1a8a-603e-4988-bb11-0bd7fb2f1d5c.png)

#### Modal
![modal](https://user-images.githubusercontent.com/32570823/204895596-891d030b-92d1-4749-9ba8-48b291553d67.png)

#### Chat
![chat](https://user-images.githubusercontent.com/32570823/204895860-8abb5920-f940-4bbc-8b84-115f9e20ff8d.png)
