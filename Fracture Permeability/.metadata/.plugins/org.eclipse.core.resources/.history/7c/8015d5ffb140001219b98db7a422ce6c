################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/framework/Matrix.cpp \
../src/framework/Options.cpp \
../src/framework/Pore.cpp \
../src/framework/PoreArray.cpp \
../src/framework/RandKnuth.cpp \
../src/framework/Rock.cpp \
../src/framework/SetupMatrixNeighbors.cpp \
../src/framework/SetupPoreNeighbors.cpp \
../src/framework/TestFunctions.cpp 

OBJS += \
./src/framework/Matrix.o \
./src/framework/Options.o \
./src/framework/Pore.o \
./src/framework/PoreArray.o \
./src/framework/RandKnuth.o \
./src/framework/Rock.o \
./src/framework/SetupMatrixNeighbors.o \
./src/framework/SetupPoreNeighbors.o \
./src/framework/TestFunctions.o 

CPP_DEPS += \
./src/framework/Matrix.d \
./src/framework/Options.d \
./src/framework/Pore.d \
./src/framework/PoreArray.d \
./src/framework/RandKnuth.d \
./src/framework/Rock.d \
./src/framework/SetupMatrixNeighbors.d \
./src/framework/SetupPoreNeighbors.d \
./src/framework/TestFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/framework/%.o: ../src/framework/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -G -g -O0  -odir "src/framework" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


