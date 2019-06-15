PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = \
  target/main/main.o \
  target/main/BalconyWateringSystem.o \
  target/ui/TextGui.o \

CXXFLAGS += -std=c++17

CFLAGS += -g

all:	dirs bin/BalconyWateringSystem

dirs:
	mkdir -p target/main/
	mkdir -p target/ui/
	mkdir -p bin/

bin/BalconyWateringSystem:	$(OBJS)
	$(CXX) -o $@ $^ -lmenu -lncurses

target/main/%.o:	$(PROJECT_ROOT)/main/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -Iui/include/ -o $@ $<

target/ui/%.o:	$(PROJECT_ROOT)/ui/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -Iui/include/ -o $@ $<

clean:
	rm -rf target/
	rm -rf bin/
	rm -rf $(OBJS)

