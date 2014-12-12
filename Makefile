objects = build/regenerate.o build/handler.o
dir_guard = @mkdir -p $(@D)

all:build/ofpsvr
build/ofpsvr:main.c $(objects)
	$(dir_guard)
	cc main.c $(objects) -o $@ -I./include -I../mruby/include -L/usr/local/lib ../mruby/build/host/lib/libmruby.a -lm -lmysqlclient -lcrypto -lmicrohttpd -lpthread -O3
build/%.o: %.c
	$(dir_guard)
	cc $< -o $@ -c -I./include -I../mruby/include -L/usr/local/lib ../mruby/build/host/lib/libmruby.a -lm -lmysqlclient -lcrypto -lmicrohttpd -lpthread -O3
install:build/ofpsvr
	cp ./build/ofpsvr /usr/local/bin
clean:
	rm -rf build/
