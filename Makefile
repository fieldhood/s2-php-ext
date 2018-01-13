PHP_INCLUDE = `php-config --includes`
PHP_LIBS = `php-config --libs`
PHP_LDFLAGS = `php-config --ldflags`
PHP_INCLUDE_DIR = `php-config --include-dir`
PHP_EXTENSION_DIR = `php-config --extension-dir`

s2.so: s2.cpp
	c++ -DHAVE_CONFIG_H -g -o s2.so -O0 -fPIC -shared s2.cpp -std=c++11 -lphpx -ls2 -lglog ${PHP_INCLUDE} -I${PHP_INCLUDE_DIR}
test.so: test.cpp
	c++ -DHAVE_CONFIG_H -g -o test.so -O0 -fPIC -shared test.cpp -std=c++11  -lphpx ${PHP_INCLUDE} -I${PHP_INCLUDE_DIR}\
	 -I${PHP_INCLUDE_DIR}/ext/swoole/include -I${PHP_INCLUDE_DIR}/ext/swoole
install: s2.so
	cp s2.so ${PHP_EXTENSION_DIR}/
clean:
	rm *.so
