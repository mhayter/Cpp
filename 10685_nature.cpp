#include <bits/stdc++.h>
using namespace std;
//c input didn't make difference
//now #1 0.010s ignore first animal input
//0.150 -> 0.030s 3rd sync

#define MAXN 100010

#define NO_RANK

struct UnionFind {
  int pset[MAXN];
#ifdef NO_RANK
  int rank[MAXN];
#endif
  int total[MAXN];

  void init(int n) { 
    for(int i = 0; i < n; i++) {
      pset[i] = i;
#ifdef NO_RANK
      rank[i] = 0;
#endif 
      total[i] = 1;
    }
  }
  int get(int i) { return (pset[i] == i) ? i : (pset[i] = get(pset[i])); }
  int join(int i, int j) {
    int xRoot = get(i);
    int yRoot = get(j);
    if (xRoot == yRoot) return total[xRoot];
    if (total[xRoot] > total[yRoot]) {
    	pset[yRoot] = xRoot;
    	return total[xRoot] += total[yRoot];
    } else {
    	pset[xRoot] = yRoot;
    	return total[yRoot] += total[xRoot];
    }
#ifdef NO_RANK
    if (rank[xRoot] < rank[yRoot])
      pset[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
      pset[yRoot] = xRoot;
    else {
      pset[yRoot] = xRoot;
      rank[xRoot] = rank[xRoot] + 1;
    }
#endif
    //int sum = total[xRoot] + total[yRoot];
    //total[xRoot] = total[yRoot] = sum;
  }
  bool sameSet(int i, int j) { return get(i) == get(j); }
};

int high=0;
unordered_map<string,int>myMap;
int getIndex(const string &s) {
  auto it = myMap.find(s);
  if (it == myMap.end())
    return myMap[s]=high++;
  else {
    return it->second;
  }
}



const int MAX_STRINGS_IN_FILE = 200000; // by experiment
const int MAX_STRING_LENGTH = 35;
char buff[MAX_STRING_LENGTH*MAX_STRINGS_IN_FILE];

char A[MAX_STRINGS_IN_FILE][MAX_STRING_LENGTH+1];

int arrayIndex;
void readAll() {
  int r = fread(buff, 1, sizeof(buff), stdin);
  assert (r <= sizeof(buff));
  arrayIndex  = 0;
  for(int i=0;i<r;++i) {
    int len = 0;
    while (buff[i] >= '0') {
      A[arrayIndex][len++] = buff[i++];
    }
    //#ifdef _WIN32
    if (len)
    //#endif
        ++arrayIndex;
  }
  arrayIndex = 0;
}

int getIndex() {
  auto it = myMap.find(A[arrayIndex]);
  if (it == myMap.end())
    return myMap[A[arrayIndex++]]=high++;
  else {
    arrayIndex++;
    return it->second;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int nAnimals, nRelations;
  string s;
  //for(int i=0;i<100000;i++) cin >>s;
  //if (cin.eof()) throw -1;
  readAll();
  UnionFind uf;
  while (true) {
    sscanf(A[arrayIndex++],"%d",&nAnimals);
    sscanf(A[arrayIndex++],"%d",&nRelations);
    //cerr << nAnimals << " " << nRelations << endl;
    if (nAnimals == 0 && nRelations == 0) break;
    uf.init(nAnimals);
    high = 0;
    myMap.clear();
    arrayIndex+=nAnimals;//?
    /*
    for(int i=0;i<nAnimals;i++) {
      string animal; cin >> animal;
      //getIndex(animal);
    }
    */
    int maxGroup = 0;
    for(int i=0;i<nRelations;i++) {
      /*
      string animal1, animal2; cin >> animal1 >> animal2;
      int index1 = getIndex(animal1);
      int index2 = getIndex(animal2);
      */

      int index1 = getIndex();
      int index2 = getIndex();

      maxGroup = max(maxGroup,uf.join(index1,index2));
    }
    cout << max(1,maxGroup) << "\n";
  }
  return 0;
}