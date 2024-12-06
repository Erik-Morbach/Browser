#pragma once

#include <sstream>
#include <string>
struct StyleContext{
	int fontSize;
	int marginTop;
	int marginRight;
	int marginLeft;
	int marginBottom;
	std::string str(){
		std::stringstream ss;
		ss << fontSize << "px "<<marginTop << " " << marginLeft << " "<< marginRight << " "<<marginBottom;
		return ss.str();
	}
};
