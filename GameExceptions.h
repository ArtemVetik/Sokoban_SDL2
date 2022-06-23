#ifndef GAMEEXCEPTIONS_H_INCLUDED
#define GAMEEXCEPTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <exception> // для std::exception

class MapLoadException: public std::exception
{
private:
	std::string m_error;

public:
	MapLoadException(std::string error)
		: m_error(error)
	{
	}

	// Возвращаем std::string в качестве константной строки C-style
    // const char* what() const { return m_error.c_str(); } // до C++11
	const char* what() const noexcept { return m_error.c_str(); } // C++11 и позднее
};


class UILoadException: public std::exception
{
private:
	std::string m_error;

public:
	UILoadException(std::string error)
		: m_error(error)
	{
	}

	// Возвращаем std::string в качестве константной строки C-style
    // const char* what() const { return m_error.c_str(); } // до C++11
	const char* what() const noexcept { return m_error.c_str(); } // C++11 и позднее
};

#endif // GAMEEXCEPTIONS_H_INCLUDED
