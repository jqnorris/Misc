################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/includes/simulation/ApplyBoundaryConditions.cpp \
../src/includes/simulation/CalculateFlow.cpp \
../src/includes/simulation/DamageMatrix.cpp \
../src/includes/simulation/Flow.cpp \
../src/includes/simulation/InitializeMatrix.cpp \
../src/includes/simulation/InitializePores.cpp \
../src/includes/simulation/Simulation.cpp \
../src/includes/simulation/TestFunctions.cpp 

OBJS += \
./src/includes/simulation/ApplyBoundaryConditions.o \
./src/includes/simulation/CalculateFlow.o \
./src/includes/simulation/DamageMatrix.o \
./src/includes/simulation/Flow.o \
./src/includes/simulation/InitializeMatrix.o \
./src/includes/simulation/InitializePores.o \
./src/includes/simulation/Simulation.o \
./src/includes/simulation/TestFunctions.o 

CPP_DEPS += \
./src/includes/simulation/ApplyBoundaryConditions.d \
./src/includes/simulation/CalculateFlow.d \
./src/includes/simulation/DamageMatrix.d \
./src/includes/simulation/Flow.d \
./src/includes/simulation/InitializeMatrix.d \
./src/includes/simulation/InitializePores.d \
./src/includes/simulation/Simulation.d \
./src/includes/simulation/TestFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/includes/simulation/%.o: ../src/includes/simulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src/includes/simulation" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -G -g -O0   "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


