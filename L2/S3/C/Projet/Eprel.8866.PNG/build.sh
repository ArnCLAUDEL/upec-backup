rm -rf PNG
mkdir PNG

tar xzvf zlib-1.2.8.tar.gz
cd zlib-1.2.8
pwd
./configure --static --prefix=`pwd`/../PNG
make
make install
cd ..
pwd
rm -rf zlib-1.2.8

tar xzvf libpng-1.6.19.tar.gz
cd libpng-1.6.19
pwd
./configure --prefix=`pwd`/../PNG --with-zlib-prefix=`pwd`/../PNG --enable-silent-rules --enable-shared=no --with-binconfigs=no CFLAGS=-I`pwd`/../PNG/include/ CPPFLAGS=-I`pwd`/../PNG/include/ LDFLAGS=-L`pwd`/../PNG/lib/ ZLIBLIB=-I`pwd`/../PNG/lib/ ZLIBINC=-I`pwd`/../PNG/include/
CFLAGS=-I`pwd`/../PNG/include/ CPPFLAGS=-I`pwd`/../PNG/include/ LDFLAGS=-L`pwd`/../PNG/lib/ ZLIBLIB=-I`pwd`/../PNG/lib/ ZLIBINC=-I`pwd`/../PNG/include/ make
make install
cd ..
pwd
rm -rf PNG/bin PNG/share PNG/lib/pkgconfig
rm -rf libpng-1.6.19


