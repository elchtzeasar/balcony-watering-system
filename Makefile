PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = \
  .target/main/main.o \
  .target/main/BalconyWateringSystem.o \
  .target/configuration/ConfigurationFile.o \
  .target/configuration/SimulationConfiguration.o \
  .target/configuration/SoilMoistureSensorConfiguration.o \
  .target/configuration/PumpConfiguration.o \
  .target/hardware/HWFactory.o \
  .target/hardware/Master.o \
  .target/hardware/SimulatedMotor.o \
  .target/hardware/SimulatedSoilMoistureSensor.o \
  .target/logic/LogicFactory.o \
  .target/logic/Pump.o \
  .target/logic/SoilMoistureSensor.o \
  .target/ui/TextGui.o \

CXXFLAGS += -std=c++17

CFLAGS += -g

all:	dirs bin/BalconyWateringSystem

dirs:
	mkdir -p .target/main/
	mkdir -p .target/configuration/
	mkdir -p .target/logic/
	mkdir -p .target/hardware/
	mkdir -p .target/ui/
	mkdir -p bin/

bin/BalconyWateringSystem:	$(OBJS)
	$(CXX) -o $@ $^ -lmenu -lncurses -lyaml

.target/main/%.o:	$(PROJECT_ROOT)/main/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) \
	-I../boost.di/include/ \
	-Iconfiguration/include/ \
	-Ihardware/include/ \
	-Ilogic/include/ \
	-Iui/include/ \
	-o $@ $<

.target/configuration/%.o:	$(PROJECT_ROOT)/configuration/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) \
	-Iconfiguration/include/ \
	-o $@ $<

.target/hardware/%.o:	$(PROJECT_ROOT)/hardware/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) \
	-Iconfiguration/include/ \
	-Ihardware/include/ \
	-o $@ $<

.target/logic/%.o:	$(PROJECT_ROOT)/logic/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) \
	-Iconfiguration/include/ \
	-Ihardware/include/ \
	-Ilogic/include \
	-o $@ $<

.target/ui/%.o:	$(PROJECT_ROOT)/ui/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) \
	-Ilogic/include/ \
	-Iui/include/ \
	-o $@ $<

clean:
	rm -rf .target/
	rm -rf bin/

