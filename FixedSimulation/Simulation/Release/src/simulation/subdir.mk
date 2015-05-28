################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/simulation/Simulation.cpp 

OBJS += \
./src/simulation/Simulation.o 

CPP_DEPS += \
./src/simulation/Simulation.d 


# Each subdirectory must supply rules for building sources it contributes
src/simulation/%.o: ../src/simulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -O3  -odir "src/simulation" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -O3 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


