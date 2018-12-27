CC=gcc
CFLAGS=-static -O3 -s

LD=gcc
LDFLAGS=-s -Wl,--gc-sections,-lm

SDIR=src
ODIR=obj
BDIR=bin

.PHONY: clean ysdump

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@

YSDUMP_OFILES=$(ODIR)/ysdump.o $(ODIR)/smsr00.o $(ODIR)/rom.o

$(BDIR)/ysdump: $(YSDUMP_OFILES) | $(BDIR)
	$(LD) $(LDFLAGS) $(YSDUMP_OFILES) -o $(BDIR)/ysdump

#$(ODIR)/smsr00.o: $(SDIR)/smsr00.c | $(ODIR)
#	$(CC) $(CFLAGS) -c $(SDIR)/smsr00.c -o $@
#
#$(ODIR)/ysdump.o: $(SDIR)/ysdump.c | $(ODIR)
#	$(CC) $(CFLAGS) -c $(SDIR)/ysdump.c -o $@
	
ysdump: $(BDIR)/ysdump

$(ODIR):
	mkdir obj

$(BDIR):
	mkdir bin

clean:
	rm -f ysdump
	rm -rf $(ODIR)
	rm -rf $(BDIR)