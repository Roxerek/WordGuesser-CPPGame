#include "VectorUtil.h"

void VectorUtil::putIfAbsent(std::vector<char>* vec, char c) {

	if (std::find(vec->begin(), vec->end(), c) == vec->end()) {
		vec->push_back(c);
	}
}

std::string VectorUtil::valuesToCommaString(std::vector<char> vec) {
	std::string content = std::string(1, vec[0]);
	for (unsigned int i = 1; i < vec.size(); i++) {
		content = content + ", " + vec[i];
	}
	return content;
}