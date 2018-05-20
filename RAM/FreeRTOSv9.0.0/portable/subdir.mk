################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeRTOSv9.0.0/portable/port.c" \

C_SRCS += \
../FreeRTOSv9.0.0/portable/port.c \

S_SRCS += \
../FreeRTOSv9.0.0/portable/portasm.s \

S_SRCS_QUOTED += \
"../FreeRTOSv9.0.0/portable/portasm.s" \

S_DEPS_QUOTED += \
"./FreeRTOSv9.0.0/portable/portasm_s.d" \

OBJS += \
./FreeRTOSv9.0.0/portable/port_c.obj \
./FreeRTOSv9.0.0/portable/portasm_s.obj \

S_DEPS += \
./FreeRTOSv9.0.0/portable/portasm_s.d \

OBJS_QUOTED += \
"./FreeRTOSv9.0.0/portable/port_c.obj" \
"./FreeRTOSv9.0.0/portable/portasm_s.obj" \

C_DEPS += \
./FreeRTOSv9.0.0/portable/port_c.d \

OBJS_OS_FORMAT += \
./FreeRTOSv9.0.0/portable/port_c.obj \
./FreeRTOSv9.0.0/portable/portasm_s.obj \

C_DEPS_QUOTED += \
"./FreeRTOSv9.0.0/portable/port_c.d" \


# Each subdirectory must supply rules for building sources it contributes
FreeRTOSv9.0.0/portable/port_c.obj: ../FreeRTOSv9.0.0/portable/port.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/portable/port.args" -o "FreeRTOSv9.0.0/portable/port_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/portable/%.d: ../FreeRTOSv9.0.0/portable/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

FreeRTOSv9.0.0/portable/portasm_s.obj: ../FreeRTOSv9.0.0/portable/portasm.s
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: PowerPC Assembler'
	"$(PAToolsDirEnv)/mwasmeppc" @@"FreeRTOSv9.0.0/portable/portasm.args" -o "FreeRTOSv9.0.0/portable/portasm_s.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/portable/%.d: ../FreeRTOSv9.0.0/portable/%.s
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


