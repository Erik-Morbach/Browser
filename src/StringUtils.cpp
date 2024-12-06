#include "StringUtils.hpp"
#include <cctype>

namespace StringUtils {
	std::string trim(const std::string &s){
		if(s.size()==0) return s;
		int last = s.size()-1;
		int first = last;
		bool gotSomeChar = false;
		for(int i=0;i<s.size();i++){
			if(!std::isspace(s[i])){
				gotSomeChar = true;
				last = i;
				first = std::min(first, i);
			}
		}
		if(!gotSomeChar) return "";
		return s.substr(first, last-first+1);
	}
}
