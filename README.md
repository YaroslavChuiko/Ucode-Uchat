<head>
    <div align="center">
        <h1 align="center">Ucode-Uchat</h2>
    </div>
</head>

<div align="center">
  <img alt="c" src="https://img.shields.io/badge/C-3581E5.svg?style=for-the-badge&logo=c&logoColor=white" />
  <img alt="gtk3" src="https://img.shields.io/badge/-GTK+3.0-7FE719.svg?style=for-the-badge&logo=gtk&logoColor=white&labelFontColor=black" />
  <img alt="css" src="https://img.shields.io/badge/-CSS3-1572B6.svg?style=for-the-badge&logo=css3&logoColor=white" />
  <img alt="sqlite" src="https://img.shields.io/badge/SQLite-003B57.svg?style=for-the-badge&logo=SQlite&logoColor=white" />
  <img alt="openssl" src="https://img.shields.io/badge/-OpenSSL-721412.svg?style=for-the-badge&logo=OpenSSL&logoColor=white" />
  <img alt="json" src="https://img.shields.io/badge/-JSON-000000.svg?style=for-the-badge&logo=json&logoColor=white" />
  <br> 
  <img alt="commit" src="https://img.shields.io/github/last-commit/YaroslavChuiko/Ucode-Uchat?label=last%20commit&style=for-the-badge" />
  <img alt="size" src="https://img.shields.io/github/repo-size/YaroslavChuiko/Ucode-Uchat?style=for-the-badge" />
  <img alt="release" src="https://img.shields.io/github/v/release/YaroslavChuiko/Ucode-Uchat?include_prereleases&style=for-the-badge" />
  <img alt="downloads" src="https://img.shields.io/github/downloads/YaroslavChuiko/Ucode-Uchat/total?style=for-the-badge" />
</div>

<div align="center">
  <h3>A simple chat application, implemented in C.</h3>
  
  <h3>Demo</h3>
  <p><a href="https://youtu.be/BJMFtsvIYG8" target="_blank">Demo video</a></p>
</div>

<br/>
<br/>

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
