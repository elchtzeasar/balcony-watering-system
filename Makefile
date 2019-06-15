PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = \
  main/target/main.o \
  main/target/BalconyWateringSystem.o

CFLAGS += -g

all:	dirs bin/BalconyWateringSystem

dirs:
	mkdir -p main/target/
	mkdir -p bin/

bin/BalconyWateringSystem:	$(OBJS)
	$(CXX) -o $@ $^

main/target/%.o:	$(PROJECT_ROOT)/main/src/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -rf main/target/
	rm -rf bin/
	rm -rf $(OBJS)

