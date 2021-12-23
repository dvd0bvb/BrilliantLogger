import BrilliantLogger;

int main()
{

	Brilliant::InitLog<1>();
	Brilliant::InitLog(Brilliant::LogLevel::Lvl2);
	Brilliant::Log() << "Test " << 1234;
	Brilliant::Log(Brilliant::LogLevel::Lvl1) << "Level " << 1 << " test";
	Brilliant::LogIf([]() { return false; }, Brilliant::LogLevel::Error) << "Test LogIf()";

	Brilliant::Log<1>() << "Hello";

	return 0;
}