## captcha

Add this to Makefile

```
check : testlib
.PHONY : check

install :
	echo make install for captcha is a no-op
.PHONY : install
```

## libmicrohttpd

    Port libmicrohttpd SVN 36085)
    
    0003893: [HTTPS (SSL)] CURL_SSLVERSION_TLSv1_1 is used when libcurl > 7.16.4 is required (Christian Grothoff) - resolved.
    * https://gnunet.org/bugs/view.php?id=3893
    * http://lists.gnu.org/archive/html/gnunet-svn/2015-07/msg00040.html

