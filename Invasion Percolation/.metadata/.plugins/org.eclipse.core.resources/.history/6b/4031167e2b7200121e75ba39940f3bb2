################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/simulation/DamageMatrix.cpp \
../src/simulation/Simulation.cpp 

OBJS += \
./src/simulation/DamageMatrix.o \
./src/simulation/Simulation.o 

CPP_DEPS += \
./src/simulation/DamageMatrix.d \
./src/simulation/Simulation.d 


# Each subdirectory must supply rules for building sources it contributes
src/simulation/%.o: ../src/simulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src/simulation" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


