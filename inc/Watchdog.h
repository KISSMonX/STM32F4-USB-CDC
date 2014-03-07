#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#ifndef WATCHDOG_DISABLED
	void WatchDogInit( void );
#else
	#define WatchDogInit()
	#warning "+-+-+-+-+-+-+ WATCHDOG DISABLED !!! +-+-+-+-+-+-+-+"
#endif

#ifndef WATCHDOG_DISABLED
	void WatchDogRefresh( void );
#else
	#define WatchDogRefresh()
#endif

#endif // WATCHDOG_H_
