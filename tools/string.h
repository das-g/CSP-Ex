// from http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string/#comment-22

#ifndef TOOLS_STRING_H
#define TOOLS_STRING_H

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

#endif // TOOLS_STRING_H
