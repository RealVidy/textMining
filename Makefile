all:
	@make -C build -j8

clean:
	@rm test/*.so 2>/dev/null || true

distclean: clean
	@rm -rf doc
	@rm -rf build

doc:
	doxygen doxygen/Doxyfile


.PHONY: test
