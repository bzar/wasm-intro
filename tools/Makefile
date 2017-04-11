ROOT_DIR=$(shell pwd)
LLVM_WORKDIR=$(ROOT_DIR)/src/llvm
LLVM_BUILDDIR=$(ROOT_DIR)/build/llvm
BINARYEN_WORKDIR=$(ROOT_DIR)/src/binaryen
BINARYEN_BUILDDIR=$(ROOT_DIR)/build/binaryen
WABT_WORKDIR=$(ROOT_DIR)/src/wabt
WABT_BUILDDIR=$(ROOT_DIR)/build/wabt
INSTALLDIR=$(ROOT_DIR)/bin

build: build-llvm build-binaryen build-wabt

clean: clean-llvm clean-binaryen clean-wabt
	rm -rf $(INSTALLDIR)

install: install-llvm install-binaryen install-wabt

$(LLVM_WORKDIR)/.svn:
	rm -rf $(LLVM_WORKDIR)
	mkdir -p $(LLVM_WORKDIR)
	svn co http://llvm.org/svn/llvm-project/llvm/trunk $(LLVM_WORKDIR)
	svn co http://llvm.org/svn/llvm-project/cfe/trunk $(LLVM_WORKDIR)/tools/clang
	svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk $(LLVM_WORKDIR)/projects/compiler-rt

$(LLVM_BUILDDIR)/Makefile: $(LLVM_WORKDIR)/.svn
	mkdir -p $(LLVM_BUILDDIR)
	cd $(LLVM_BUILDDIR); cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=$(INSTALLDIR) -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=WebAssembly -DLLVM_TARGETS_TO_BUILD= -DCMAKE_BUILD_TYPE=Release $(LLVM_WORKDIR)

build-llvm: $(LLVM_BUILDDIR)/Makefile
	$(MAKE) -C $(LLVM_BUILDDIR) -j 8 clang llc llvm-lib

clean-llvm:
	rm -rf $(LLVM_WORKDIR)
	rm -rf $(LLVM_BUILDDIR)

install-llvm:
	mkdir -p $(INSTALLDIR)
	$(MAKE) -C $(LLVM_BUILDDIR) install-clang install-llc install-llvm-lib

$(BINARYEN_WORKDIR)/.git:
	rm -rf $(BINARYEN_WORKDIR)
	mkdir -p $(BINARYEN_WORKDIR)
	git clone https://github.com/WebAssembly/binaryen $(BINARYEN_WORKDIR)

$(BINARYEN_BUILDDIR)/Makefile: $(BINARYEN_WORKDIR)/.git
	mkdir -p $(BINARYEN_BUILDDIR)
	cd $(BINARYEN_BUILDDIR); cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=$(INSTALLDIR) -DCMAKE_BUILD_TYPE=Release $(BINARYEN_WORKDIR)

build-binaryen: $(BINARYEN_BUILDDIR)/Makefile
	$(MAKE) -C $(BINARYEN_BUILDDIR) -j 8 wasm-as wasm-dis s2wasm

clean-binaryen:
	rm -rf $(BINARYEN_WORKDIR)
	rm -rf $(BINARYEN_BUILDDIR)

install-binaryen:
	mkdir -p $(INSTALLDIR)
	cp $(addprefix $(BINARYEN_BUILDDIR)/bin/, wasm-as wasm-dis s2wasm) $(INSTALLDIR) 

$(WABT_WORKDIR)/.git:
	rm -rf $(WABT_WORKDIR)
	mkdir -p $(WABT_WORKDIR)
	git clone --recursive https://github.com/WebAssembly/wabt.git $(WABT_WORKDIR)

$(WABT_BUILDDIR)/Makefile: $(WABT_WORKDIR)/.git
	mkdir -p $(WABT_BUILDDIR)
	cd $(WABT_BUILDDIR); cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=$(INSTALLDIR) -DCMAKE_BUILD_TYPE=Release $(WABT_WORKDIR)

build-wabt: $(WABT_BUILDDIR)/Makefile
	$(MAKE) -C $(WABT_BUILDDIR) -j 8

clean-wabt:
	rm -rf $(WABT_WORKDIR)
	rm -rf $(WABT_BUILDDIR)

install-wabt:
	mkdir -p $(INSTALLDIR)
	$(MAKE) -C $(WABT_BUILDDIR) -j 8 install

.PHONY: build clean install build-llvm clean-llvm install-llvm build-binaryen clean-binaryen install-binaryen build-wabt clean-wabt install-wabt

