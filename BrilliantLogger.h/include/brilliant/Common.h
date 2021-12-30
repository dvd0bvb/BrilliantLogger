#ifndef BRILLIANTLOGGER_COMMON_H
#define BRILLIANTLOGGER_COMMON_H

#include <string_view>

namespace Brilliant
{
	using LoggerId = unsigned int;
	static constexpr LoggerId iDefaultLogId = 0u;
	static constexpr std::string_view svCOUT = "std_cout";
	static constexpr std::string_view svCERR = "std_cerr";
}

#endif
