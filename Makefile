PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = \
  target/main/main.o \
  target/main/BalconyWateringSystem.o \
  target/ui/TextGui.o \
  target/logic/Pump.o \
  target/logic/SoilMoistureSensor.o \

CXXFLAGS += -std=c++17

CFLAGS += -g

all:	dirs bin/BalconyWateringSystem

dirs:
	mkdir -p target/main/
	mkdir -p target/ui/
	mkdir -p target/logic/
	mkdir -p bin/

bin/BalconyWateringSystem:	$(OBJS)
	$(CXX) -o $@ $^ -lmenu -lncurses

target/main/%.o:	$(PROJECT_ROOT)/main/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -Iui/include/ -Ilogic/include/ -o $@ $<

target/ui/%.o:	$(PROJECT_ROOT)/ui/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -Iui/include/ -Ilogic/include/ -o $@ $<

target/logic/%.o:	$(PROJECT_ROOT)/logic/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -Ilogic/include -o $@ $<

clean:
	rm -rf target/
	rm -rf bin/
	rm -rf $(OBJS)

