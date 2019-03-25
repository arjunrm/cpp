#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ostream>
#include <string>

template <typename Time_T = std::chrono::milliseconds>
class Timer
{
	Time_T _start;
	Time_T _end;
	Time_T _duration;
	std::string _unit;
	std::ostream& _stream;
public:
	explicit Timer(std::string unit = "ms", std::ostream& stream = std::cout)
		: _unit(unit)
		, _stream(stream)
	{
		_start = std::chrono::duration_cast<Time_T>(std::chrono::steady_clock::now().time_since_epoch());
	}

	~Timer()
	{
		_end = std::chrono::duration_cast<Time_T>(std::chrono::steady_clock::now().time_since_epoch());
		_duration = _end - _start;

		_stream << std::endl << "----------------------------------------------";
		_stream << std::endl << "Time";
		_stream << std::endl << "   StartTime : " << _start.count() << " " << _unit;
		_stream << std::endl << "   EndTime   : " << _end.count() << " " << _unit;
		_stream << std::endl << "   Duration  : " << _duration.count() << " " << _unit;
		_stream << std::endl << "----------------------------------------------" << std::endl;
	}
};

#endif
