#include <iostream>
#include <fstream>
#include <string>

void my_replace(std::string& original, size_t pos, size_t len, const std::string& replacement) {
    if (pos > original.length()) {
        return ;
    }

    if (pos + len > original.length()) {
        len = original.length() - pos;
    }
    original.erase(pos, len);
    original.insert(pos, replacement);
}


int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Wrong amount of arguments" << std::endl;
		return (0);
	}

	std::string		file = argv[1];
	std::string		to_find = argv[2];
	std::string		to_replace = argv[3];
	std::string		fullFileName = file + ".replace";
	std::ifstream	FileReader(argv[1]);
	std::ofstream	FileWriter(fullFileName.c_str());
	std::string		line;
	size_t 			res;
	size_t			len = to_find.length();

	while (std::getline(FileReader, line)) 
	{
		res = 0;
    	while ((res = line.find(to_find, res + 1)) != std::string::npos)
			my_replace(line, res, len, to_replace);
		FileWriter << line << std::endl;
	}
	FileReader.close();
	FileWriter.close();
	return (0);
}