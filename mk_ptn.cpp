#include <tuple>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::map<int, char> alphabet = { {0,'a'}, {1,'b'}, {2,'c'}, {3,'d'}, {4,'e'}, {5,'f'}, {6,'g'}, {7,'h'}, {8,'i'},
				 {9,'j'}, {10,'k'}, {11,'l'}, {12,'m'}, {13,'n'}, {14,'o'}, {15,'p'}, {16,'q'},
				 {17,'r'}, {18,'s'}, {19,'t'}, {20,'u'}, {21,'v'}, {22,'w'}, {23,'x'}, {24,'y'}, {25,'z'} };

std::vector<std::string> ssplit(std::string& str, char chr)
{
	std::vector<std::string> vstr;
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

int main(int argc, char* argv[])
{
	std::fstream inf(argv[1], std::ifstream::in);
	std::string buffer;
	
	while (std::getline(inf, buffer))
	{
		if (buffer.find(',') == std::string::npos)
			continue;

		auto pos = buffer.find_last_of(' ');
		std::string repz = buffer.substr(pos + 1);

		std::vector<std::string> dms = ssplit(repz, ';');
		std::vector<std::pair<int, char>> vpr;
		for (int j = 0; j != dms.size(); ++j) {
			if (dms[j].find(',') != std::string::npos) {
				auto sgmts = ssplit(dms[j], ',');
				for (int k = 0; k != sgmts.size(); ++k) {
					vpr.emplace_back(std::make_pair(std::stoi(ssplit(sgmts[k], '-')[0]),
									 alphabet[j]));
				}
			}
			else
				vpr.emplace_back(std::make_pair(std::stoi(ssplit(dms[j], '-')[0]), alphabet[j]));
		}
		
		std::sort(vpr.begin(), vpr.end(), [](std::pair<int, char>& lpr, 
						     std::pair<int, char>& rpr)
                                                    { return lpr.first < rpr.first; });

		for (auto& s : vpr)
			std::cout << s.second << "";
		std::cout << std::endl;	
	}
}

