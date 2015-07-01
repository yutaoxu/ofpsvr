<p align="center"><img src="https://raw.githubusercontent.com/pmq20/ofpsvr/master/public/img/index.png" /></p>

<p align="center">P.S.V.R 的软件实验室</p>

<p align="center">http://www.ofpsvr.com</p>
 
## 状态

[![持续集成状态](https://travis-ci.org/pmq20/ofpsvr.svg?branch=master)](https://travis-ci.org/pmq20/ofpsvr)
 
## 编译

必备系统组件：

 * [Autoconf](http://www.gnu.org/software/autoconf/autoconf.html), [Automake](http://www.gnu.org/software/automake/), [GNU Libtool](http://www.gnu.org/software/libtool/)
 * [MySQL Connector/C (libmysqlclient)](https://dev.mysql.com/downloads/connector/c)
 * [GNU Libmicrohttpd](https://www.gnu.org/software/libmicrohttpd/)
 * [Check](http://check.sourceforge.net/)

（参考）Ubuntu 用户可通过以下命令安装这些系统组件：

```sh
sudo apt-get install libmysqlclient-dev
sudo apt-get install libmicrohttpd-dev
sudo apt-get install libssl-dev
```

先进入 deps/mruby 目录编译 mruby 依赖包：

```sh
cd deps/mruby
./minirake
```

回到主目录，执行：

```sh
sh autogen.sh
./configure
make
make check
sudo make install
```

## 代码风格

本项目遵循 [Linux 内核代码风格](https://www.kernel.org/doc/Documentation/CodingStyle).

## 许可协议

本项目的源代码在 [MIT 许可协议](https://raw.githubusercontent.com/pmq20/ofpsvr/master/LICENSE) 下发布.
