# s2-php-ext
使用google s2库 计算cellid和getcoving  本扩展需要安装s2geometry库和php-x库， 仅在linux64位

依赖
------

* s2geometry: https://github.com/google/s2geometry
* php-x: https://github.com/swoole/PHP-X

安装
------

```
cd s2-php-ext
make 
sudo make install
```

加载配置
------
```
Edit php.ini, add extension=s2.so
```

测试
```
php example.php
```
