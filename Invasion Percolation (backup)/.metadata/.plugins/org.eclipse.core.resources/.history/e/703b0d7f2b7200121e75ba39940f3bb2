################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/includes/simulation/DamageMatrix.cpp \
../src/includes/simulation/Simulation.cpp 

OBJS += \
./src/includes/simulation/DamageMatrix.o \
./src/includes/simulation/Simulation.o 

CPP_DEPS += \
./src/includes/simulation/DamageMatrix.d \
./src/includes/simulation/Simulation.d 


# Each subdirectory must supply rules for building sources it contributes
src/includes/simulation/%.o: ../src/includes/simulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -O3  -odir "src/includes/simulation" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -O3   "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


