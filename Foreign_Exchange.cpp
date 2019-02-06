#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef std::set<int> stI;
typedef std::map<int, stI> mIStI;
typedef std::vector<bool> vB;
typedef std::vector<int> vI;

bool check(const mIStI &);
void bfs(int, int, mIStI &, vB &, vI &);

int main() {
	string l;
	mIStI G;
	while (std::getline(std::cin, l)) {
		std::istringstream sl(l);
		int a, b;
		sl >> a >> b;
		mIStI::iterator t = G.find(a);
		if (t != G.end()) {
			t->second.insert(b);
		}
		else {
			stI ns;
			ns.insert(b);
			G.insert(std::pair<int, stI>(a, ns));
		}
	}
	if (check(G)) {
		std::cout << "YES" << std::endl;
	}
	else
		std::cout << "NO" << std::endl;
}

bool check(const mIStI &TG) {
	vB visted(TG.size());
	vI result(TG.size());
    
	//初始化visted为全false
	for (vB::iterator bn = visted.begin();
		bn != visted.end();
		++bn) {
		*bn = false;
	}

	for (mIStI::iterator bn = TG.begin();
		bn != TG.end();
		++bn) {
		int v = bn->first;
		stI &ws = bn->second;
		for (stI::iterator bn1 = ws.begin();
			bn1 != ws.end();
			++bn1) {
			visted[v] = true;
			bfs(v, *bn1, TG, visted, result);
		}
	}

	bool flag = true;
	for (vI::iterator bn = result.begin();
		bn != result.end();
		++bn) {
		if (*bn == 0) {
			flag = false;
			break;
		}
	}
	return flag
}

void bfs(int v, int w, mIStI &TG, vB &vs, vI &r) {
	mIStI::iterator ivws1 = TG.find(w);
	if (vs[w])
		return;
	stI &ws1 = ivws1->second;
	for (stI::iterator bn = ws1.begin();
		bn != ws1.end();
		++bn) {
		if (*bn == v) {
			r[v]++;
			r[w]++;
			break;
		}
	}
}





