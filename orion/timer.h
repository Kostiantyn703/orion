#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class timer {
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;
	using time_stamp = std::chrono::time_point<std::chrono::system_clock>;
public:
	timer();
	~timer();

	void start();
	void stop();

	void current_clock();
	float get_current_time();

private:
	time_point m_start_point;
	time_stamp m_start_stamp;

	void show_time(const time_stamp &in_time_stamp);
};

#endif // TIMER_H
