#ifndef __TIMERFN_H__
#define __TIMERFN_H__

#define TIMER_MAX_CALLBACKS 10
#define TIMER_FLAGS_EMPTY    1
#define TIMER_FLAGS_DUMMY    2

typedef struct {
	int flags;
	int ticks[TIMER_MAX_CALLBACKS];
	void (*callback[TIMER_MAX_CALLBACKS])();
//	int (*callback[TIMER_MAX_CALLBACKS])(int source);
} timerctx_t;

extern timerctx_t timeractx;

void timer_initialise();
int timer_callback(int ticks, void (*callback)());
void timer_set_dummy();
void timer_clear_dummy();
void timer_wait_for(int msDelay);
void timer_docallbacks();
int timer_is_present(void (*callback)());
int timer_is_present_remove(void (*callback)());

#endif // __TIMERFN_H__
