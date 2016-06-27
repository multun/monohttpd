# monohttpd

A simple HTTP server meant to serve a single file.

Should compile under linux 2.6+. This program uses the sendfile syscall, which is known to be broken under Mac OSX.

It requires GCC as well as a decent OS.

install procedure :
```
make
sudo make install
```