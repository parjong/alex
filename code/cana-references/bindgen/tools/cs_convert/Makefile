OUT := convert.exe

LIBS := CppSharp.AST.dll,CppSharp.Generator.dll,CppSharp.Parser.CSharp.dll,CppSharp.Runtime.dll

all: ${OUT} 

${OUT}: convert.cs
	mcs -debug -unsafe -lib:lib -reference:${LIBS} -out:${OUT} convert.cs

clean:
	rm -f ${OUT} ${OUT}.mdb
