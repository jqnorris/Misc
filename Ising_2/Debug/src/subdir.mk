################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ising.cpp \
../src/randKnuth.cpp 

OBJS += \
./src/ising.o \
./src/randKnuth.o 

CPP_DEPS += \
./src/ising.d \
./src/randKnuth.d 


# Each subdirectory must supply rules for building sources it contributes
src/ising.o: ../src/ising.cpp
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


