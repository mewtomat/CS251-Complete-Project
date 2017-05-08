.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
TARGET = cs251_base_11

# Project Paths
PROJECT_ROOT=./
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs
BINDIR = $(PROJECT_ROOT)/mybins
LIBDIR = $(PROJECT_ROOT)/mylibs
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

#Compiler and Linker flags
CPPFLAGS =-g -O3 -fPIC -Wall -fno-strict-aliasing
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

#Variable Declarations
STATIC_LIB = FALSE
STATIC_LIBCS251 = libCS251.a
SHARED_LIBCS251 = libCS251.so
MY_LIBS = cs251_exelib_11

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all setup doc clean distclean report 

all: setup executable

setup : 
	@mkdir -p myobjs || exit 1
	@mkdir -p mylibs || exit 1
	@mkdir -p mybins || exit 1
	@if [ ! -d "$(EXTERNAL_ROOT)/include/Box2D" ] || [ ! -d "$(EXTERNAL_ROOT)/lib/Box2D" ]; then \
		tar -zxvf "$(EXTERNAL_ROOT)/src/Box2D.tgz" ; \
		mv Box2D "$(EXTERNAL_ROOT)/src/" ; \
		echo "Done" ; \
		mkdir -p "$(EXTERNAL_ROOT)/src/Box2D/build251/" ;\
		cd $(EXTERNAL_ROOT)/src/Box2D/build251 ; \
		cmake ../ ; \
		make ; \
		make install ; \
		cd .. ; \
		cd .. ; \
		cd .. ; \
		cd .. ; \
	else \
		echo "Already Installed" ; \
	fi

executable : $(OBJS)
	@$(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(OBJS) $(LIBS)

exelib : staticlib sharedlib
	@$(CC) -o $(MY_LIBS) $(LDFLAGS) -L $(LIBDIR) $(OBJDIR)/main.o -lCS251 $(LIBS);
	@mv $(MY_LIBS) $(BINDIR);

staticlib :
ifeq ($(STATIC_LIB), TRUE)
	@ar rcs $(STATIC_LIBCS251) $(filter-out $(OBJDIR)/main.o,$(wildcard $(OBJDIR)/*.o));
	@mv $(STATIC_LIBCS251) $(LIBDIR);
endif

sharedlib :
ifeq ($(STATIC_LIB), FALSE)
	@gcc -shared -o $(SHARED_LIBCS251) $(filter-out $(OBJDIR)/main.o,$(wildcard $(OBJDIR)/*.o));
	@mv $(SHARED_LIBCS251) $(LIBDIR);
endif

-include -include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@

doc:

	@$(ECHO) -n "Generating Doxygen Documentation with our changes... "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"
	
report:
	@cd $(PROJECT_ROOT)/report ; \
	pdflatex main.tex 2 > /dev/null ; \
	bibtex main.aux ; \
	pdflatex main.tex 2 > /dev/null ; \
	pdflatex main.tex 2 > /dev/null ; \
	rm -f *.bbl *.toc *.blg *.log *.nav *.out *.snm *.aux ; \
	cd .. ; \
	rm -f *~ *.log
	
mainReport:
	@pdflatex Latex\ Report.tex 2 > /dev/null
	@rm -f *.bbl *.toc *.blg *.log *.nav *.out *.snm *.aux ; \

clean:
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~

distclean: clean
	@$(RM) -rf $(BINDIR) $(LIBDIR) $(EXTERNAL_ROOT)/include/Box2D $(EXTERNAL_ROOT)/lib/* $(EXTERNAL_ROOT)/src/Box2D $(PROJECT_ROOT)/doc/html
