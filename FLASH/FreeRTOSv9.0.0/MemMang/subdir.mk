################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeRTOSv9.0.0/MemMang/heap_2.c" \

C_SRCS += \
../FreeRTOSv9.0.0/MemMang/heap_2.c \

OBJS += \
./FreeRTOSv9.0.0/MemMang/heap_2_c.obj \

OBJS_QUOTED += \
"./FreeRTOSv9.0.0/MemMang/heap_2_c.obj" \

C_DEPS += \
./FreeRTOSv9.0.0/MemMang/heap_2_c.d \

OBJS_OS_FORMAT += \
./FreeRTOSv9.0.0/MemMang/heap_2_c.obj \

C_DEPS_QUOTED += \
"./FreeRTOSv9.0.0/MemMang/heap_2_c.d" \


# Each subdirectory must supply rules for building sources it contributes
FreeRTOSv9.0.0/MemMang/heap_2_c.obj: ../FreeRTOSv9.0.0/MemMang/heap_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/MemMang/heap_2.args" -o "FreeRTOSv9.0.0/MemMang/heap_2_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/MemMang/%.d: ../FreeRTOSv9.0.0/MemMang/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


