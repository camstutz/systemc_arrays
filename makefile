
include_dirs := /usr/local/lib/systemc-2.3.1/include /usr/local/include/root

librarypaths := /usr/local/lib/systemc-2.3.1/lib-linux64 /usr/local/lib/root
libraries := systemc

sub_libs := sc_analyzer sc_map

##########################################################################################

LINK_LIBS     = $(addprefix -l,$(libraries))
LINK_LIBPATHS = $(addprefix -L,$(librarypaths))

CC       := g++
CPPFLAGS := -Wall -g3 -O0 -std=c++11 $(addprefix -I,$(include_dirs)) $(LINK_LIBPATHS) $(LINK_LIBS)

SUBLIBS_SRC  := $(addsuffix /src,$(sub_libs))
SOURCES      := $(foreach _LIB,$(SUBLIBS_SRC),$(wildcard $(_LIB)/*.cpp))
OBJECTS      := $(subst .cpp,.o,$(SOURCES))
DEPENDENCIES := $(subst .cpp,.d,$(SOURCES))


.PHONY: all
all: systemc_helpers.a

systemc_helpers.a : $(DEPENDENCIES) $(OBJECTS)
	ar rcs libsystemc_helpers.a $(OBJECTS)

%.d: %.cpp
	$(CC) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cpp,.d,$<)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)

.PHONY: clean
clean:
	rm -f  $(OBJECTS) $(DEPENDENCIES)

ifneq "$(MAKECMDGOALS)" "clean"
	include $(DEPENDENCIES)
	@echo "included dependencies"
endif











#headers    = $(wildcard include/*.h)
#lib_hdr    = $(wildcard src/*.h)
#lib_src    = $(wildcard src/*.cpp)
#lib_libs   = -lalib 
#test_hdr   = $(wildcard test/*.h)
#test_src   = $(wildcard test/*.cpp)
#test_libs  = $(lib_libs) -lUnitTest++
#extra_dist = Makefile README.md
#dist_files = $(headers) $(lib_hdr) $(lib_src) $(test_hdr) $(test_src) $(extra_dist)


#.PHONY: library
#make library: 


#ifeq ($(MSYSTEM), MINGW32)
#  EXEEXT    = .exe  
#  LIBEXT    = .dll
#else
#  EXEEXT    =
#  LIBEXT    = .so  
#endif

#.PHONY: all check clean install uninstall dist

#all: $(PACKAGE)$(LIBEXT)

#$(PACKAGE)$(LIBEXT): $(patsubst %.cpp, %.o, $(lib_src))
#	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ $(lib_libs) -Wl,--out-implib=$(patsubst %$(LIBEXT),lib%.a, $@) -o $@

#check: test-$(PACKAGE)$(EXEEXT)	
#	./test-$(PACKAGE)$(EXEEXT)

#test-$(PACKAGE)$(EXEEXT): $(PACKAGE)$(LIBEXT) $(patsubst %.cpp, %.o, $(test_src))
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(test_libs) -o $@

#clean: 
#	rm -f src/*.o src/*.d test/*.o test/*.d $(PACKAGE)$(LIBEXT) test-$(PACKAGE)$(EXEEXT)	



#ifneq "$(MAKECMDGOALS)" "clean"
#deps  = $(patsubst %.cpp, %.d, $(lib_src))
#deps += $(patsubst %.cpp, %.d, $(test_src))
#-include $(deps)
#endif
