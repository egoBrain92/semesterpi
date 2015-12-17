################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AudioPlayer.cpp \
../ISensor.cpp \
../Projekt.cpp \
../SensorLow.cpp \
../SensorMid.cpp \
../SensorUp.cpp 

OBJS += \
./AudioPlayer.o \
./ISensor.o \
./Projekt.o \
./SensorLow.o \
./SensorMid.o \
./SensorUp.o 

CPP_DEPS += \
./AudioPlayer.d \
./ISensor.d \
./Projekt.d \
./SensorLow.d \
./SensorMid.d \
./SensorUp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


