#pragma once

class IdUtils{
public:
	static int getUniqueId(){
		static int counter = 1;
		return counter++;
	}
};
