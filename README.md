![OF P.S.V.R](https://raw.githubusercontent.com/pmq20/ofpsvr/master/public/img/index.png)
 
P.S.V.R 的软件实验室

http://www.ofpsvr.com
 
## 状态
 
[![持续集成状态](https://travis-ci.org/pmq20/ofpsvr.svg?branch=master)](https://travis-ci.org/pmq20/ofpsvr)
 
## 编译

系统必备组件（仅 UNIX 系统）：

 * GCC 4.2 或以上
 * G++ 4.2 或以上
 * Python 2.6 或 2.7
 * GNU Make 3.81 或以上
 * libexecinfo (仅 FreeBSD and OpenBSD 系统)

请在 Unix / Macintosh 系统上执行：

```sh
./configure
make
make install
```

如果您的 python 二进制文件存放在了非标准的位置，或有着非标准的名称，请使用以下替代脚本：

```sh
export PYTHON=/path/to/python
$PYTHON ./configure
make
make install
```

系统必备组件（仅 Windows 系统）：

 * Python 2.6 or 2.7
 * Visual Studio 2010 or 2012

请在 Windows 系统上执行:

```sh
vcbuild nosign
```

## 代码风格

本项目遵循 [Linux 内核代码风格](https://www.kernel.org/doc/Documentation/CodingStyle).

## 许可协议

本项目的源代码在 [MIT 许可协议](https://raw.githubusercontent.com/pmq20/ofpsvr/master/LICENSE) 下发布.
