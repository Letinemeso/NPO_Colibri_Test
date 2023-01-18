#include <experimental/filesystem>

namespace filesystem = std::experimental::filesystem;

#include <iostream>
#include <fstream>

#include "File_Processor.h"

int main()
{
	//	i haven't put a lot of effort into "ui" design due to limited time and lack of necessity :)

	File_Processor processor;

	std::cout << "Hello, Simple Encoder User! Please specify some options below:\n\n";

	std::string input;

	std::cout << "File mask (can look like \"*.txt\", \"file_number_*.txt\", \"any_extension.*\" or can be left empty):\n ";
	std::cin >> input;
	std::cout << "\n";
	processor.set_mask(input);

	std::cout << "Should Encoder delete input file? (Y / N):\n ";
	std::cin >> input;
	std::cout << "\n";

	if(input == "Y" || input == "y")
		processor.set_clear_input(true);
	else if(input == "N" || input == "n")
		processor.set_clear_input(false);
	else
	{
		std::cout << "Error: unexpected input!\n";
		return 1;
	}

	std::cout << "Direction, in which output files will be stored:\n ";
	std::cin >> input;
	std::cout << "\n";
	processor.set_output_directory(input);

	std::cout << "Can Encoder rewrite existing files? If no, Encoder will try to enumerate output files like 1_file.txt, 2_file.txt, etc. (Y / N):\n ";
	std::cin >> input;
	std::cout << "\n";

	if(input == "Y" || input == "y")
		processor.set_rewrite_permission(true);
	else if(input == "N" || input == "n")
		processor.set_rewrite_permission(false);
	else
	{
		std::cout << "Error: unexpected input!\n";
		return 1;
	}

	std::cout << "Enter encryption key (max length is 8, can contain any symbols, for example \"aPb{1|/\\\"):\n ";
	std::cin >> input;
	std::cout << "\n";

	if(input.size() > 8)
	{
		std::cout << "Error: unexpected input!\n";
		return 1;
	}

	processor.set_code(input);

	std::cout << "Should Encryptor run until told otherwise? (Y / N):\n ";
	std::cin >> input;
	std::cout << "\n";

	if(input == "Y" || input == "y")
	{
		std::cout << "Enter frequency (how often Encryptor will attempt to process files) in milliseconds:\n ";
		std::cin >> input;
		std::cout << "\n";

		int frequency = std::stoi(input);
		if(frequency < 1)
		{
			std::cout << "Error: unexpected input!\n";
			return 1;
		}

		processor.set_delay_in_milliseconds(frequency);

		processor.start();
	}
	else if(input == "N" || input == "n")
	{
		processor.process_once();
		std::cout << "Simple Encoder completed it's work. Thank You for using LEti products!\n\n";	//	LEti products, lol
		return 0;
	}
	else
	{
		std::cout << "Error: unexpected input!\n";
		return 1;
	}


	while(true)
	{
		std::cout << "Simple Encoder is running! You can still change this settings:\n"
					 "1. Input files' mask\n"
					 "2. Deletion of input files\n"
					 "3. Output files' path\n"
					 "4. Permission to rewrite existing files\n"
					 "5. Frequency\n"
					 "6. Encryption key\n"
					 "Or Enter '0' to stop Encoder\n\n"
					 "Your choise: ";

		int command_id = -1;
		std::cin >> command_id;
		std::cout << "\n";

		if(command_id == 0)
		{
			std::cout << "Please wait a little...\n\n";
			processor.stop();	//	this should wait until processor's thread is stopped
			break;
		}


		switch(command_id)
		{
		case(1):
		{
			std::cout << "File mask (can look like \"*.txt\", \"file_number_*.txt\", \"any_extension.*\" or can be left empty):\n ";
			std::cin >> input;
			std::cout << "\n";
			processor.set_mask(input);
			break;
		}

		case(2):
		{
			std::cout << "Should Encoder delete input file? (Y / N):\n ";
			std::cin >> input;
			std::cout << "\n";
			if(input == "Y" || input == "y")
				processor.set_clear_input(true);
			else if(input == "N" || input == "n")
				processor.set_clear_input(false);
			else
				std::cout << "Error: unexpected input! Operation aborted\n\n";
			break;
		}

		case(3):
		{
			std::cout << "Direction, in which output files will be stored:\n ";
			std::cin >> input;
			std::cout << "\n";
			processor.set_output_directory(input);
			break;
		}

		case(4):
		{
			std::cout << "Can Encoder rewrite existing files? If no, Encoder will try to enumerate output files like 1_file.txt, 2_file.txt, etc. (Y / N):\n ";
			std::cin >> input;
			std::cout << "\n";
			if(input == "Y" || input == "y")
				processor.set_rewrite_permission(true);
			else if(input == "N" || input == "n")
				processor.set_rewrite_permission(false);
			else
				std::cout << "Error: unexpected input! Operation aborted\n\n";
			break;
		}

		case(5):
		{
			std::cout << "Enter frequency (how often Encryptor will attempt to process files) in milliseconds:\n ";
			std::cin >> input;
			std::cout << "\n";
			int frequency = std::stoi(input);
			if(frequency < 1)
				std::cout << "Error: unexpected input! Operation aborted\n\n";
			else
				processor.set_delay_in_milliseconds(frequency);
			break;
		}

		case(6):
		{
			std::cout << "Enter encryption key (max length is 8, can contain any symbols, for example \"aPb{1|/\\\"):\n ";
			std::cin >> input;
			std::cout << "\n";
			if(input.size() > 8)
				std::cout << "Error: unexpected input! Operation aborted\n\n";
			else
				processor.set_code(input);
			break;
		}

		default:
		{
			std::cout << "Error: specified command does not exist!\n\n";
			break;
		}
		}
	}

	std::cout << "Simple Encoder is stopped. Thank You for using LEti products!\n\n";

	return 0;
}
