export CC=/usr/bin/gcc-9
export CXX=/usr/bin/g++-9

rm -Rf build bin
mkdir build 
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="../" -G "Unix Makefiles"
make
make install
cd ..
