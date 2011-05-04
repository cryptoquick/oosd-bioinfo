SRCS		= main ui file seq needleman_wunsch smith algorithm
#SRCS		= $(addsuffix .cpp, $(FILES))
#OBJS		= $(addprefix obj/, $(addsuffix .o, $(FILES)))
#OBJS		= $(SRCS:.cpp=.o)
#OBJS		= $(addsuffix .o, $(SRCS))
CXXFLAGS	= -Wall -Iinc
LPATH		= -Llib
LIB			= -ljson
OUT			= bioinfo
OBJDIR		= obj
SRCDIR		= src
INCDIR		= inc
_OBJS		= $(addsuffix .o, $(SRCS))
OBJS		= $(addprefix $(OBJDIR)/,$(_OBJS))
#VPATH		= src:inc

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
#	$(CXX) $< -o $@ $(CXXFLAGS)
#   $(COMPILE.c) $(OUTPUT_OPTION) $<

$(OUT): $(OBJS)
	$(CXX) -o $(OUT) $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

#$(ODIR)/%.o: $(SDIR)/%.cpp
	
#	$(CXX) $(CXXFLAGS) -c $< -o obj/$@

#$(OUT): $(OBJS)
#	$(CXX) -o $(OBJS)

#$(ODIR)/%.o: $(SRCS)
#		$(CXX) $(OBJS) $(LPATH) $(LIB) -o $@
#		mv -f *.o obj/




#bioinfo: src/main.o src/ui.o src/file.o src/seq.o src/needleman_wunsch.o src/smith.o src/algorithm.o src/json.o
#	g++ -o bioinfo lib/libjson.so src/main.o src/ui.o src/file.o src/seq.o src/needleman_wunsch.o src/smith.o src/algorithm.o src/json.o
#
#main.o: src/main.cpp
#	g++ -Wall -c src/main.cpp
#
#ui.o: src/ui.cpp src/ui.h
#	g++ -Wall -c src/ui.cpp src/ui.h
#
#file.o: src/file.cpp src/file.h
#	g++ -Wall -c src/file.cpp src/file.h
#
#seq.o: src/seq.cpp src/seq.h
#	g++ -Wall -c src/seq.cpp src/seq.h
#	
#algorithm.o: src/algorithm.cpp src/algorithm.h
#	g++ -Wall -c src/algorithm.cpp src/algorithm.h
#
#needleman_wunsch.o:
#	g++ -Wall -c src/needleman_wunsch.cpp src/needleman_wunsch.h
#
#smith.o:
#	g++ -Wall -c src/smith.cpp src/smith.h
#
#json.o:
#	g++ -Wall -c src/json.cpp
#
clean:
	rm -f obj/*.o bioinfo *.o