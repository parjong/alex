DBGCMD?=
RUNCMD?=ls

STORAGE_NAME=cana

LIB_PATH=$(CANA_PATH)/lib/libcana_rt.so

all:

clean:
	rm -rf $(STORAGE_NAME)

init:
	mkdir -p $(STORAGE_NAME)

run: clean init
	CANA_STORAGE="$(CURDIR)/$(STORAGE_NAME)" \
	CANA_CORECONF="$(CURDIR)/coreconf.json" \
	CANA_COREHOME="$(CURDIR)/../bin/ext" \
	CANA_APPCONF="$(CURDIR)/appconf.json" \
	CANA_APPHOME="$(CURDIR)/../bin/ext" \
	LD_PRELOAD="$(LIB_PATH)" \
	$(DBGCMD) $(RUNCMD)
