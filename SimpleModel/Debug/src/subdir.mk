################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Fibers.cpp \
../src/Simulation.cpp \
../src/randKnuth.cpp \
../src/runDamage.cpp 

OBJS += \
./src/Fibers.o \
./src/Simulation.o \
./src/randKnuth.o \
./src/runDamage.o 

CPP_DEPS += \
./src/Fibers.d \
./src/Simulation.d \
./src/randKnuth.d \
./src/runDamage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


