BIN23=2023/bin
BIN22=2022/bin
WARN=-Wall -Wextra
DEBUG=-Og -ggdb3 -fsanitize=address -fsanitize=pointer-compare \
-fsanitize=pointer-subtract -fsanitize=undefined \
-fsanitize-address-use-after-scope -fstack-check \
-fno-stack-clash-protection
CFLAGS=$(DEBUG) $(WARN) -march=native -std=gnu99

PROG22=day3 day4 day5 day6 day6-simd
PROG23=day1-part1 day1-part2 day2-part1 day2-part2
SOURCE22=day3/day3.c day4/day4.c day5/day5.c day6/day6.c day6/day6-simd.c
SOURCE23=day1/part1.c day1/part2.c day2/part1.c day2/part2.c

LIST23=$(addprefix $(BIN23)/, $(PROG23))
LIST22=$(addprefix $(BIN22)/, $(PROG22))
SLIST22=$(addprefix 2022/,$(SOURCE22))
SLIST23=$(addprefix 2023/,$(SOURCE23))

$(VERBOSE).SILENT:

all: $(LIST22) $(LIST23)
2023: $(LIST23)
2022: $(LIST22)

define goal
$(1): $(2)
	$(CC) $(2) $(CFLAGS) -o $(1)
endef



$(foreach count, $(shell seq -s ' ' 1 $(words $(LIST22))), $(eval $(call goal, $(word $(count), $(LIST22)), $(word $(count), $(SLIST22)))))
$(foreach count, $(shell seq -s ' ' 1 $(words $(LIST23))), $(eval $(call goal, $(word $(count), $(LIST23)), $(word $(count), $(SLIST23)))))
