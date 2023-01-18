#include "Data_Encryptor.h"


Data_Encryptor::Data_Encryptor()
{

}

Data_Encryptor::~Data_Encryptor()
{

}



std::string Data_Encryptor::encode(const std::string &_data, uli_t _code)
{
	if(_data.size() == 0)
		return std::string();

	std::string encrypted_data;

	encrypted_data.resize(_data.size());

	unsigned int fullsize = _data.size() / sizeof(uli_t);
	const uli_t* raw_data_uli = (const uli_t*)_data.c_str();

	char* raw_encrypted_cstr = new char[fullsize * sizeof(uli_t)];
	uli_t* raw_enctypted_uli = (uli_t*)raw_encrypted_cstr;

	for(unsigned int i=0; i<fullsize; ++i)
		raw_enctypted_uli[i] = raw_data_uli[i] ^ _code;

	for(unsigned int i=0; i<fullsize * sizeof(uli_t); ++i)
		encrypted_data[i] = raw_encrypted_cstr[i];

	delete[] raw_encrypted_cstr;

	unsigned int leftover_size = _data.size() % sizeof(uli_t);

	if(leftover_size == 0)
		return encrypted_data;

	raw_encrypted_cstr = new char[sizeof(uli_t)];
	raw_enctypted_uli = (uli_t*)raw_encrypted_cstr;

	for(unsigned int i=0; i<leftover_size; ++i)
		raw_encrypted_cstr[i] = _data[(fullsize * sizeof(uli_t)) + i];
	for(unsigned int i=leftover_size; i < sizeof(uli_t); ++i)
		raw_encrypted_cstr[i] = 0;

	*raw_enctypted_uli = *raw_enctypted_uli ^ _code;

	for(unsigned int i=0; i<leftover_size; ++i)
		encrypted_data[(fullsize * sizeof(uli_t)) + i] = raw_encrypted_cstr[i];

	delete[] raw_encrypted_cstr;

	return encrypted_data;
}























































