##################
COMPILE = g++
##################
q1_files = assign1.cpp

q3a_files = assign3a.cpp
q3b_files = assign3b.cpp

q6a_files = assign6a.cpp
q6b_files = assign6b.cpp
##################
all: q1_exe q3a_exe q3b_exe q6a_exe q6b_exe

	mkdir OUTPUT
q1_exe: $(q1_files)
	$(COMPILE) $(q1_files) -o $@

q3a_exe: $(q3a_files)
	$(COMPILE) $(q3a_files) -o $@
q3b_exe: $(q3b_files)
	$(COMPILE) $(q3b_files) -o $@

q6a_exe: $(q6a_files)
	$(COMPILE) $(q6a_files) -o $@
q6b_exe: $(q6b_files)
	$(COMPILE) $(q6b_files) -o $@
##################
clean:
	rm -f q1_exe q3a_exe q3b_exe q6a_exe q6b_exe
	rm -rf OUTPUT
