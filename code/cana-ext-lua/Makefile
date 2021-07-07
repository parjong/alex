PRODUCT_DIR=bin
INTERIM_DIR=obj

.PHONY: all configure build clean run

all: build

$(INTERIM_DIR):
	mkdir -p $@
	cd $@ && cmake -DCMAKE_INSTALL_PREFIX=$(CURDIR)/$(PRODUCT_DIR) ..

configure: $(INTERIM_DIR)

build: $(INTERIM_DIR)
	cd $(INTERIM_DIR) && make all install

clean:
	rm -rf $(PRODUCT_DIR) $(INTERIM_DIR)

run:
	make -C run run
