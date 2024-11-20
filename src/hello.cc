import std;

std::string hello_world(const std::string& name)
{
	const std::string greeting { std::format("Hello, {}!", name) };
	std::println("Hello, {}!", name);
	return greeting;
}
