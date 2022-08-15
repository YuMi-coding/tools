sudo apt install -y cmake libncurses5-dev libreadline-dev nettle-dev libgnutls28-dev libargon2-0-dev libmsgpack-dev  libssl-dev libfmt-dev libjsoncpp-dev libhttp-parser-dev &&\
sudo apt-get install -y cython3 python3-dev python3-setuptools && \
cd ~/ && \
mkdir restinio && cd restinio &&\
wget https://github.com/aberaud/restinio/archive/2224ffedef52cb2b74645d63d871d61dbd0f165e.tar.gz \
&& ls -l && tar -xzf 2224ffedef52cb2b74645d63d871d61dbd0f165e.tar.gz \
&& cd restinio-2224ffedef52cb2b74645d63d871d61dbd0f165e/dev \
&& cmake -DCMAKE_INSTALL_PREFIX=/usr -DRESTINIO_TEST=OFF -DRESTINIO_SAMPLE=OFF -DRESTINIO_INSTALL_SAMPLES=OFF -DRESTINIO_BENCH=OFF -DRESTINIO_INSTALL_BENCHES=OFF -DRESTINIO_FIND_DEPS=ON -DRESTINIO_ALLOW_SOBJECTIZER=Off -DRESTINIO_USE_BOOST_ASIO=none . \
&& make -j8 && sudo make install \
&& cd ../../ && rm -rf restinio &&\
cd ~/ && \
git clone https://github.com/YuMi-coding/opendht.git && \
cd opendht && \
mkdir build && cd build && \
cmake -DOPENDHT_PYTHON=ON -DCMAKE_INSTALL_PREFIX=/usr .. && \
make -j4 && \
sudo make install

