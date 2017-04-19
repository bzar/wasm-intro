TOOLS=$(dir $(lastword $(MAKEFILE_LIST)))/tools
CLANG=$(TOOLS)/bin/bin/clang 
LLC=$(TOOLS)/bin/bin/llc
S2WASM=$(TOOLS)/bin/s2wasm
WAST2WASM=$(TOOLS)/bin/bin/wast2wasm

%.bc : %.c
	${CLANG} --target=wasm32 -Oz -c -emit-llvm $< -o $@

%.s : %.bc
	${LLC} $< -o $@

%.wat : %.s
	${S2WASM} $< > $@

%.wasm : %.wat
	${WAST2WASM} $< -o $@

