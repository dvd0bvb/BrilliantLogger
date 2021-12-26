export module BrilliantLogger;

import <optional>;
import <source_location>;
import <concepts>;

import LogLevel;
import LogLine;
import LogStream;

//unsure why I need compare outside of this module or even in this module
export import <compare>;
export import Common;

export namespace Brilliant
{
	template<LoggerId Id> class Logger;

	template<LoggerId Id = iDefaultLogId>
	void InitLog(LogLevel iMaxLevel = LogLevel::None, std::string_view svOut = svCOUT) noexcept
	{
		Logger<Id>::Init(iMaxLevel, svOut);
	}

	template<LoggerId = iDefaultLogId>
	void InitLog(std::string_view svOut) noexcept
	{
		InitLog<LoggerId>(LogLevel::None, svOut);
	}

	template <LoggerId Id = iDefaultLogId>
	Logger<Id> Log(LogLevel level = LogLevel::None, std::source_location loc = std::source_location::current()) noexcept
	{
		return Logger<Id>::InitLine(level, loc, true);
	}

	template <LoggerId Id = iDefaultLogId, std::invocable Pred>
	Logger<Id> LogIf(Pred predicate, LogLevel level = LogLevel::None, std::source_location loc = std::source_location::current()) noexcept
	{
		return Logger<Id>::InitLine(level, loc, std::invoke(predicate));
	}

	struct LogInfo
	{
		LogInfo(LogLevel level, std::string_view svOut) : iMaxLevel(level), line(std::nullopt), outputter(svOut) { }

		LogLevel iMaxLevel;
		std::optional<LogLine> line;
		LogStream outputter;
		static LoggerId iLastLogger;
	};

	LoggerId LogInfo::iLastLogger = 0u;

	template <LoggerId Id>
	class Logger
	{
		using logger_t = Logger<Id>;

	public:
		static void Init(LogLevel iMaxLevel, std::string_view svOut) noexcept
		{
			logger_t logger{};
			logger.info.emplace(iMaxLevel, svOut);
		}

		static logger_t InitLine(LogLevel level, std::source_location loc, bool bLineAllowed) noexcept
		{
			logger_t logger{};
			if (bLineAllowed)
			{
				logger.StartNewLine(level, loc);
			}
			else
			{
				logger.info->line.reset();
			}
			return logger;
		}

		explicit operator bool() const noexcept
		{
			return static_cast<bool>(info);
		}

		template<class T>
		logger_t& operator<<(T&& t) noexcept
		{
			if (*this && info->line)
			{
				info->outputter << std::forward<T>(t);
			}
			return *this;
		}

	private:
		void StartNewLine(LogLevel level, std::source_location loc) noexcept
		{
			if (*this)
			{
				if (info->iMaxLevel >= level)
				{
					if (info->line || info->iLastLogger != Id)
					{
						info->outputter << '\n';
						info->iLastLogger = Id;
					}

					info->line.emplace(level, loc);
					info->outputter << "Logger Id: " << Id << ' ' << *info->line;
				}
				else if(info->line)
				{
					info->line.reset();
				}
			}
		}

		static std::optional<LogInfo> info;
	};

	template<LoggerId Id> std::optional<LogInfo> Logger<Id>::info = std::nullopt;
}

