CC 			= gcc
CFLAGS 		= -std=c11 -Wall -Werror -Wextra
TEST_LIBS 	= -lm $(shell pkg-config --cflags --libs check)
BACK_P 		= 3D_Viewer/back/
SOURCES 	= $(wildcard 3D_Viewer/back/*.c)
OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
PROJECT		= s21_3dviewer
STATIC_LIB	= 3D_Viewer.a
COL_GREEN	=| awk '{ print "\033[1;32m" $$0"\033[0m"}'



all: build

install: build
	mkdir -vp install
	@cp -rv build/3D_Viewer.app install$(COL_GREEN)
	rm -rf build

build:
	rm -rf build
	mkdir -vp build
	cd build && cmake ../3D_Viewer
	cd build && $(MAKE)

uninstall: clean
	rm -rf 3D_Viewer/CMakeLists.txt.user
	rm -rf 3D_Viewer/build
	rm -rf build
	rm -rf install

execute:
	cd build && open ./3D_Viewer.app

gcov_flag:
	$(eval CFLAGS += --coverage)

debug_flag:
	$(eval CFLAGS += -g)

dist: build
	@tar --totals -cvf build.tar build/3D_Viewer.app$(COL_GREEN)

dvi:
	rm -rf Documentation
	doxygen
	open Documentation/html/index.html


gcov_report: clean gcov_flag test
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf $(BACK_P)*.gcno $(BACK_P)*.gcda $(BACK_P)*.gcov *.gcno *.gcda *.gcov
	open gcov/index.html

$(STATIC_LIB): clean $(OBJECTS)
	ar -rcs $(STATIC_LIB) $(OBJECTS)
	ranlib $(STATIC_LIB)
	rm -f $(BACK_P)*.o


test: clean $(STATIC_LIB)
	$(CC) $(CFLAGS) Tests/*.c -o test $(STATIC_LIB) $(TEST_LIBS) 
	./test

debug: debug_flag test

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf Documentation test gcov
	rm -rf $(BACK_P)*.o *.a *.gcda *.gcno *.gch *.pdf *.tar rep.info test.info test.dSYM coverage.info
