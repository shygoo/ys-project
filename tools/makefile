CC=gcc
CFLAGS=-static -O3 -s

LD=gcc
LDFLAGS=-s -Wl,--gc-sections,-lm

SDIR=src
ODIR=obj
BDIR=bin

.PHONY: clean ysdump ovl

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@

#####################

YSDUMP_OFILES=$(ODIR)/ysdump.o $(ODIR)/smsr00.o $(ODIR)/rom.o $(ODIR)/img.o

$(BDIR)/ysdump: $(YSDUMP_OFILES) | $(BDIR)
	$(LD) $(LDFLAGS) $(YSDUMP_OFILES) -o $(BDIR)/ysdump

ysdump: $(BDIR)/ysdump

#####################

OVLDUMP_OFILES=$(ODIR)/ovldump.o $(ODIR)/mips_disasm.o $(ODIR)/rom.o

$(BDIR)/ovldump: $(OVLDUMP_OFILES) | $(BDIR)
	$(LD) $(LDFLAGS) $(OVLDUMP_OFILES) -o $(BDIR)/ovldump

ovldump: $(BDIR)/ovldump

#####################

$(ODIR):
	mkdir obj

$(BDIR):
	mkdir bin

clean:
	rm -f ysdump
	rm -rf $(ODIR)
	rm -rf $(BDIR)