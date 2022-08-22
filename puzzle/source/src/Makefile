CFLAGS = -std=gnu99 -O0 -g -m32

# supress warning
CFLAGS += -Wno-format-security

# disable ASLR
CFLAGS += -no-pie -fno-pic

VULNCFLAGS = $(CFLAGS) -fno-stack-protector

# enable SSP
CFLAGS += -fstack-protector 

# enable executable stack
TARGETCFLAGS += $(CFLAGS) -z execstack

LDFLAGS = -lseccomp

ALL := target vuln

all: $(ALL)

target: target.c
	$(CC) $(TARGETCFLAGS)  -o $@ $< $(LDFLAGS)
	checksec --file $@

vuln: vuln.c
	$(CC) $(VULNCFLAGS)  -o $@ $< $(LDFLAGS)
	checksec --file $@

clean:
	rm -f $(ALL)

.PHONY: all clean
