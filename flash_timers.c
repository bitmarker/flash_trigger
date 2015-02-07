#include "flash_timers.h"

int FlashTimers_States[MAX_TIMERS];
int timer_count;

timer_callback callback;

int dead_time_max = 0;
int dead_time_current = 0;

void FlashTimers_Init()
{
  int i;
  timer_count = 0;
  for (i = 0; i < MAX_TIMERS; i++)
  {
    FlashTimers_States[i] = 0;
  }
}

void FlashTimers_SetCallback(timer_callback c)
{
  callback = c;
}

void FlashTimers_SetDeadTime(int time)
{
  dead_time_max = time;
}

void FlashTimers_AddTimer(int time)
{
  if (timer_count < MAX_TIMERS && dead_time_current == 0)
  {
    FlashTimers_States[timer_count] = time;
    timer_count++;
    dead_time_current = dead_time_max;
  }
}

void FlashTimers_DecreaseTimers(int period, timer_callback callback)
{
  int i, s;
  
  for (i = 0; i < timer_count; i++)
  {
    // Timer is stil active
    if (FlashTimers_States[i] > period)
    {
      FlashTimers_States[i] -= period;
    }
    else // Timer descreased to zero
    {
      (*callback)();

      // Shift all timers after the ith timer
      for (s = i + 1; s < MAX_TIMERS; s++)
      {
        FlashTimers_States[s - 1] = FlashTimers_States[s];
      }

      timer_count--;
      i--;
    }
  }
}

void FlashTimers_Idle()
{
  if (FlashTimers_Count() > 0)
  {
    FlashTimers_DecreaseTimers(1, callback);
  }
  
  if(dead_time_current > 0)
  {
    dead_time_current--;
  }
}

void FlashTimers_DebugTimers()
{
  int i;
  for (i = 0; i < timer_count; i++)
  {
    //_printf("%d: %d\n", i, FlashTimers_States[i]);
  }
}

int FlashTimers_Count()
{
  return timer_count;
}
