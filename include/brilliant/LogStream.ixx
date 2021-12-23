export module LogStream;

import <iostream>;
import <memory>;
import <fstream>;
import Common;

namespace Brilliant
{
	class ILogStreamBase
	{
	public:
		virtual ~ILogStreamBase() = default;
		virtual void Flush() noexcept = 0;
		virtual explicit operator bool() const noexcept = 0;
	};

	class ILogStream : public ILogStreamBase
	{
	public:
		ILogStream(std::ostream& os) : pOs(&os)
		{

		}

		template<class T>
		inline void operator<< (T&& t) noexcept
		{
			(*pOs) << std::forward<T>(t);
		}

	protected:
		std::ostream* GetStream() noexcept
		{
			return pOs;
		}

		std::ostream* GetStream() const noexcept
		{
			return pOs;
		}

	private:
		//not owned, necessary for << operator
		std::ostream* pOs;
	};

	class UnownedStream : public ILogStream
	{
	public:
		UnownedStream(std::ostream& os) : ILogStream(os)
		{

		}

		void Flush() noexcept
		{
			GetStream()->flush();
		}

		explicit operator bool() const noexcept
		{
			return GetStream() && static_cast<bool>(*GetStream());
		}
	};

	class FileStream : public ILogStream
	{
	public:
		FileStream(std::string_view svFile) : ILogStream(of), of(svFile.data())
		{
			
		}

		void Flush() noexcept
		{
			of.flush();
		}

		explicit operator bool() const noexcept
		{
			return static_cast<bool>(of);
		}
	private:
		std::ofstream of;
	};

	//only need to export LogStream class
	export class LogStream : public ILogStreamBase
	{
	public:
		LogStream(std::string_view svOut) : stream(MakeStream(svOut))
		{

		}

		LogStream(std::ostream& os) : stream(MakeStream(os))
		{

		}

		~LogStream() = default;

		LogStream(LogStream&& other) : stream(std::move(other.stream))
		{

		}

		LogStream& operator= (LogStream&& other)
		{
			stream = std::move(other.stream);
			return *this;
		}

		LogStream(LogStream&) = delete;
		LogStream& operator= (LogStream&) = delete;

		explicit operator bool() const noexcept
		{
			return stream && static_cast<bool>(*stream);
		}

		void Flush() noexcept
		{
			stream->Flush();
		}

		template<class T>
		inline LogStream& operator<< (T&& t) noexcept
		{
			if (*this)
			{
				(* stream) << std::forward<T>(t);
			}
			return *this;
		}

	private:
		static std::unique_ptr<ILogStream> MakeStream(std::string_view svOut) noexcept
		{
			if (svOut == svCOUT)
			{
				return std::make_unique<UnownedStream>(std::cout);
			}
			else if (svOut == svCERR)
			{
				return std::make_unique<UnownedStream>(std::cerr);
			}
			else
			{
				return std::make_unique<FileStream>(svOut);
			}
		}

		static std::unique_ptr<ILogStream> MakeStream(std::ostream& os) noexcept
		{
			return std::make_unique<UnownedStream>(os);
		}

		std::unique_ptr<ILogStream> stream;
	};
}