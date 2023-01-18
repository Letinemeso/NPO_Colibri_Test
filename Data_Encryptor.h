#ifndef DATA_ENCRYPTOR_H
#define DATA_ENCRYPTOR_H

#include <string>

class Data_Encryptor
{
private:
	using uli_t = unsigned long int;

public:
	Data_Encryptor();
	~Data_Encryptor();

public:
	std::string encode(const std::string& _data, uli_t _code);
};

#endif // DATA_ENCRYPTOR_H
