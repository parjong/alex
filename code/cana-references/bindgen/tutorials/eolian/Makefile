EFL_PREFIX=/home/parjong/.opt/efl-1.16.1

all: build
		
build: tst.eo
	$(EFL_PREFIX)/bin/eolian_gen -I /home/parjong/.opt/efl-1.16.1/share/eolian/include --eo --gh -o tst.h tst.eo
	$(EFL_PREFIX)/bin/eolian_gen -I /home/parjong/.opt/efl-1.16.1/share/eolian/include --eo --gs -o tst.stub.h tst.eo
	$(EFL_PREFIX)/bin/eolian_gen -I /home/parjong/.opt/efl-1.16.1/share/eolian/include --eo --gc -o tst.c tst.eo
	$(EFL_PREFIX)/bin/eolian_gen -I /home/parjong/.opt/efl-1.16.1/share/eolian/include --eo --gi -o tst.impl.c tst.eo
	$(EFL_PREFIX)/bin/eolian_gen -I /home/parjong/.opt/efl-1.16.1/share/eolian/include --eo --gi -o tst.impl.c tst.eo
	$(EFL_PREFIX)/bin/eolian_cxx -I /home/parjong/.opt/efl-1.16.1/share/eolian/include -r tst.eo
	
help_gen:
	$(EFL_PREFIX)/bin/eolian_gen --help

help_cxx:
	$(EFL_PREFIX)/bin/eolian_cxx --help
