OUT = convert
SRC = convert.cc

all: $(OUT)

$(OUT): $(SRC)
	g++ -std=c++11 -I /usr/lib/llvm-3.5/include -o $(OUT) $(SRC) -lclang-3.5

clean:
	rm -f $(OUT)
