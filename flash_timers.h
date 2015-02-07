#ifndef __FLASH_TIMERS_H__
#define __FLASH_TIMERS_H__

#define MAX_TIMERS 10

typedef void (* timer_callback)();

#ifdef __cplusplus
extern "C" {
#endif

void FlashTimers_Init();

void FlashTimers_AddTimer(int time);

void FlashTimers_DecreaseTimers(int period, timer_callback callback);

void FlashTimers_DebugTimers();

int FlashTimers_Count();

void FlashTimers_Idle();

void FlashTimers_SetCallback(timer_callback c);

void FlashTimers_SetDeadTime(int time);

#ifdef __cplusplus
}
#endif

#endif
