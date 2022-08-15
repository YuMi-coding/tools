curl https://binaries.cockroachdb.com/cockroach-v21.2.7.linux-amd64.tgz | tar -xz && sudo cp -i cockroach-v21.2.7.linux-amd64/cockroach /usr/local/bin/
sudo mkdir -p /usr/local/lib/cockroach
sudo cp -i cockroach-v21.2.7.linux-amd64/lib/libgeos.so /usr/local/lib/cockroach/
sudo cp -i cockroach-v21.2.7.linux-amd64/lib/libgeos_c.so /usr/local/lib/cockroach/
which cockroach
sudo timedatectl set-ntp no
sudo apt-get install -y ntp
sudo service ntp stop
sudo ntpd -b time.google.com
sudo service ntp start
sudo ntpq -p