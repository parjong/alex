REDUCE_DIR = ../../tools/reduce/libtooling_cxx
CONVERT_DIR = ../../tools/cs_convert

HEADERS =
HEADERS += a.h
HEADERS += b.h

all: 

full: clean appfw.dll

appfw.cs: ${HEADERS}
	make -C $(CONVERT_DIR)
	MONO_PATH=$(CONVERT_DIR)/lib mono --debug $(CONVERT_DIR)/convert.exe --namespace appfw --triple arm-linux-unknown-gnueabi --library pthread ${HEADERS}

appfw.dll: appfw.cs
	mcs -unsafe -target:library -out:$@ $<

clean:
	rm -f *.cs *.dll
