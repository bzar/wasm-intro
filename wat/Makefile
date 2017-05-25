include ../Makefile
INPUTS = $(wildcard *.wat)
OUTPUTS = $(patsubst %.wat,%.wasm,$(INPUTS))

all: $(OUTPUTS)

serve:
	python3 -m http.server
