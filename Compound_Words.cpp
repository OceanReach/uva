#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef std::vector<std::string> vS;
typedef unsigned int UI;
typedef std::vector<int> vI;
typedef std::map<std::string, UI> mSUI;
const int MAX = 193939;


//×Üµ¥´ÊÊý²»»á³¬¹ý120000

UI BKDRHash(std::string);

UI Hadd(std::string, vS &);
UI Hfind(std::string, vS &);

std::ostream &operator << (std::ostream &, vS &);
std::ostream &operator << (std::ostream &, vI &);



int main() {
	std::string x;
	vS dict(MAX);
	mSUI b;

	while (std::cin >> x) {
		UI pos = Hadd(x, dict);

		for (std::string::iterator bn = x.begin(), ed = x.end(), bn1 = bn+1;
			bn1+1 != ed;
			++bn1) {
			std::string str1(bn, bn1+1), str2(bn1+1, ed);
			if (UI p = Hfind(str1, dict) != MAX) {
				b.insert(std::pair<std::string, UI>(str2, pos));
				break;
			}
		}
	}

	for (mSUI::iterator bn = b.begin();
		bn != b.end();
		++bn) {
		std::string s = bn->first;
		UI pos = bn->second;
		if (Hfind(s,dict) != MAX){
			std::cout << dict[pos] << std::endl;
		}
	}

	return 0;
}

UI Hadd(std::string s, vS &H) {
	UI pos = BKDRHash(s) % MAX;

	for (int i = 1, sum = 0;!H[pos].empty(); i += 2) {
		pos += sum + i;
		pos %= MAX;
	}
	H[pos] = s;
	return pos;
}

UI Hfind(std::string s, vS &H) {
	UI pos = BKDRHash(s) % MAX;
	for (int i = 1, sum = 0;
		H[pos] != s && !H[pos].empty();
		i += 2) {
		pos += (sum + i);
		pos %= MAX;
	}
	if (H[pos] == s)
		return pos;
	else
		return MAX;
}

UI BKDRHash(std::string s) {
	UI seed = 31;
	UI result = 0;

	for (std::string::iterator c = s.begin();
		c != s.end();
		++c) {
		result = result * seed + *c;
	}

	return (result & 0x7fffffff);
}

std::ostream & operator << (std::ostream & os, vS &tg) {
	for (vS::iterator bn = tg.begin();
		bn != tg.end();
		++bn) {
		if (bn->empty())
			continue;
		else
			os << *bn << " ";
	}

	return os;
}

std::ostream & operator << (std::ostream & os, vI &tg) {
	for (vI::iterator bn = tg.begin();
		bn != tg.end();
		++bn) {
		os << *bn << " ";
	}

	return os;
}
