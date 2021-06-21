.PHONY: install uninstall clean unit_tests all

# Compiler
CC := gcc

# Compilation flags
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla

# Check util flags
CHECK_FLAGS := -lcheck -lpthread -lrt

# Files
SRCS := $(wildcard src/*.c)
UNITS := $(wildcard unit_tests/*.c)

all: app.out check.out

app.out:  $(SRCS:%.c=out/%.o)
	$(CC) -o $@ $^

check.out: $(filter-out out/src/main.o,$(SRCS:%.c=out/%.o)) \
	$(UNITS:%.c=out/%.o)
	$(CC) -o $@ $^ $(CHECK_FLAGS)

out/src/%.o: src/%.c
	@mkdir -p out/src
	$(CC) $(CFLAGS) -o $@ -c $<

out/unit_tests/%.o: unit_tests/%.c
	@mkdir -p out/unit_tests
	$(CC) $(CFLAGS) -o $@ -c $<

out/src/%.d: src/%.c
	@mkdir -p out/src
	$(CC) -M $< > $@

out/unit_tests/%.d: unit_tests/%.c
	@mkdir -p out/unit_tests
	$(CC) -M $< > $@

include $(SRCS:%.c=out/%.d) $(UNITS:%.c=out/%.d)

install: app.out

unit_tests: check.out

clean:
	rm -f out/src/* out/unit_tests/*
	rm -f app.out check.out
