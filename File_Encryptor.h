#ifndef FILE_ENCRYPTOR_H
#define FILE_ENCRYPTOR_H

#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace filesystem = std::experimental::filesystem;

class File_Encryptor
{
private:
	using uli_t = unsigned long int;

private:
	std::string m_decrypted_data;
	std::string m_encrypted_data;

	uli_t m_code = 0;

	bool m_rewrite_permission = false;
	unsigned int m_numered_file_copy_limit = 5;	//	magic number :)

public:
	File_Encryptor();
	~File_Encryptor();

private:
	void M_encrypt();
	void M_save_data(const std::string& _path, const std::string& _name, const std::string& _data) const;
	std::string M_availible_full_path(const std::string& _path, const std::string& _name) const;

public:
	void load_file(const std::string& _path, const std::string& _name);
	void save_file_raw(const std::string& _path, const std::string& _name);
	void save_file_enctypted(const std::string& _path, const std::string& _name);

	inline void set_code(unsigned long int _code) { m_code = _code; }
	inline void set_rewrite_permission(bool _permission) { m_rewrite_permission = _permission; }
	inline void set_numered_file_copy_limit(unsigned int _limit) { m_numered_file_copy_limit = _limit; }

};

#endif // FILE_ENCRYPTOR_H
