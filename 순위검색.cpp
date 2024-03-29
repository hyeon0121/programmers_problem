// 정확성 성공, 효율성 실패
/*#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer(query.size(),0);
    string fs[4];
    //char ch[4];
    //vector<string> s(4);
    string is[4];
    string x;
    vector<pair<string,int>> q;
    string ad;
    string score;

    for (int i = 0; i < query.size(); ++i) {
    	stringstream f(query[i]);

    	f >> fs[0] >> ad >> fs[1] >> ad >> fs[2] >> ad >> fs[3] >> x;

    	for (int j = 0; j < info.size(); ++j) {
	    	stringstream ss(info[j]);

	    	ss >> is[0] >> is[1] >> is[2] >> is[3] >> score;
	    	//cout << cond[0] << cond[1] << cond[2] << cond[3] << endl;
	    	if (stoi(score) >= stoi(x)) {
	    		if (fs[0][0] != '-' && fs[0][0] != is[0][0]) continue;
	    		if (fs[1][0] != '-' && fs[1][0] != is[1][0]) continue;
	    		if (fs[2][0] != '-' && fs[2][0] != is[2][0]) continue;
	    		if (fs[3][0] != '-' && fs[3][0] != is[3][0]) continue;

	    		answer[i]++;
	    	}
	    		
	    }
    	

    }
    return answer;
}*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> db[3][2][2][2];

// query 문자열 쪼개기 함수
vector<string> querySplit(string s){
  vector<string> ret;
  string temp;
  for(char c:s){
    if(c==' '){
      ret.push_back(temp);
      temp="";
    }
    else temp+=c;
  }
  ret.push_back(temp);
  return ret;
}

// info 문자열 쪼개기 함수
vector<int> infoSplit(string s){
  vector<int> ret;
  string temp;
  int n;
  for(char c:s){
    if(c==' '){
      if(temp=="cpp" || temp=="backend" || temp=="junior" || temp=="chicken") n=0;
      else if(temp=="python") n=2;
      else n=1;
      ret.push_back(n);
      temp="";
    }
    else temp+=c;
  }
  ret.push_back(stoi(temp));
  return ret;
}

vector<int> solution(vector<string> info, vector<string> query) {
   vector<int> answer;

  // info 저장
  for(string s: info){
    vector<int> v = infoSplit(s);
    db[v[0]][v[1]][v[2]][v[3]].push_back(v[4]);
  }

  // 추후 이분 탐색을 위한 모든 배열 정렬
  for(int i=0; i<3; i++)
    for(int j=0; j<2; j++)
      for(int k=0; k<2; k++)
        for(int l=0; l<2; l++)
          sort(db[i][j][k][l].begin(),db[i][j][k][l].end());

  // 쿼리 수행
  for(string s: query){
    vector<string> v = querySplit(s);

    // 쿼리 조건에 따른 구간 정의
    int ai,bi,aj,bj,ak,bk,al,bl;

    if(v[0]=="cpp") ai=bi=0;
    else if(v[0]=="java") ai=bi=1;
    else if(v[0]=="python") ai=bi=2;
    else {ai=0; bi=2;} // '-'

    if(v[2]=="backend") aj=bj=0;
    else if(v[2]=="frontend") aj=bj=1;
    else {aj=0; bj=1;}; // '-'

    if(v[4]=="junior") ak=bk=0;
    else if(v[4]=="senior") ak=bk=1;
    else {ak=0; bk=1;} // '-'

    if(v[6]=="chicken") al=bl=0;
    else if(v[6]=="pizza") al=bl=1;
    else {al=0; bl=1;} // '-'

    int score = stoi(v[7]);

    // 점수가 X점 이상인 사람의 수 계산
    int ans=0;
    for(int i=ai; i<=bi; i++){
      for(int j=aj; j<=bj; j++){
        for(int k=ak; k<=bk; k++){
          for(int l=al; l<=bl; l++){
            int n = db[i][j][k][l].size();
            if(n==0) continue;

            // 이분 탐색
            auto iter = lower_bound(db[i][j][k][l].begin(),db[i][j][k][l].end(),score);

            if(iter == db[i][j][k][l].end()) continue;
            ans += n-(iter-db[i][j][k][l].begin());
          }
        }
      }
    }
    answer.push_back(ans);
  }

  return answer;
}