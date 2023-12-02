BIN=2023/bin
WARN=-Wall -Wextra
DEBUG=-Og -ggdb3 -fsanitize=address -fsanitize=pointer-compare \
-fsanitize=pointer-subtract -fsanitize=undefined \
-fsanitize-address-use-after-scope -fstack-check \
-fno-stack-clash-protection
CFLAGS=$(DEBUG) $(WARN) -std=gnu99

PROG=day1-part1 day1-part2 day2-part1 day2-part2
LIST=$(addprefix $(BIN)/, $(PROG))
INC=1

all: $(LIST)
$(VERBOSE).SILENT:

$(BIN)/%: $(wildcard 2023/*/*.c)
		$(CC) $(word $(INC),$^) $(CFLAGS) -o $@
		$(eval INC=$(shell bc <<<$(INC)+1))

