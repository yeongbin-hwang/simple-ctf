CFLAGS = -std=gnu99 -O0 -g -m64

# supress warning
CFLAGS += -Wno-format-security

# disable ASLR
CFLAGS += -no-pie -fno-pic

# disable SSP
CFLAGS += -fno-stack-protector

# enable executable stack
TARGETCFLAGS += $(CFLAGS)

ALL := target

all: $(ALL)

target: target.c
	$(CC) $(TARGETCFLAGS)  -o $@ $<
	checksec --file $@

clean:
	rm -f $(ALL)

.PHONY: all clean
