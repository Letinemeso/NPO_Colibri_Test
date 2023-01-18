#include <experimental/filesystem>

namespace filesystem = std::experimental::filesystem;

#include <iostream>
#include <fstream>

#include "File_Mask.h"
#include "File_Encryptor.h"

int main()
{
	File_Mask mask("*.txt");

	filesystem::directory_iterator it("../");
	it = filesystem::begin(it);

//	filesystem::create_directory("./Folder");

	File_Encryptor encr;
	encr.set_rewrite_permission(true);
	encr.set_numered_file_copy_limit(5);
//	encr.set_code((unsigned long int)(-1));
	encr.set_code(6827226174);

	bool remove_input = false;


	for(; it != filesystem::end(it); ++it)
	{
		if(filesystem::is_directory(*it))
			continue;

		std::string path = it->path().string();

		std::string filename;
		unsigned int offset = path.size() - 1;
		for(; offset != 0; --offset)
		{
			if(path[offset] == '/')
			{
				++offset;
				break;
			}
		}
		filename = path.substr(offset, path.size() - offset);
		path = path.substr(0, offset);

		if(!mask.compare(path + filename))
			continue;

		encr.load_file(path, filename);

		encr.save_file_enctypted(path + "Test/", filename);

		if(remove_input)
			std::remove(it->path().string().c_str());

		continue;
	}




	return 0;
}
