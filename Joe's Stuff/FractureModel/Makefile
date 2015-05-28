o/%.o: %.cpp
	@mkdir -p o
	@echo Compiling $<...
	@g++  -c -O3  -o $@ -Wall -pedantic  $<

SOURCES = 			runDamage.cpp           \
					randKnuth.cpp           \
					Simulation.cpp          \
					Sites.cpp              	\
					statistics.cpp


damageNucleation: $(SOURCES:%.cpp=o/%.o)
	@echo Building $@...
	@g++  -O3 -Wall -pedantic  -o $@ $^

clean:
	@echo Removing object files ...
	@-rm -rf o
	@echo Removing executable ...
	@-rm -f damageNucleation
