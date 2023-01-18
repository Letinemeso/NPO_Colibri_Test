#include "File_Encryptor.h"


File_Encryptor::File_Encryptor()
{

}

File_Encryptor::~File_Encryptor()
{

}



void File_Encryptor::M_encrypt()
{
	m_encrypted_data.clear();
	if(m_decrypted_data.size() == 0)
		return;

	m_encrypted_data.resize(m_decrypted_data.size());

	unsigned int fullsize = m_decrypted_data.size() / sizeof(uli_t);
	const uli_t* raw_data_uli = (const uli_t*)m_decrypted_data.c_str();

	char* raw_encrypted_cstr = new char[fullsize * sizeof(uli_t)];
	uli_t* raw_enctypted_uli = (uli_t*)raw_encrypted_cstr;

	for(unsigned int i=0; i<fullsize; ++i)
		raw_enctypted_uli[i] = raw_data_uli[i] ^ m_code;

	for(unsigned int i=0; i<fullsize * sizeof(uli_t); ++i)
		m_encrypted_data[i] = raw_encrypted_cstr[i];

	delete[] raw_encrypted_cstr;

	unsigned int leftover_size = m_decrypted_data.size() % sizeof(uli_t);

	if(leftover_size == 0)
		return;

	raw_encrypted_cstr = new char[sizeof(uli_t)];
	raw_enctypted_uli = (uli_t*)raw_encrypted_cstr;

	for(unsigned int i=0; i<leftover_size; ++i)
		raw_encrypted_cstr[i] = m_decrypted_data[(fullsize * sizeof(uli_t)) + i];
	for(unsigned int i=leftover_size; i < sizeof(uli_t); ++i)
		raw_encrypted_cstr[i] = 0;

	*raw_enctypted_uli = *raw_enctypted_uli ^ m_code;

	for(unsigned int i=0; i<leftover_size; ++i)
		m_encrypted_data[(fullsize * sizeof(uli_t)) + i] = raw_encrypted_cstr[i];

	delete[] raw_encrypted_cstr;
}

void File_Encryptor::M_save_data(const std::string &_path, const std::string &_name, const std::string &_data) const
{
	std::string full_path = M_availible_full_path(_path, _name);

	if(full_path.size() == 0)
		return;

	std::ofstream file(full_path, std::ofstream::binary);

	file << _data;
	file.close();
}

std::string File_Encryptor::M_availible_full_path(const std::string &_path, const std::string &_name) const
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



void File_Encryptor::load_file(const std::string &_path, const std::string &_name)
{
	m_encrypted_data.clear();
	m_decrypted_data.clear();

	std::ifstream file(_path + _name, std::ifstream::binary);
	if(!file.is_open())
		return;

	file.seekg(0, std::ifstream::end);
	unsigned int size = file.tellg();
	file.seekg(0, std::ifstream::beg);

	m_decrypted_data.resize(size);
	for(unsigned int i=0; i<size; ++i)
		m_decrypted_data[i] = file.get();

	file.close();

	M_encrypt();
}

void File_Encryptor::save_file_raw(const std::string &_path, const std::string &_name)
{
	M_save_data(_path, _name, m_decrypted_data);
}

void File_Encryptor::save_file_enctypted(const std::string &_path, const std::string &_name)
{
	M_save_data(_path, _name, m_encrypted_data);
}























































