#pragma once
#include <string>
#include <vector>

template<typename T>
T strip(std::string& str)
{
	auto ib = str.cbegin();
	for (; (*ib) == ' '; ++ib) {}
	auto ie = str.cend() - 1;
	for (; (*ie) == ' '; --ie) {}

	return T{ib, ie + 1};	

}
template<typename T>
T strip(std::string& str, char chr)
{
	auto ib = str.cbegin();
	for (; (*ib) == chr; ++ib) {}
	auto ie = str.cend() - 1;
	for (; (*ie) == chr; --ie) {}

	return T{ib, ie + 1};	
}

template<template<typename> typename T>
T<std::string> ssplit(std::string& str, char chr)
{
	T<std::string> vstr;

	using size_t = std::string::size_type;
	std::vector<size_t> vt;
	for (size_t i = 0; i != str.size(); ++i) {
		if (str[i] != chr)
			vt.emplace_back(i);
	}
	
	int indx = 0;
	int lgth = 0;
	int startp = 0;
	size_t mnt = vt[indx];
	while (indx != vt.size()) {
		if (mnt == vt[indx]) {
			mnt += 1;
			lgth += 1;
			indx += 1;
		}
		else {
			vstr.emplace_back(str.substr(vt[startp], lgth));
			lgth = 0;
			startp = indx;
			mnt = vt[indx];
		}
	}
	vstr.emplace_back(str.substr(vt[startp], lgth));

	return vstr;
}

