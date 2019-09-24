cd ~
# Install dependencies
apt-get install cmake openssl gperf zlib1g zlib1g-dev libssl-dev build-essential xz-utils curl
# install clang8
curl -SL http://releases.llvm.org/8.0.0/clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-16.04.tar.xz | tar -xJC .
mv clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-16.04 clang_8.0.0
mv clang_8.0.0/ /usr/local
export CXX=/usr/local/clang_8.0.0/bin/clang++
export CC=/usr/local/clang_8.0.0/bin/clang
# install ton-lite
wget https://test.ton.org/ton-test-liteclient-full.tar.xz
tar xf ton-test-liteclient-full.tar.xz 
cd lite-client/
# Patching lite-client
find ./ -type f -exec sed -i -e 's/tl_object_storage/tl_object_ptr/g' {} \;
# Building
mkdir ~/liteclient-build
cd ~/liteclient-build
cmake ~/lite-client
cmake --build . --target lite-client
