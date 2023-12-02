BIN23=2023/bin
BIN22=2022/bin
WARN=-Wall -Wextra
DEBUG=-Og -ggdb3 -fsanitize=address -fsanitize=pointer-compare \
-fsanitize=pointer-subtract -fsanitize=undefined \
-fsanitize-address-use-after-scope -fstack-check \
-fno-stack-clash-protection
CFLAGS=$(DEBUG) $(WARN) -march=native -std=gnu99

SOURCE22=$(wildcard 2022/day*/*.c)
SOURCE23=$(wildcard 2023/day*/*.c)
PROG22=$(addprefix $(BIN22)/, $(basename $(notdir $(SOURCE22))))
PROG23=$(addprefix $(BIN23)/, $(basename $(subst /,-, $(SOURCE23:2023/%=%))))

$(VERBOSE).SILENT:

all: $(PROG22) $(PROG23)
	echo $(SOURCE23)
2023: $(PROG23)
2022: $(PROG22)

define goal
$(1): $(2)
	$(CC) $(2) $(CFLAGS) -o $(1)
endef

$(foreach count, $(shell seq -s ' ' 1 $(words $(PROG22))), $(eval $(call goal, $(word $(count), $(PROG22)), $(word $(count), $(SOURCE22)))))
$(foreach count, $(shell seq -s ' ' 1 $(words $(PROG23))), $(eval $(call goal, $(word $(count), $(PROG23)), $(word $(count), $(SOURCE23)))))
