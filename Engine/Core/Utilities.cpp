#include "Utilities.h"
#include <algorithm> 

namespace neu
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		// convert string characters to lower case 
		for (auto& c : lower)
		{
			c = tolower(c);
		}

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		// convert string characters to upper case 
		for (auto& c : upper)
		{
			c = toupper(c);
		}

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		// if string lengths don't match return false
		// returns false if string characters aren't equal 
		if (str1.size() == str2.size())
		{
			if (std::equal(str1.begin(), str1.end(), str2.begin(), [](char& c1, char& c2) {return (c1 == c2 || std::toupper(c1) == std::toupper(c2));})) 
			{
				return true;
			}
		}

		return false; 
	}
}