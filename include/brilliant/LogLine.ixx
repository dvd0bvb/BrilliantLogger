export module LogLine;

import <format>;
import <ostream>;
import <source_location>;
import <filesystem>;
import <iterator>;

import LogLevel;

export namespace Brilliant
{
	struct LogLine
	{
		LogLevel iLevel;
		std::source_location location;
	};

	inline std::ostream& operator<< (std::ostream& os, const LogLine& line) noexcept
	{
		std::filesystem::path file{ line.location.file_name() };
		os << "Level: " << line.iLevel;
		std::format_to(std::ostream_iterator<std::decay_t<decltype(os)>::char_type>{ os }, " {:>20} {:>30}() {:>10} ", file.filename().string(), line.location.function_name(), line.location.line());
		return os;
	}
}