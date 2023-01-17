#ifndef FILE_MASK_H
#define FILE_MASK_H

#include <string>
#include <list>


class File_Mask
{
private:
	std::string m_raw_pattern;
	std::list<std::string> m_necessary_parts;
	bool m_any_start = false;
	bool m_any_end = false;

private:
	void M_process_pattern(const std::string& _raw_pattern);

private:
	unsigned int M_substr_offset(const std::string& _raw, unsigned int _offset, const std::string& _substr) const;

public:
	File_Mask(const std::string& _raw_pattern);
	void operator=(const std::string& _raw_pattern);

public:
	bool compare(const std::string& _filename);

};

#endif // FILE_MASK_H
