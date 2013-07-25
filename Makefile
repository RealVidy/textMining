COMPILE_BIN = compile

all:
	@make -C build -j8

clean:
	@rm $(COMPILE_BIN)

distclean: clean
	@rm -rf doc
	@rm -rf build

doc:
	doxygen doxygen/Doxyfile

check:
	@./$(COMPILE_BIN)


.PHONY: test
