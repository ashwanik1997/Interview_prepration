// Includes #include "stm32f4xx_hal.h" #include <stdbool.h> #include "os.h"

// Handles TIM_HandleTypeDef htim3; TIM_HandleTypeDef htim9;

// Audio sample array (external) extern const uint8_t audioSamples[]; extern const uint16_t audioSamplesSize;

// Audio state machine typedef enum { QuietBurstMsb, QuietBurstLsb, AlarmBurstMsb, AlarmBurstLsb, AlarmPulseSpacingMsb, AlarmPulseSpacingLsb, AlarmInterburstIntervalMsb, AlarmInterburstIntervalLsb } AudioState;

volatile AudioState audioState = QuietBurstMsb; volatile uint8_t alarmBurst = 0; volatile uint16_t audioFileByteCount = 0; volatile uint32_t audioQuietByteCount = 0; volatile bool audioOn = false; volatile bool audioTestPending = true; #define alarmNumBursts 5

#define AUDIO_TASK_PRIO      5 #define AUDIO_TASK_STK_SIZE 256 OS_TCB AudioTaskTCB; CPU_STK AudioTaskStk[AUDIO_TASK_STK_SIZE];

// Function to enable/disable audio void audiowrite(bool enable) { audioOn = enable; }

// Initialize TIM3 (PWM on CH3 - PB0) void MX_TIM3_Init(void) { __HAL_RCC_TIM3_CLK_ENABLE(); __HAL_RCC_GPIOB_CLK_ENABLE();

GPIO_InitTypeDef GPIO_InitStruct = {0};
GPIO_InitStruct.Pin = GPIO_PIN_0;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

htim3.Instance = TIM3;
htim3.Init.Prescaler = 83;
htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
htim3.Init.Period = 255;
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
HAL_TIM_PWM_Init(&htim3);

TIM_OC_InitTypeDef sConfigOC = {0};
sConfigOC.OCMode = TIM_OCMODE_PWM1;
sConfigOC.Pulse = 0;
sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);

}

// Initialize TIM9 (Sample rate timer) void MX_TIM9_Init(void) { __HAL_RCC_TIM9_CLK_ENABLE();

htim9.Instance = TIM9;
htim9.Init.Prescaler = 83;
htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
htim9.Init.Period = 24;
htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
HAL_TIM_Base_Init(&htim9);

HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 0, 0);
HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

}

// TIM9 IRQ handler void TIM1_BRK_TIM9_IRQHandler(void) { HAL_TIM_IRQHandler(&htim9); }

// Timer ISR void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { static uint8_t lsb;

if (htim->Instance == TIM9) {
    switch (audioState) {
        case QuietBurstMsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[0]);
            audioState = QuietBurstLsb;
            break;

        case QuietBurstLsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[1]);
            if (audioOn || audioTestPending) {
                alarmBurst = 0;
                audioFileByteCount = 0;
                audioState = AlarmBurstMsb;
            } else {
                audioState = QuietBurstMsb;
            }
            break;

        case AlarmBurstMsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[audioFileByteCount + 4]);
            lsb = audioSamples[audioFileByteCount++];
            audioState = AlarmBurstLsb;
            break;

        case AlarmBurstLsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, lsb);
            if (audioFileByteCount >= audioSamplesSize) {
                audioQuietByteCount = 0;
                if (audioTestPending) {
                    audioTestPending = false;
                    audioState = QuietBurstMsb;
                } else {
                    audioState = (++alarmBurst < alarmNumBursts)
                                 ? AlarmPulseSpacingMsb
                                 : AlarmInterburstIntervalMsb;
                }
            } else {
                audioState = AlarmBurstMsb;
            }
            break;

        case AlarmPulseSpacingMsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[0]);
            audioQuietByteCount++;
            audioState = AlarmPulseSpacingLsb;
            break;

        case AlarmPulseSpacingLsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[1]);
            if (++audioQuietByteCount >= 5120) {
                audioFileByteCount = 0;
                audioState = AlarmBurstMsb;
            } else {
                audioState = AlarmPulseSpacingMsb;
            }
            break;

        case AlarmInterburstIntervalMsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[0]);
            audioQuietByteCount++;
            audioState = AlarmInterburstIntervalLsb;
            break;

        case AlarmInterburstIntervalLsb:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, audioSamples[1]);
            if (++audioQuietByteCount >= 153520) {
                if (audioOn) {
                    alarmBurst = 0;
                    audioFileByteCount = 0;
                    audioState = AlarmBurstMsb;
                } else {
                    audioState = QuietBurstMsb;
                }
            } else {
                audioState = AlarmInterburstIntervalMsb;
            }
            break;
    }
}

}

// FSM for audio triggering static void appAudioFsm(uint8_t event, uint8_t eventData) { static uint16_t rxMatchingTimer;

switch (event)
{
    case 0: // InitEvent
        rxMatchingTimer = 0;
        break;

    case 1: // TimerTickEvent
        if (rxMatchingTimer < UINT16_MAX)
            rxMatchingTimer++;
        if (rxMatchingTimer > 5000)
            audiowrite(true);
        break;

    case 2: // ValidStatusByteReceived
        rxMatchingTimer = 0;
        if ((eventData & 0x01) != 0)
            audiowrite(true);
        else
            audiowrite(false);
        break;
}

}

// Micrium OS task void AudioTask(void *p_arg) { (void)p_arg; appAudioFsm(0, 0); // InitEvent

while (1)
{
    OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, NULL); // 10ms delay
    appAudioFsm(1, 0); // TimerTickEvent
}

}

// Main application int main(void) { OS_ERR os_err;

HAL_Init();
SystemClock_Config();
MX_TIM3_Init();
MX_TIM9_Init();

OSInit(&os_err);

OSTaskCreate(&AudioTaskTCB,
             "Audio Task",
             AudioTask,
             0,
             AUDIO_TASK_PRIO,
             &AudioTaskStk[0],
             AUDIO_TASK_STK_SIZE / 10,
             AUDIO_TASK_STK_SIZE,
             0,
             0,
             0,
             (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             &os_err);

HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
HAL_TIM_Base_Start_IT(&htim9);

OSStart(&os_err);

while (1) {}

}

