SOURCE_DIR = ../../targets/sample

REDUCE_DIR = ../../tools/reduce/libtooling_cxx
CONVERT_DIR = ../../tools/cs_convert

LIBRARY_NAME = toy

C_FILE = sample.toy.c
H_FILE = sample.h
CS_FILE = ${LIBRARY_NAME}.cs
SO_FILE = lib${LIBRARY_NAME}.so

all: 

full: clean run

${H_FILE}: $(SOURCE_DIR)/${C_FILE}
	make -C $(REDUCE_DIR)
	$(REDUCE_DIR)/reduce $(SOURCE_DIR)/${C_FILE} -- > ${H_FILE}

${CS_FILE}: ${H_FILE}
	make -C $(CONVERT_DIR)
	MONO_PATH=$(CONVERT_DIR)/lib mono --debug $(CONVERT_DIR)/convert.exe -l ${LIBRARY_NAME} ${H_FILE}

${SO_FILE}: $(SOURCE_DIR)/${C_FILE}
	g++ -shared -fPIC -o ${SO_FILE} $(SOURCE_DIR)/${C_FILE}

toy.client.exe: ${CS_FILE} client/hello.cs
	mcs -unsafe -target:exe -out:toy.client.exe ${CS_FILE} client/hello.cs

build: ${H_FILE} ${CS_FILE} ${SO_FILE} toy.client.exe

run: ${SO_FILE} toy.client.exe
	mono --debug toy.client.exe 

clean:
	rm -f ${H_FILE} ${CS_FILE} ${SO_FILE} *.cs *.h *.so
