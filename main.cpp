#include <experimental/filesystem>

namespace filesystem = std::experimental::filesystem;

#include <iostream>
#include <fstream>

#include "File_Mask.h"

int main()
{
	File_Mask mask("Makefile");

	filesystem::directory_iterator it(".");
	it = filesystem::begin(it);

	for(; it != filesystem::end(it); ++it)
	{
		if(filesystem::is_directory(*it))
			continue;

		std::string path = it->path().string();
		path = path.substr(2, path.size() - 2);	//	should remove "./" from path

		if(!mask.compare(path))
			continue;

//		std::ifstream file(path);

//		bool iso = file.is_open();

	}




	return 0;
}
