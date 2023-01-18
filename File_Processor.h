#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <experimental/filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

namespace filesystem = std::experimental::filesystem;

#include "File_Mask.h"
#include "Data_Encryptor.h"


class File_Processor
{
private:
	Data_Encryptor m_encryptor;

	bool m_is_active = false;
	bool m_should_be_active = false;

	std::mutex m_mutex;

private:
	File_Mask m_mask;
	bool m_clear_input = false;
	std::string m_output_directory;
	bool m_rewrite_permission = false;
	unsigned int m_numered_file_copy_limit = 0xFFFF;	//	magic number :)
	unsigned int m_delay_ms = 1000;
	unsigned long int m_code = 0;

public:
	File_Processor();
	~File_Processor();

private:
	void M_save_data(const std::string& _path, const std::string& _name, const std::string& _data) const;
	std::string M_availible_full_path(const std::string& _path, const std::string& _name) const;
	std::string M_load_file(const std::string& _path, const std::string& _name);

private:
	void M_process();

public:
	void process_once();
	void start();
	void stop();

public:
	void set_mask(const std::string& _mask);
	void set_clear_input(bool _value);
	void set_output_directory(const std::string& _value);
	void set_rewrite_permission(bool _value);
	void set_numbered_file_copy_limit(unsigned int _value);
	void set_delay_in_milliseconds(unsigned int _value);
	void set_code(const std::string& _code);

};

#endif // FILE_PROCESSOR_H
