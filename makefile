CPP := g++
CC := gcc
AR := ar

SUB_DIRS := $(shell find src -type d -print)
OBJ_DIRS := $(foreach dir,$(SUB_DIRS),$(patsubst src%,build%,$(dir)))
SRC := $(foreach dir,$(SUB_DIRS),$(wildcard $(dir)/*.cc) $(wildcard $(dir)/*.c))
OBJ := $(patsubst src/%.cc,build/%.o,$(patsubst src/%.c,build/%.o,$(SRC)))
INCLUDE := -Isrc -Iinclude -Iinclude/windows-layer
CFLAGS := $(INCLUDE)
LIBS :=
RELEASE_TARGET := bin/windows-layer.a
DEBUG_TARGET := bin/debug.a

.PRECIOUS: build/%.d test-build/%.d
.PHONY: clean debug release test
.DEFAULT_GOAL := debug

release: $(RELEASE_TARGET)
debug: $(DEBUG_TARGET)
test: $(TEST_TARGET)

$(RELEASE_TARGET) $(DEBUG_TARGET): $(OBJ)
	$(AR) cr $@ $^

$(OBJ_DIRS) $(TEST_OBJ_DIRS):
	mkdir -p $@

build/%.d: src/%.c | $(OBJ_DIRS)
	$(CC) -MM -MT build/$*.o $(CFLAGS) -MF $@ $<

build/%.o: src/%.c build/%.d | $(OBJ_DIRS)
	$(CC) -c -o $@ $(CFLAGS) $<

build/%.d: src/%.cc | $(OBJ_DIRS)
	$(CPP) -std=c++11 -MM -MT build/$*.o $(CFLAGS) -MF $@ $<

build/%.o: src/%.cc build/%.d | $(OBJ_DIRS)
	$(CPP) -c -o $@ -std=c++11 $(CFLAGS) $<

bin/%.dll: build/%.o
	$(CPP) -shared -o $@ $^

clean:
	if [ -d "build" ]; then rm -R build; fi

include $(wildcard build/*.d)
