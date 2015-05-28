################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fiberElement.cpp \
../src/myDelay.cpp \
../src/randKnuth.cpp 

OBJS += \
./src/fiberElement.o \
./src/myDelay.o \
./src/randKnuth.o 

CPP_DEPS += \
./src/fiberElement.d \
./src/myDelay.d \
./src/randKnuth.d 


# Each subdirectory must supply rules for building sources it contributes
src/fiberElement.o: ../src/fiberElement.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/myDelay.o: ../src/myDelay.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/randKnuth.o: ../src/randKnuth.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc --compile -G -O0 -g -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


