#pragma warning(disable : 4996)
#include "timer.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

timer::timer() {}
timer::~timer() {}

void timer::start() {
	m_start_point = std::chrono::steady_clock::now();
	m_start_stamp = std::chrono::system_clock::now();

	std::cout << "Application start up time: ";
	show_time(m_start_stamp);
}

void timer::stop() {
	std::cout << " Application finished at: ";
	time_stamp curr_time = std::chrono::system_clock::now();
	show_time(curr_time);
}

void timer::current_time() {
	std::cout << " Current time: ";
	time_stamp curr_time = std::chrono::system_clock::now();
	show_time(curr_time);
}

void timer::current_duration() {
	
}

void timer::show_time(const time_stamp &in_time_stamp) {
	const std::time_t t_c = std::chrono::system_clock::to_time_t(in_time_stamp);
	std::cout << std::put_time(std::localtime(&t_c), "%F %T.\n") << std::endl;
}
