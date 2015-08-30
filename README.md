<p align="center"><img src="https://raw.githubusercontent.com/pmq20/ofpsvr/master/public/img/index.png" /></p>

<p align="center">P.S.V.R 的软件实验室</p>

<p align="center">http://www.ofpsvr.com</p>
 
## 状态

[![持续集成服务](https://travis-ci.org/pmq20/ofpsvr.svg?branch=master)](https://travis-ci.org/pmq20/ofpsvr)
[![文档生成](https://readthedocs.org/projects/ofpsvr/badge/?version=latest)](http://ofpsvr.readthedocs.org/zh_CN/latest/)
[![测试覆盖率](https://coveralls.io/repos/pmq20/ofpsvr/badge.png)](https://coveralls.io/r/pmq20/ofpsvr)

## 系统组件

本项目依赖于以下必要的系统组件：

* [Autoconf](http://www.gnu.org/software/autoconf/autoconf.html) / [Automake](http://www.gnu.org/software/automake/) / [GNU Libtool](http://www.gnu.org/software/libtool/)
* [MySQL Connector/C (libmysqlclient)](https://dev.mysql.com/downloads/connector/c)
* [OpenSSL](https://www.openssl.org/)
* [GnuTLS](http://www.gnutls.org/)
* [ImageMagick](http://www.imagemagick.org/)
* [Check](http://check.sourceforge.net/)
* [LCOV](http://ltp.sourceforge.net/coverage/lcov.php)
* [bison](http://www.gnu.org/software/bison/)

如果您使用 Mac，可以通过以下命令安装这些系统组件：

```sh
brew install libtool autoconf automake
brew install mysql
brew install gnutls
brew install imagemagick
brew install bison
brew install check
brew install lcov
```

如果您使用 Ubuntu，可以通过以下命令安装这些系统组件：

```sh
sudo apt-get install libtool autoconf automake
sudo apt-get install libmysqlclient-dev
sudo apt-get install libssl-dev
sudo apt-get install libgnutls-dev
sudo apt-get install bison
sudo apt-get install check
sudo apt-get install lcov
```

## 编译安装

如果是从代码仓库下载的源码，请先执行：

```sh
sh autogen.sh
```

进入项目根目录，执行：

```sh
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

例如：

```sh
export OFPSVR_DB_HOST=127.0.0.1
export OFPSVR_DB_USER=user1
export OFPSVR_DB_PASSWD=secret
export OFPSVR_DB_DB=ofpsvr
```

在这些环境变量之下执行 `ofpsvr` 即可：

```sh
ofpsvr
```

除了上述必选的环境变量外，还有下列可选的环境变量：

* `OFPSVR_ASSET_HOST`   - 静态文件的 CDN 地址头，结尾无斜杠

例如：

```sh
export OFPSVR_ASSET_HOST=http://7xjzhb.com1.z0.glb.clouddn.com/890201
```

## 代码风格

本项目遵循 [Linux 内核代码风格](https://raw.githubusercontent.com/pmq20/ofpsvr/master/CodingStyle)。

## 许可协议

本项目使用 [GNU 通用公共许可协议](https://raw.githubusercontent.com/pmq20/ofpsvr/master/LICENSE)，请在遵守该协议的前提下使用源代码。
