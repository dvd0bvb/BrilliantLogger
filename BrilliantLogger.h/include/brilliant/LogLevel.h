#ifndef BRILLIANTLOGGER_LOGLEVEL_H
#define BRILLIANTLOGGER_LOGLEVEL_H

#include <ostream>

namespace Brilliant
{
	enum class LogLevel
	{
		Error,
		None,		
		Lvl1,
		Lvl2,
		Lvl3
	};

	std::ostream& operator<< (std::ostream& os, const LogLevel level)
	{
		switch (level)
		{
		case LogLevel::None:
			os << "None";
			break;
		case LogLevel::Lvl1:
			os << "Lvl1";
			break;
		case LogLevel::Lvl2:
			os << "Lvl2";
			break;
		case LogLevel::Lvl3:
			os << "Lvl3";
			break;
		case LogLevel::Error:
			os << "Error";
			break;
		}
		return os;
	}
}

#endif