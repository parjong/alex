DBGCMD?=
RUNCMD?=g++ -I inc -o sample sample.cpp

STORAGE_NAME=cana

LIB_PATH=$(CANA_PATH)/lib/libcana_rt.so

all:

clean:
	rm -rf $(STORAGE_NAME)
	mkdir -p $(STORAGE_NAME)/capture
	cp toolconf.json $(STORAGE_NAME)/capture/config.json

init:
	mkdir -p $(STORAGE_NAME)

exe: clean init
	CANA_STORAGE="$(CURDIR)/$(STORAGE_NAME)" \
	CANA_CORECONF="$(CURDIR)/coreconf.json" \
	CANA_COREHOME="$(CANA_PATH)/ext" \
	CANA_APPCONF="$(CURDIR)/appconf.json" \
	CANA_APPHOME="$(CURDIR)/../bin" \
	LD_PRELOAD="$(LIB_PATH)" \
	$(DBGCMD) $(RUNCMD)

prn:
	cat $(STORAGE_NAME)/capture/capture.log

run: exe prn
