CC = g++

CFLAGS = -Wall -std=c++0x  -O6 #-pg -g
LFLAGS = -std=c++0x -O6 -larmadillo  #-pg -g 

FLEX = flex
BISON = bison
BISONFLAGS = -d

PROJECT = GPDD

HEADERS = poly.h \
		  edge.h \
		  node.h \
		  symbol.h \
		  cktparam.h \
		  paralleledgeMap.h \
		  cplx.h \
		  ckt.h \
		  actask.h \
		  option.h \
		  stringMap.h \
		  stringenc.h \
		  graph.h \
		  graphMap.h \
		  gpddnode.h \
		  coefnode.h \
		  gpddnodeMap.h \
		  gpddnodeTripleMap.h \
		  gpdd.h 

SOURCES = swmain.cpp \
		  poly.cpp \
		  stringMap.cpp \
		  stringenc.cpp \
		  ckt.cpp \
		  actask.cpp \
		  graph.cpp \
		  gpdd.cpp \
		  gpddnode.cpp \
		  gpddspanZ.cpp \
		  gpddspanE.cpp \
		  gpddspanF.cpp \
		  gpddspanG.cpp \
		  gpddspanH.cpp \
		  gpddspan.cpp \
		  gpddcoef.cpp \
		  gpddtraverse.cpp \
		  gpddzs.cpp \
		  gpddreduce.cpp \
		  gpddac.cpp \
		  cfault.cpp 

OBJECTS = $(SOURCES:.cpp=.o)

FLEXINPUT = parserflex.l

BISONINPUT = parserbison.y

PARSERHEADERS = parserdefs.h \
				parserbison.hpp

PARSERSOURCES = parserflex.cpp \
				parserbison.cpp

PARSEROBJECTS = $(PARSERSOURCES:.cpp=.o)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

TARGET = gpdd

all:$(TARGET)

$(TARGET):$(OBJECTS) $(PARSEROBJECTS) $(HEADERS) $(PARSERHEADERS) 
	$(CC) $(LFLAGS) -o $@ $^

#$(OBJECTS):$(SOURCES) $(HEADERS) Makefile
$(OBJECTS):$(HEADERS) Makefile


$(PARSEROBJECTS):$(PARSERHEADERS) parserbison.cpp parserflex.cpp Makefile
#$(PARSEROBJECTS):$(PARSERSOURCES) $(PARSERHEADERS) Makefile


parserbison.cpp:$(BISONINPUT) parserdefs.h
	@$(BISON) $(BISONFLAGS) $(BISONINPUT) -o $@

parserflex.cpp: $(FLEXINPUT) $(PARSERHEADERS)
	@$(FLEX) $(FLEXINPUT)

clean:
	rm -f *.o *~ $(PARSERSOURCES)


