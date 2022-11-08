#include "Utilities.h"
#include <algorithm>

namespace squampernaut
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		// convert string characters to lower case 

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		// convert string characters to upper case 

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		// if string lengths don't match return false 
		if (str1.length() != str2.length()) { return false; }
		// returns false if string characters aren't equal 

		return true;
	}
	
}