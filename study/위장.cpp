#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int cnt = 1;

    map<string, int> m;

    for (int i = 0; i < clothes.size(); i++) {
        m[clothes[i][1]] += 1;
    }

    for (auto i = m.begin(); i != m.end(); i++) {
        cnt *= (i->second) + 1;

    }
    
    // 아무것도 입지 않았을 경우를 고려해 -1
    return cnt-1;
}