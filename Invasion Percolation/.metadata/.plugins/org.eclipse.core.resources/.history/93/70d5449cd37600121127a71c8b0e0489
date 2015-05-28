################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/framework/Matrix.cpp \
../src/framework/Options.cpp \
../src/framework/Pore.cpp \
../src/framework/PoreArray.cpp \
../src/framework/Rock.cpp \
../src/framework/SetupMatrixNeighbors.cpp \
../src/framework/SetupPoreNeighbors.cpp 

OBJS += \
./src/framework/Matrix.o \
./src/framework/Options.o \
./src/framework/Pore.o \
./src/framework/PoreArray.o \
./src/framework/Rock.o \
./src/framework/SetupMatrixNeighbors.o \
./src/framework/SetupPoreNeighbors.o 

CPP_DEPS += \
./src/framework/Matrix.d \
./src/framework/Options.d \
./src/framework/Pore.d \
./src/framework/PoreArray.d \
./src/framework/Rock.d \
./src/framework/SetupMatrixNeighbors.d \
./src/framework/SetupPoreNeighbors.d 


# Each subdirectory must supply rules for building sources it contributes
src/framework/%.o: ../src/framework/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -O3  -odir "src/framework" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -O3 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


