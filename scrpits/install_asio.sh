sudo apt update && \
cd ~/ && \
wget https://sourceforge.net/projects/asio/files/asio/1.18.0%20%28Stable%29/asio-1.18.0.tar.bz2 && \
tar -xf ./asio-1.18.0.tar.bz2 && \
cd asio-1.18.0 && \
./configure && \
make && \
sudo make install

