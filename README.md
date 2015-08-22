<p align="center"><img src="https://raw.githubusercontent.com/pmq20/ofpsvr/master/public/img/index.png" /></p>

<p align="center">P.S.V.R 的软件实验室</p>

<p align="center">http://www.ofpsvr.com</p>
 
## 状态

[![持续集成服务](https://travis-ci.org/pmq20/ofpsvr.svg?branch=master)](https://travis-ci.org/pmq20/ofpsvr)
[![文档生成](https://readthedocs.org/projects/ofpsvr/badge/?version=latest)](http://ofpsvr.readthedocs.org/zh_CN/latest/)
[![测试覆盖率](https://coveralls.io/repos/pmq20/ofpsvr/badge.png)](https://coveralls.io/r/pmq20/ofpsvr)

## 编译

必要的系统组件：

* [Autoconf](http://www.gnu.org/software/autoconf/autoconf.html) / [Automake](http://www.gnu.org/software/automake/) / [GNU Libtool](http://www.gnu.org/software/libtool/)
* [MySQL Connector/C (libmysqlclient)](https://dev.mysql.com/downloads/connector/c)
* [OpenSSL](https://www.openssl.org/)
* [Check](http://check.sourceforge.net/) 与 [LCOV](http://ltp.sourceforge.net/coverage/lcov.php)

作为参考，Ubuntu 用户可通过以下命令安装这些系统组件：

```sh
sudo apt-get install libtool autoconf automake
sudo apt-get install libmysqlclient-dev
sudo apt-get install libssl-dev
sudo apt-get install check lcov
```

进入项目根目录，执行：

```sh
sh autogen.sh
./configure
make
make check
sudo make install
```

## 运行

运行之前请确保正确设置以下环境变量：
 
* `OFPSVR_DB_HOST`   - MySQL 主机
* `OFPSVR_DB_USER`   - MySQL 用户
* `OFPSVR_DB_PASSWD` - MySQL 密码
* `OFPSVR_DB_DB`     - MySQL 数据库名

在这些环境变量之下用根用户执行 `ofpsvr` 即可，例如

    sudo OFPSVR_DB_HOST=127.0.0.1 OFPSVR_DB_USER=user1 OFPSVR_DB_PASSWD=secret OFPSVR_DB_DB=ofpsvr ofpsvr

## 代码风格

本项目遵循 [Linux 内核代码风格](https://www.kernel.org/doc/Documentation/CodingStyle).

## 许可协议

本软件是一个自由软件；您可依据  [GNU 通用公共许可协议](https://raw.githubusercontent.com/pmq20/ofpsvr/master/LICENSE) 的条款，对源代码进行修改及再发布。

在协议的保护下，所有修改版将持续保持自由开放，欢迎贡献代码！
