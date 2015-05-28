################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/periodicArray.cpp \
../src/randKnuth.cpp \
../src/testing.cpp 

OBJS += \
./src/periodicArray.o \
./src/randKnuth.o \
./src/testing.o 

CPP_DEPS += \
./src/periodicArray.d \
./src/randKnuth.d \
./src/testing.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


