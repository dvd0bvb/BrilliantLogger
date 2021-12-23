export module Common;

//export string view for convenience in other modules
export import <string_view>;

export namespace Brilliant
{
	using LoggerId = unsigned int;
	static constexpr LoggerId iDefaultLogId = 0u;
	static constexpr std::string_view svCOUT = "std_cout";
	static constexpr std::string_view svCERR = "std_cerr";
}