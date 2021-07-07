# Dependent tools
SWIG = /home/parjong/.opt/swig-latest/bin/swig
#SWIG = swig

CONV = ../../tools/swig_convert/libclang_python/convert.py

# Dependent source code
SOURCE_BASE = ../../targets/sample

OUT = sample.exe

all: clean build run

$(OUT):
	clang-3.5 -o sample.i -E $(SOURCE_BASE)/sample.c
	clang-3.5 -o sample.ast -emit-ast sample.i
	$(CONV) sample.ast > sample.ii
	$(SWIG) -csharp -noproxy -module sample sample.ii
	gcc -shared -fPIC -o libsample.so $(SOURCE_BASE)/sample.c sample_wrap.c
	mcs -out:$(OUT) *.cs client/hello.cs

build: $(OUT)

run: $(OUT)
	mono $(OUT)

clean:
	rm -f $(OUT) *.cs *.so *.i *.ii *.ast sample_wrap.c *.o
