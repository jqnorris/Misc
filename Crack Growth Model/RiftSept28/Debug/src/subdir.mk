################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Model.cpp \
../src/OptionsBin.cpp \
../src/Simulation.cpp \
../src/orderedPair.cpp \
../src/periodicArray.cpp \
../src/randKnuth.cpp 

OBJS += \
./src/Model.o \
./src/OptionsBin.o \
./src/Simulation.o \
./src/orderedPair.o \
./src/periodicArray.o \
./src/randKnuth.o 

CPP_DEPS += \
./src/Model.d \
./src/OptionsBin.d \
./src/Simulation.d \
./src/orderedPair.d \
./src/periodicArray.d \
./src/randKnuth.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


