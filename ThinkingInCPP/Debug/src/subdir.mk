################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Ch03Ex2.cpp 

OBJS += \
./src/Ch03Ex2.o 

CPP_DEPS += \
./src/Ch03Ex2.d 


# Each subdirectory must supply rules for building sources it contributes
src/Ch03Ex2.o: ../src/Ch03Ex2.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


