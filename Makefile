BIN23=2023/bin
BIN22=2022/bin
WARN=-Wall -Wextra
DEBUG=-Og -ggdb3 -fsanitize=address -fsanitize=pointer-compare \
-fsanitize=pointer-subtract -fsanitize=undefined \
-fsanitize-address-use-after-scope -fstack-check \
-fno-stack-clash-protection
CFLAGS=$(DEBUG) $(WARN) -march=native -std=gnu99
LIBS=-lm
RELEASE=-O2 -s -pipe -flto=4
CFLAGS=$(WARN) -march=native -std=gnu99

SOURCE22=$(wildcard 2022/day*/*.c)
SOURCE23=$(wildcard 2023/day*/*.c)
PROG22=$(addprefix $(BIN22)/, $(basename $(notdir $(SOURCE22))))
PROG23=$(addprefix $(BIN23)/, $(basename $(subst /,-, $(SOURCE23:2023/%=%))))
CPPCHECK=$(shell command -v cppcheck)

$(VERBOSE).SILENT:

debug: CFLAGS += $(DEBUG)
debug: | 2023 2022
release: CFLAGS += $(RELEASE)
release: | 2023 2022
clean:
	rm -f $(BIN23)/*
	rm -f $(BIN22)/*
2023: | dir23 $(PROG23)
2022: | dir22 $(PROG22)

dir23:
	mkdir -p $(BIN23)
dir22:
	mkdir -p $(BIN22)

define goal
$(1): $(2)
	if [ -n $(CPPCHECK) ]; then\
		cppcheck --enable=all --suppress=missingIncludeSystem -q $(2);\
	fi
	$(CC) $(2) $(LIBS) $(CFLAGS) -o $(1)
endef

$(foreach count, $(shell seq -s ' ' 1 $(words $(PROG22))), $(eval $(call goal, $(word $(count), $(PROG22)), $(word $(count), $(SOURCE22)))))
$(foreach count, $(shell seq -s ' ' 1 $(words $(PROG23))), $(eval $(call goal, $(word $(count), $(PROG23)), $(word $(count), $(SOURCE23)))))

