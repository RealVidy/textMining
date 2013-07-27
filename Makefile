COMPILE_BIN = compile
INTERPRET_BIN = interpret
DICTIONNARY = words.txt

all:
	@make -C build -j8

clean:
	@rm -f $(COMPILE_BIN) $(INTERPRET_BIN) out

distclean: clean
	@rm -rf doc
	@rm -rf build

doc:
	doxygen doxygen/Doxyfile

check:
	@./$(COMPILE_BIN) $(DICTIONNARY) > out


.PHONY: test
