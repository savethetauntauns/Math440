##################
MPI_COMPILE = mpiCC
RIGHTS = chmod
##################
XFLAG = 111
step1_files = step1.cpp
step2_files = step2.cpp
##################
all: step1_exe step2_exe 

step1_exe: $(step1_files)
	$(MPI_COMPILE) $(step1_files) -o $@
	$(RIGHTS) $(XFLAG) $@

step2_exe: $(step2_files)
	$(MPI_COMPILE) $(step2_files) -o $@
	$(RIGHTS) $(XFLAG) $@

##################
clean:
	rm -f step1_exe step2_exe a.out

