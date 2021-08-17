#include "main.h"
#include "time.h"
extern RTC_HandleTypeDef RtcHandle;

//int clock_gettime_test (struct timespec *tp)
int clock_gettime (clockid_t clock_id, struct timespec *tp)
{
	
  
//  RTC_DateTypeDef sdatestructureget;
//  RTC_TimeTypeDef stimestructureget;
  
  
  if (tp == NULL) {
         
          return -1;
      }
  
	
//  /* Get the RTC current Time */
//  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
//  /* Get the RTC current Date */
//  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
//
//  tp->tv_sec = stimestructureget.Seconds + stimestructureget.Minutes * 60;
//  tp->tv_nsec = 0;
  tp->tv_sec= osKernelSysTick()/1000;
  tp->tv_nsec = (osKernelSysTick() % 1000 ) *1000000;
  return 0;
} 
