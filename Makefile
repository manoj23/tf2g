#
# © 2014 Georges Savoundararadj 
#
# SPDX-License-Identifier: MIT
#
CXX = clang++

SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin

PROG = tf2g

SRCS = $(wildcard $(SRCDIR)/*.cpp) 
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS = -std=c++11 -Wall -I$(INCDIR) 

all: $(BINDIR)/$(PROG)

depend: .depend

.depend: $(SRCS)
	rm -rfv ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ | sed 's/[[:alnum:]]*.o:/obj\/&/' > ./.depend

include .depend

$(BINDIR)/$(PROG): $(OBJS) | $(BINDIR)
	$(CXX) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rfv $(OBJDIR) $(BINDIR) .depend
