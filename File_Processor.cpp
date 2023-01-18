#include "File_Processor.h"


File_Processor::File_Processor()
{

}

File_Processor::~File_Processor()
{

}



void File_Processor::M_save_data(const std::string &_path, const std::string &_name, const std::string &_data) const
{
	std::string full_path = M_availible_full_path(_path, _name);

	if(full_path.size() == 0)
		return;

	std::ofstream file(full_path, std::ofstream::binary);

	file << _data;
	file.close();
}

std::string File_Processor::M_availible_full_path(const std::string &_path, const std::string &_name) const
{
	filesystem::create_directory(_path);

	std::ifstream test;

	test.open(_path + _name, std::ifstream::binary);
	if(test.is_open())
	{
		test.close();
		if(m_rewrite_permission == true)
			return _path + _name;
	}
	else
	{
		return _path + _name;
	}

	for(unsigned int i=0; i<m_numered_file_copy_limit; ++i)
	{
		std::string path = _path + std::to_string(i) + '_' + _name;

		test.open(path, std::ifstream::binary);

		if(!test.is_open())
			return path;

		test.close();
	}

	return std::string();
}

std::string File_Processor::M_load_file(const std::string &_path, const std::string &_name)
{
	std::string result;

	std::ifstream file(_path + _name, std::ifstream::binary);
	if(!file.is_open())
		return result;

	file.seekg(0, std::ifstream::end);
	unsigned int size = file.tellg();
	file.seekg(0, std::ifstream::beg);

	result.resize(size);
	for(unsigned int i=0; i<size; ++i)
		result[i] = file.get();

	file.close();

	return result;
}



void File_Processor::M_process()
{
	filesystem::directory_iterator it("./");
	it = filesystem::begin(it);

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

		if(!m_mask.compare(/*path + */filename))
			continue;

		std::string content = M_load_file(path, filename);

		if(m_clear_input)
			std::remove(it->path().string().c_str());

		std::string encrypted = m_encryptor.encode(content, m_code);

		M_save_data(path + m_output_directory, filename, encrypted);

		continue;
	}
}



void File_Processor::process_once()
{
	M_process();
}

#include <iostream>

void File_Processor::start()
{
	if(m_is_active)
		return;

	m_should_be_active = true;

	std::thread th([this]()
	{
		m_is_active = true;

		while(m_should_be_active)
		{
			m_mutex.lock();

			M_process();

			m_mutex.unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(m_delay_ms));
		}

		m_is_active = false;
	});

	th.detach();
}

void File_Processor::stop()
{
	m_mutex.lock();
	m_should_be_active = false;
	m_mutex.unlock();

	while(m_is_active)
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}



void File_Processor::set_mask(const std::string &_mask)
{
	m_mutex.lock();
	m_mask = _mask;
	m_mutex.unlock();
}

void File_Processor::set_clear_input(bool _value)
{
	m_mutex.lock();
	m_clear_input = _value;
	m_mutex.unlock();
}

void File_Processor::set_output_directory(const std::string& _value)
{
	m_mutex.lock();
	m_output_directory = _value + '/';
	m_mutex.unlock();
}

void File_Processor::set_rewrite_permission(bool _value)
{
	m_mutex.lock();
	m_rewrite_permission = _value;
	m_mutex.unlock();
}

void File_Processor::set_numbered_file_copy_limit(unsigned int _value)
{
	m_mutex.lock();
	m_numered_file_copy_limit = _value;
	m_mutex.unlock();
}

void File_Processor::set_delay_in_milliseconds(unsigned int _value)
{
	m_mutex.lock();
	m_delay_ms = _value;
	m_mutex.unlock();
}

void File_Processor::set_code(const std::string &_code)
{
	m_mutex.lock();
	if(_code.size() > 8)
		return;

	std::string code = _code;
	if(_code.size() < 8)
	{
		for(unsigned int i=_code.size(); i < 8; ++i)
			code += (unsigned char)(-1);
	}

	m_code = *((unsigned long int*)code.c_str());
	m_mutex.unlock();
}




















































