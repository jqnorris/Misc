################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IP_Earthquake.cpp 

OBJS += \
./src/IP_Earthquake.o 

CPP_DEPS += \
./src/IP_Earthquake.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -O3  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -O3 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


