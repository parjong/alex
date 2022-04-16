LLVM_PREFIX	= /usr/lib/llvm-3.5

CXX 			= g++
CXXFLAGS 	= -fno-rtti -O0 -g

LLVM_CXXFLAGS 	= `$(LLVM_PREFIX)/bin/llvm-config --cxxflags`

LLVM_LDFLAGS 		= `$(LLVM_PREFIX)/bin/llvm-config --ldflags`
LLVM_LIBS		 		= `$(LLVM_PREFIX)/bin/llvm-config --libs --system-libs`

CLANG_CXXFLAGS	= 

CLANG_LIBS := \
	-Wl,--start-group \
	-lclangAST \
	-lclangAnalysis \
	-lclangBasic \
	-lclangDriver \
	-lclangEdit \
	-lclangFrontend \
	-lclangFrontendTool \
	-lclangLex \
	-lclangParse \
	-lclangSema \
	-lclangEdit \
	-lclangASTMatchers \
	-lclangRewrite \
	-lclangRewriteFrontend \
	-lclangStaticAnalyzerFrontend \
	-lclangStaticAnalyzerCheckers \
	-lclangStaticAnalyzerCore \
	-lclangSerialization \
	-lclangTooling \
	-lclangIndex \
	-Wl,--end-group

OUT = reduce
SRC = reduce.cc

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) $(LLVM_LDFLAGS) $(CLANG_CXXFLAGS) $^ $(CLANG_LIBS) $(LLVM_LIBS)	-o $@ 

clean:
	rm -f $(OUT)

