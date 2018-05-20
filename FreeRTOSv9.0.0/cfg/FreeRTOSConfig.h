/*
    SPC5 FreeRTOS - Copyright (C) 2015 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License").
    You may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    FreeRTOSConfig.h
 * @brief   FreeRTOS configuration header.
 * @details FreeRTOS is customised using a configuration file called FreeRTOSConfig.h.
 *          Every FreeRTOS application must have a FreeRTOSConfig.h header file in its
 *          pre-processor include path.
 *          FreeRTOSConfig.h tailors the RTOS kernel to the application being built.
 * @addtogroup FREERTOS_CONFIG
 * @{
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/**
 * @name    FreeRTOS configuration
 */

/**
 * @brief   Set to 1 to use the preemptive RTOS scheduler, or 0 to use the cooperative RTOS scheduler.
 */
#define configUSE_PREEMPTION                 1

/**
 * @brief   Set to 1 to use prioritised preemptive scheduling with time slicing (configUSE_PREEMPTION must be set to 1).
 */
#define configUSE_TIME_SLICING               1

/**
 * @brief   Set the frequency in Hz at which the internal clock that drives the peripheral used to generate the tick interrupt.
 */
#define configCPU_CLOCK_HZ                   64000000

/**
 * @brief   Set the frequency of the RTOS tick interrupt.
 */
#define configTICK_RATE_HZ                   1000

/**
 * @brief   Set to 1 to cause TickType_t (tick counter type) to be defined ans an unsigned 16bit type.
 */
#define configUSE_16_BIT_TICKS               0

/**
 * @brief   The number of priorities available to the application tasks.
 */
#define configMAX_PRIORITIES                 4

/**
 * @brief   The maximum permissible length of the descriptive name given to a task when the task is created.
 */
#define configMAX_TASK_NAME_LEN              16

/**
 * @brief   This parameter controls the behaviour of tasks at the idle priority.
 */
#define configIDLE_SHOULD_YIELD              1

/**
 * @brief   The size (in words - 4 bytes each) of the stack used by the idle task.
 */
#define configMINIMAL_STACK_SIZE             256


/*
 * Mutex and semaphores
 */
 
/**
 * @brief   Set to 1 to include mutex functionality.
 */
#define configUSE_MUTEXES                    1

/**
 * @brief   Set to 1 to include recursive mutex functionality.
 */
#define configUSE_RECURSIVE_MUTEXES          0

/**
 * @brief   Set to 1 to include counting semaphore functionality.
 */
#define configUSE_COUNTING_SEMAPHORES        0


/*
 * Co-routines
 */

/**
 * @brief   Set to 1 to include co-routine functionality.
 */
#define configUSE_CO_ROUTINES                0

/**
 * @brief   The number of priorities available to the application co-routines.
 */
#define configMAX_CO_ROUTINE_PRIORITIES      4


/*
 * Memory allocation
 */
 
/**
 * @brief   The total (in bytes) amount of RAM available in the FreeRTOS heap.
 */
#define configTOTAL_HEAP_SIZE                8192

/**
 * @brief   Set to 1 to get RTOS objects created using RAM provided by the application.
 */
#define configSUPPORT_STATIC_ALLOCATION      0

/**
 * @brief   Set to 1 to get RTOS objects created using RAM automatically allocated from the FreeRTOS heap.
 */
#define configSUPPORT_DYNAMIC_ALLOCATION     1

/**
 * @brief   Set to 1 to get the heap memory declared and allocated by the application.
 */
#define configAPPLICATION_ALLOCATED_HEAP     0


/*
 * Hook functions
 */

/**
 * @brief   Set to 1 to use an idle hook function [void vApplicationIdleHook(void)].
 */
#define configUSE_IDLE_HOOK                  0

/**
 * @brief   Set to 1 to use a tick hook function [void vApplicationTickHook(void)].
 */
#define configUSE_TICK_HOOK                  0

/**
 * @brief   Set to 1 to use stack check overflow functionality.
 */
#define configCHECK_FOR_STACK_OVERFLOW       0

/**
 * @brief   Set to 1 to use a malloc failed hook function [void vApplicationMallocFailedHook(void)].
 */
#define configUSE_MALLOC_FAILED_HOOK         0


/*
 * Tracing and stats
 */

#define configGENERATE_RUN_TIME_STATS        0

#define configUSE_TRACE_FACILITIES           0

#define configUSE_STATS_FORMATTING_FUNCTIONS 0


/*
 * Software timers configuration
 */
#define configUSE_TIMERS                     0

#define configTIMER_TASK_PRIORITY            3
#define configTIMER_QUEUE_LENGTH             10
#define configTIMER_TASK_STACK_DEPTH         2048


/*
 * Queue configuration
 */
#define configQUEUE_REGISTRY_SIZE            4

#define configUSE_QUEUE_SETS                 0


/*
 * API Configuration
 */

#define INCLUDE_vTaskPrioritySet             1

#define INCLUDE_uxTaskPriorityGet            1

#define INCLUDE_vTaskDelete                  0

#define INCLUDE_vTaskSuspend                 1

#define INCLUDE_vResumeFromISR               1

#define INCLUDE_vTaskDelayUntil              1

#define INCLUDE_vTaskDelay                   1

#define INCLUDE_xTaskGetSchedulerState       0

#define INCLUDE_xTaskGetCurrentTaskHandle    0

#define INCLUDE_uxTaskGetStackHighWaterMark  0

#define INCLUDE_xTaskGetIdleTaskHandle       0

#define INCLUDE_eTaskGetState                0

#define INCLUDE_eTaskGetHandle               0


#endif /* FREERTOS_CONFIG_H */

/** @} */
