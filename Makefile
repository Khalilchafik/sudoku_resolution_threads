# Makefile (root directory)

all:
	$(MAKE) -C lib
	$(MAKE) -C src

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C src clean

.PHONY: all clean
