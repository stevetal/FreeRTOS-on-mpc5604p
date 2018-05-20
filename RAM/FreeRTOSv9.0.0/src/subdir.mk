################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../FreeRTOSv9.0.0/src/croutine.c" \
"../FreeRTOSv9.0.0/src/event_groups.c" \
"../FreeRTOSv9.0.0/src/list.c" \
"../FreeRTOSv9.0.0/src/queue.c" \
"../FreeRTOSv9.0.0/src/tasks.c" \
"../FreeRTOSv9.0.0/src/timers.c" \

C_SRCS += \
../FreeRTOSv9.0.0/src/croutine.c \
../FreeRTOSv9.0.0/src/event_groups.c \
../FreeRTOSv9.0.0/src/list.c \
../FreeRTOSv9.0.0/src/queue.c \
../FreeRTOSv9.0.0/src/tasks.c \
../FreeRTOSv9.0.0/src/timers.c \

OBJS += \
./FreeRTOSv9.0.0/src/croutine_c.obj \
./FreeRTOSv9.0.0/src/event_groups_c.obj \
./FreeRTOSv9.0.0/src/list_c.obj \
./FreeRTOSv9.0.0/src/queue_c.obj \
./FreeRTOSv9.0.0/src/tasks_c.obj \
./FreeRTOSv9.0.0/src/timers_c.obj \

OBJS_QUOTED += \
"./FreeRTOSv9.0.0/src/croutine_c.obj" \
"./FreeRTOSv9.0.0/src/event_groups_c.obj" \
"./FreeRTOSv9.0.0/src/list_c.obj" \
"./FreeRTOSv9.0.0/src/queue_c.obj" \
"./FreeRTOSv9.0.0/src/tasks_c.obj" \
"./FreeRTOSv9.0.0/src/timers_c.obj" \

C_DEPS += \
./FreeRTOSv9.0.0/src/croutine_c.d \
./FreeRTOSv9.0.0/src/event_groups_c.d \
./FreeRTOSv9.0.0/src/list_c.d \
./FreeRTOSv9.0.0/src/queue_c.d \
./FreeRTOSv9.0.0/src/tasks_c.d \
./FreeRTOSv9.0.0/src/timers_c.d \

OBJS_OS_FORMAT += \
./FreeRTOSv9.0.0/src/croutine_c.obj \
./FreeRTOSv9.0.0/src/event_groups_c.obj \
./FreeRTOSv9.0.0/src/list_c.obj \
./FreeRTOSv9.0.0/src/queue_c.obj \
./FreeRTOSv9.0.0/src/tasks_c.obj \
./FreeRTOSv9.0.0/src/timers_c.obj \

C_DEPS_QUOTED += \
"./FreeRTOSv9.0.0/src/croutine_c.d" \
"./FreeRTOSv9.0.0/src/event_groups_c.d" \
"./FreeRTOSv9.0.0/src/list_c.d" \
"./FreeRTOSv9.0.0/src/queue_c.d" \
"./FreeRTOSv9.0.0/src/tasks_c.d" \
"./FreeRTOSv9.0.0/src/timers_c.d" \


# Each subdirectory must supply rules for building sources it contributes
FreeRTOSv9.0.0/src/croutine_c.obj: ../FreeRTOSv9.0.0/src/croutine.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/src/croutine.args" -o "FreeRTOSv9.0.0/src/croutine_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/src/%.d: ../FreeRTOSv9.0.0/src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

FreeRTOSv9.0.0/src/event_groups_c.obj: ../FreeRTOSv9.0.0/src/event_groups.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/src/event_groups.args" -o "FreeRTOSv9.0.0/src/event_groups_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/src/list_c.obj: ../FreeRTOSv9.0.0/src/list.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/src/list.args" -o "FreeRTOSv9.0.0/src/list_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/src/queue_c.obj: ../FreeRTOSv9.0.0/src/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/src/queue.args" -o "FreeRTOSv9.0.0/src/queue_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/src/tasks_c.obj: ../FreeRTOSv9.0.0/src/tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/src/tasks.args" -o "FreeRTOSv9.0.0/src/tasks_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSv9.0.0/src/timers_c.obj: ../FreeRTOSv9.0.0/src/timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"FreeRTOSv9.0.0/src/timers.args" -o "FreeRTOSv9.0.0/src/timers_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


