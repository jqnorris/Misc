################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test/FiberBundleTEST.cpp 

OBJS += \
./src/Test/FiberBundleTEST.o 

CPP_DEPS += \
./src/Test/FiberBundleTEST.d 


# Each subdirectory must supply rules for building sources it contributes
src/Test/FiberBundleTEST.o: ../src/Test/FiberBundleTEST.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src/Test" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


