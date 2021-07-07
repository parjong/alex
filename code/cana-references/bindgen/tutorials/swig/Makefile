SWIG = ~/opt/swig-latest/bin/swig

SRC := lib.c

OUT_SO := _sample.so
OUT_C := sample_wrap.c

all: clean ${OUT_SO} test

$(OUT_C): $(SRC)
	$(SWIG) -python -module sample -o $(OUT_C) $(SRC)

$(OUT_SO): $(SRC) $(OUT_C)
	gcc -fPIC -shared -o $(OUT_SO) $(SRC) $(OUT_C) -I /usr/include/python2.7

test:
	./hello.py

clean:
	rm -f $(OUT_SO) $(OUT_C) sample.py sample.pyc
