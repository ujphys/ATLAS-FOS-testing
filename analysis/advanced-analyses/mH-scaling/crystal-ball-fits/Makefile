# Lines starting with the pound sign are comments.
#
# These are the two options that may need tweaking

EXECUTABLE = diallo_crystall_ball
LINKCC = $(CXX)

 

#Uncomment this next line if you want to link to the ROOT FrameWork
INCLUDES = -I$(ROOTSYS)/include -I/usr/local/Cellar/boost/1.80.0 -I/opt/X11/include
# You can modify the below as well, but probably
# won't need to
#

# CC is for the name of the C compiler. CPPFLAGS denotes pre-processor
# flags, such as -I options. CFLAGS denotes flags for the C compiler.
# CXXFLAGS denotes flags for the C++ compiler. You may add additional
# settings here, such as PFLAGS, if you are using other languages such
# as Pascal.

CPPFLAGS =

#Uncomment this next line if you want to link to the ROOT FrameWork
LDFLAGS = -L$(ROOTSYS)/lib `root-config --glibs`  -L/usr/local/Cellar/boost/1.80.0 -framework OpenGL  -framework GLUT

CC = clang -g
#CFLAGS = -Wall -O2
CFLAGS = -Wall -Wunused-variable

# CXX = g++ -g -std=c++11
CXX = clang++ -g -std=c++14
CXXFLAGS = $(CFLAGS) $(INCLUDES)

SRCS := $(wildcard *.c) $(wildcard *.cc) $(wildcard *.cpp) $(wildcard *.C)
OBJS := $(patsubst %.c,%.o,$(wildcard *.c)) \
	$(patsubst %.cpp,%.o,$(wildcard *.cpp)) \
	$(patsubst %.cc,%.o,$(wildcard *.cc)) \
	$(patsubst %.C,%.o,$(wildcard *.C))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# "all" is the default target. Simply make it point to myprogram.

all: $(EXECUTABLE)

# Define the components of the program, and how to link them together.
# These components are defined as dependencies; that is, they must be
# made up-to-date before the code is linked.

$(EXECUTABLE): $(DEPS) $(OBJS)
	$(LINKCC) $(LDFLAGS) -o $(EXECUTABLE) $(OBJS)

# Specify that the dependency files depend on the C source files.

%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@
	$(CC) -MM $(CPPFLAGS) $< | sed s/\\.o/.d/ >> $@

%.d: %.cc
		$(CC) -MM $(CPPFLAGS) $< > $@
		$(CC) -MM $(CPPFLAGS) $< | sed s/\\.o/.d/ >> $@

%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) $(CPPFLAGS) $< > $@
	$(CXX) -MM $(CXXFLAGS) $(CPPFLAGS) $< | sed s/\\.o/.d/ >> $@

%.d: %.C
	$(CXX) -MM $(CXXFLAGS) $(CPPFLAGS) $< > $@
	$(CXX) -MM $(CXXFLAGS) $(CPPFLAGS) $< | sed s/\\.o/.d/ >> $@

# Specify that all .o files depend on .c files, and indicate how
# the .c files are converted (compiled) to the .o files.

clean:
	-rm $(OBJS) $(EXECUTABLE) $(DEPS) *~

explain:
	@echo "The following information represents your program:"
	@echo "Final executable name: $(EXECUTABLE)"
	@echo "Source files:     $(SRCS)"
	@echo "Object files:     $(OBJS)"
	@echo "Dependency files:   $(DEPS)"

depend: $(DEPS)
	@echo "Dependencies are now up-to-date."

-include $(DEPS)
