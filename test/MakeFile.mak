
OUTDIR = ./bin/
$(OUTDIR) :
	if not exist "$(OUTDIR)" makedir $(OUTDIR)
all:test.exe
	cl testProcessController.cpp

clean:
	del $(OUTDIR)\*.*




