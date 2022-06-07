all:
		if [ -d "build" ]; then \
			cmake --build ./build; \
		else \
			cmake -H. -Bbuild;\
		fi

.PHONY: clean disclean
clean:
		if [ -d "build" ]; then \
			cd bulid && make clean \
		fi

disclean:
	-rm -rf build
