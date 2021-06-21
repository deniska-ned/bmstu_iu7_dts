#ifndef __TIMER_H__

#define __TIMER_H__ 

#include <stdint.h>
#include <inttypes.h>

/**
 * @return Return time stamp counter
 */
uint64_t curr_ticks(void);

#endif // __TIMER_H__
