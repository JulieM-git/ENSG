# Python #

https://www.unixmen.com/howto-install-python-3-x-in-ubuntu-debian-fedora-centos/

Sur Debian :
```sh
wget https://www.python.org/ftp/python/3.6.0/Python-3.6.0.tgz
tar xvf Python-3.6.0.tgz
cd Python-3.6.0
./configure --enable-optimizations
make -j8
sudo make altinstall
python3.6
```

ou

```sh
$ sudo nano etc/apt/sources.list
# add
deb http://ftp.de.debian.org/debian experimental main
deb http://ftp.de.debian.org/debian unstable main
# and maybe it needs this too
deb http://http.debian.net/debian/ jessie main contrib non-free
$ sudo apt-get update
$ sudo apt-get install python3.6
$ python3.6 -V
```
