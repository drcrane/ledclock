PKGCONF?=pkg-config

LIBNAME=main
CC=gcc
CFLAGS=-g -Wno-unused-function -D__COMPILE_FOR_LINUX -Wpedantic -MMD --std=c11 -O2 -Wall -Wno-unknown-pragmas -Isrc -Iinclude
CXX=g++
CXXFLAGS=-g -O2 -MMD -std=c++14 -Wall -Wno-write-strings -Isrc -Iinclude $(OPTFLAGS)
LDLIBS=-Llib $(EXTRALIBS) `$(PKGCONF) --libs openssl` -lm

SRCDIR=src/
OBJDIR=obj/
LIBDIR=lib/
DEPS_OBJ=$(wildcard $(OBJDIR)*.o)
DEPS=$(patsubst %.o,%.d,$(DEPS_OBJ))
CSOURCES=$(wildcard $(SRCDIR)*.c)
COBJECTS=$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(CSOURCES))
CPPSOURCES=$(wildcard $(SRCDIR)*.cpp)
CPPOBJECTS=$(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(CPPSOURCES))
OBJECTS=$(COBJECTS) $(CPPOBJECTS)
OPTLIBS=-lstdc++
TESTDIR=testsrc/
TESTSRC=$(wildcard $(TESTDIR)*.c)
TESTBIN=$(patsubst $(TESTDIR)%.c,$(TESTDIR)%,$(TESTSRC))

$(COBJECTS): $(OBJDIR)%.o : $(SRCDIR)%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(CPPOBJECTS): $(OBJDIR)%.o : $(SRCDIR)%.cpp $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lib/lib$(LIBNAME).a: $(OBJECTS) $(LIBDIR)
	ar -rcs $@ $(OBJECTS)

.PHONY: directories

directories: $(OBJDIR) $(LIBDIR)

$(LIBDIR):
	mkdir $(LIBDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

appsrc/% : EXTRALIBS=-l$(LIBNAME)
appsrc/% : appsrc/%.c $(LIBDIR)lib$(LIBNAME).a
	$(CC) $(DEPFLAGS) $(LDFLAGS) $(CFLAGS) $< $(LDLIBS) -o $@

testsrc/%: EXTRALIBS=-l$(LIBNAME)
testsrc/%: testsrc/%.c $(LIBDIR)lib$(LIBNAME).a
	$(CC) $(DEPFLAGS) $(LDFLAGS) $(CFLAGS) $< $(LDLIBS) -o $@

testsrc/%: testsrc/%.cpp $(LIBDIR)lib$(LIBNAME).a
	$(CXX) $(DEPFLAGS) $(LDFLAGS) $(CXXFLAGS) $< $(LDLIBS) -o $@

test: $(TESTBIN)
	./testsrc/runtests.sh

-include $(DEPS)

clean:
	rm -f lib/*.a
	rm -f obj/*.o
	rm -f obj/*.d

