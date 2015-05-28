################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/includes/framework/Matrix.cpp \
../src/includes/framework/Options.cpp \
../src/includes/framework/Pore.cpp \
../src/includes/framework/PoreArray.cpp \
../src/includes/framework/RandKnuth.cpp \
../src/includes/framework/Rock.cpp \
../src/includes/framework/SetupMatrixNeighbors.cpp \
../src/includes/framework/SetupPoreNeighbors.cpp \
../src/includes/framework/TestFunctions.cpp 

OBJS += \
./src/includes/framework/Matrix.o \
./src/includes/framework/Options.o \
./src/includes/framework/Pore.o \
./src/includes/framework/PoreArray.o \
./src/includes/framework/RandKnuth.o \
./src/includes/framework/Rock.o \
./src/includes/framework/SetupMatrixNeighbors.o \
./src/includes/framework/SetupPoreNeighbors.o \
./src/includes/framework/TestFunctions.o 

CPP_DEPS += \
./src/includes/framework/Matrix.d \
./src/includes/framework/Options.d \
./src/includes/framework/Pore.d \
./src/includes/framework/PoreArray.d \
./src/includes/framework/RandKnuth.d \
./src/includes/framework/Rock.d \
./src/includes/framework/SetupMatrixNeighbors.d \
./src/includes/framework/SetupPoreNeighbors.d \
./src/includes/framework/TestFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/includes/framework/%.o: ../src/includes/framework/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -O3  -odir "src/includes/framework" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -O3   "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


