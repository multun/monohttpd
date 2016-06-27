# monohttpd

A simple HTTP server meant to share a single file with people on your local network.

Should compile under linux 2.6+. This program makes use of the sendfile syscall, which is known to be broken under Mac OSX.

install procedure :
```
apt-get install gcc
make
sudo make install
```