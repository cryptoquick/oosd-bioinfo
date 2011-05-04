SRCS		= main ui file seq needleman_wunsch smith algorithm json
OUT			= bioinfo
OBJDIR		= obj
SRCDIR		= src
INCDIR		= inc
_OBJS		= $(addsuffix .o, $(SRCS))
OBJS		= $(addprefix $(OBJDIR)/,$(_OBJS))
CXXFLAGS	= -Wall -I$(INCDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OUT): $(OBJS)
	$(CXX) -o $(OUT) $(OBJS) -Llib -ljson

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -f obj/*.o bioinfo *.o