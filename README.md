<p align="center"><a href="http://www.ofpsvr.com"><img src="https://raw.githubusercontent.com/pmq20/ofpsvr-static/master/img/index.png" alt="OF P.S.V.R" /></a></p>

<p align="center">
<a href="https://travis-ci.org/pmq20/ofpsvr"><img src="https://img.shields.io/travis/pmq20/ofpsvr.svg?style=flat-square" alt="Build status"></a>
<a href="https://coveralls.io/r/pmq20/ofpsvr?branch=master"><img src="https://img.shields.io/coveralls/pmq20/ofpsvr.svg?style=flat-square" alt="Test coverage"></a>
<a href="https://www.gittip.com/pmq20/"><img src="https://img.shields.io/gittip/pmq20.svg?style=flat-square" alt="Gittip"></a>
<a href="https://raw.githubusercontent.com/pmq20/ofpsvr/master/LICENSE"><img src="http://img.shields.io/badge/license-GPLv3-blue.svg" alt="License"></a>
<a href="http://www.ofpsvr.com"><img src="https://img.shields.io/badge/made%20with-%3C3-red.svg" alt="Made with love"></a>
</p>

This is the source code of [OF P.S.V.R](http://www.ofpsvr.com),
the personal website of P.S.V.R
written purely in the C programming language.

## DEPENDENCIES

  - Autotools
  - MySQL Connector/C
  - OpenSSL
  - GnuTLS
  - ImageMagick
  
On a Macintosh computer, they could be installed via brew:

```
brew install libtool autoconf automake
brew install mysql
brew install gnutls
brew install imagemagick
```

On a Linux box, say Ubuntu, they could be installed via apt-get:

```
apt-get install libtool autoconf automake
apt-get install libmysqlclient-dev
apt-get install libssl-dev
apt-get install libgnutls-dev
```

## BUILDING

```
./configure
make
sudo make install
```

Note: if building from the source repository, first run:
  
```
sh autogen.sh
```
  
## RUNNING
  
Set these environment variables:
  
  - "OFPSVR_DB_HOST"    - MySQL host
  - "OFPSVR_DB_USER"    - MySQL user name
  - "OFPSVR_DB_PASSWD"  - MySQL password
  - "OFPSVR_DB_DB"      - MySQL database name
  - "OFPSVR_REDIS_HOST" - Redis host
  - "OFPSVR_REDIS_PORT" - Redis port number
  - "OFPSVR_ASSET_HOST" - CDN address, no trailing slashes
  
For instance,

```
export OFPSVR_DB_HOST=127.0.0.1
export OFPSVR_DB_USER=user1
export OFPSVR_DB_PASSWD=secret
export OFPSVR_DB_DB=ofpsvr
export OFPSVR_REDIS_HOST=127.0.0.1
export OFPSVR_REDIS_PORT=6379
export OFPSVR_ASSET_HOST=http://7xjzhb.com1.z0.glb.clouddn.com/890201
```

Then run:

```
ofpsvr
```

## SEE ALSO

  - https://github.com/pmq20/ofpsvr-static
