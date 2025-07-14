#ifndef BLOWER_TASK_H_
#define BLOWER_TASK_H_

#include <stdint.h>

void BlowerTaskInit(void);

#include "blower_task.h"
#include "stm32f4xx_hal.h"
#include "os.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim2; // TIM2_CH4 - Input Capture
extern TIM_HandleTypeDef htim3; // TIM3_CH1 - PWM Output

#define BLOWER_TASK_PRIO      21u
#define BLOWER_TASK_STK_SIZE  512u
#define PULSES_PER_REV        2

static OS_TCB  blowerTaskTCB;
static CPU_STK blowerTaskStk[BLOWER_TASK_STK_SIZE];

static volatile uint32_t lastCapture = 0;
static volatile uint32_t captureDiff = 0;
static volatile uint32_t blower_rpm = 0;

void Blower_SetSpeedPercent(uint8_t percent)
{
    if (percent > 100) percent = 100;
    uint32_t period = htim3.Init.Period;
    uint32_t duty = (percent * period) / 100;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
}

uint32_t Blower_GetRPM(void)
{
    return blower_rpm;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
        uint32_t currentCapture = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);

        if (currentCapture >= lastCapture) {
            captureDiff = currentCapture - lastCapture;
        } else {
            captureDiff = (0xFFFFFFFF - lastCapture + currentCapture);
        }

        lastCapture = currentCapture;

        if (captureDiff > 0) {
            blower_rpm = (60 * 1000000UL) / (captureDiff * PULSES_PER_REV);
        }
    }
}


// RTOS task to monitor and control blower
static void BlowerTask(void *p_arg)
{
    RTOS_ERR err;
    (void)p_arg;

    printf("🔧 Blower task started\n");

    // Start timers
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);      // Start PWM
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);    // Start Input Capture with interrupt

    // Set initial speed
    Blower_SetSpeedPercent(50); // 50% duty cycle

    while (DEF_TRUE) {
        // Print RPM every second
        printf("🌀 Blower RPM: %lu\n", Blower_GetRPM());

        // Optional: adjust speed dynamically here
        // Blower_SetSpeedPercent(new_speed);

        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

// Called from main() to create the blower task
void BlowerTaskInit(void)
{
    RTOS_ERR err;

    OSTaskCreate(&blowerTaskTCB,
                 "Blower Task",
                 BlowerTask,
                 0,
                 BLOWER_TASK_PRIO,
                 &blowerTaskStk[0],
                 BLOWER_TASK_STK_SIZE / 10u,
                 BLOWER_TASK_STK_SIZE,
                 0u,
                 0u,
                 0u,
                 (OS_OPT_TASK_STK_CLR),
                 &err);
}



#endif // BLOWER_TASK_H_

#include "blower_task.h"

int main(void)
{
    RTOS_ERR err;

    HAL_Init();
    SystemClock_Config();     // Your system clock config

    MX_GPIO_Init();
    MX_TIM2_Init();           // TIM2 for TACHO input capture (PB11)
    MX_TIM3_Init();           // TIM3 for PWM output (PA6)

    OSInit(&err);             // Init Micrium OS kernel

    BlowerTaskInit();         // Create blower task

    OSStart(&err);            // Start the scheduler

    while (1); // Should never hit
}