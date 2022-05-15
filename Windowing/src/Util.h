#include <iostream>
#include <sstream>
#include <fstream>

namespace Util {
	std::string loadfile(const std::string& path);
}

namespace Util {
	std::string loadfile(const std::string& path) {
		std::stringstream result;
		std::ifstream stream(path);

		if (stream.is_open()) {
			std::string line;
			while (getline(stream, line))
			{
				result << line << '\n';
			}
			stream.close();
		}
		else
			std::cout << "Unable to open file\n";

		return result.str();
	}
}