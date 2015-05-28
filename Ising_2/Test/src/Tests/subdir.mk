################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tests/IsingTEST.cpp 

OBJS += \
./src/Tests/IsingTEST.o 

CPP_DEPS += \
./src/Tests/IsingTEST.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tests/IsingTEST.o: ../src/Tests/IsingTEST.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src/Tests" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


