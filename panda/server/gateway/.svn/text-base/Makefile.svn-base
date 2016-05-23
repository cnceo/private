TARGET=GatewayServer
TARGET := $(addprefix ../bin/,$(TARGET))

CXX = g++ -std=c++11
CFLAGS =-g -O0 -Wall -fpermissive -Wno-parentheses -Wno-sign-compare -Wno-unused-variable -Wpointer-sign -Wparentheses
CFLAGS += -I./ -I../ -I/usr/include/mysql/ -I../pandadb -I../../pandanet -I../../pandanet/thirdparts/include
LFLAGS = -L../../pandanet/ -L../../pandanet/thirdparts/lib -L../pandadb/ -L/usr/lib/mysql -L/usr/local/lib/ -lpthread -lm -lmysqlclient -lstdc++ -lkeye -lprotobuf-lite
LFLAGS += -lpandadb -lpandanet -lcurses -lboost_system-mt -lboost_date_time-mt

FILES+= $(wildcard *.cpp) \
	$(wildcard handlers/*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(FILES))

default all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS)
	find ./ -name *.o -exec rm -f {} \;

echo:
	@echo CFLAGS=$(CFLAGS)

.PHONY: default all clean depend

%o:%cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)
