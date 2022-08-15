cd ~/opendht && \
git pull && \
cd build && \
cmake -DOPENDHT_PYTHON=ON -DCMAKE_INSTALL_PREFIX=/usr .. && \
make -j4 && \
sudo make install
