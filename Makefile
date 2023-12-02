BIN23=2023/bin
BIN22=2022/bin
WARN=-Wall -Wextra
DEBUG=-Og -ggdb3 -fsanitize=address -fsanitize=pointer-compare \
-fsanitize=pointer-subtract -fsanitize=undefined \
-fsanitize-address-use-after-scope -fstack-check \
-fno-stack-clash-protection
CFLAGS=$(DEBUG) $(WARN) -march=native -std=gnu99

PROG22=day3 day4 day5 day6 day6-simd day7
PROG23=day1-part1 day1-part2 day2-part1 day2-part2
LIST23=$(addprefix $(BIN23)/, $(PROG23))
LIST22=$(addprefix $(BIN22)/, $(PROG22))
INC23=1
INC22=1

all: $(LIST22) $(LIST23)
#$(VERBOSE).SILENT:

2023: $(LIST23)
2022: $(LIST22)

$(BIN23)/%: $(wildcard 2023/*/*.c)
		$(CC) $(word $(INC23),$^) $(CFLAGS) -o $@
		$(eval INC23=$(shell bc <<<$(INC23)+1))

$(BIN22)/%: $(wildcard 2022/*/*.c)
		$(CC) $(word $(INC22),$^) $(CFLAGS) -o $@
		$(eval INC22=$(shell bc <<<$(INC22)+1))
