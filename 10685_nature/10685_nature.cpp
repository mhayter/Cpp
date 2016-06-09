#include <bits/stdc++.h>
using namespace std;
//used super input and hashtable hack (linear probing + no bounds check)
//still same runtime :'( 0.010s

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

namespace HashTable {

  struct Node {
    int count;
    int value;
    int newIndex;
  };
  const int MOST_UNIQUE_HASHES = 5010;
  unsigned clearHashes[MOST_UNIQUE_HASHES];
  int clearHashesPlace = 0;
  const int MOD = 800011;
  const int HASH_TABLE_SIZE = 1000003;//50021;//20011;//64000031;//48000013;//;//16000057
  Node hashTable[HASH_TABLE_SIZE];

  int insert() {
    int hashIndex = 0;
    for (int i = 0; A[arrayIndex][i]; i++) {
      hashIndex = hashIndex*31 + A[arrayIndex][i];
      if (hashIndex >= MOD) hashIndex %= MOD;
    }

    //do linear probing
    if (hashTable[hashIndex].count == 0) {
      hashTable[hashIndex].value = arrayIndex;
      clearHashes[clearHashesPlace++] = hashIndex;
      hashTable[hashIndex].count = 1;
      return hashTable[hashIndex].newIndex = high++;
    } else {
      if (strcmp(A[hashTable[hashIndex].value], A[arrayIndex])==0) {
        return hashTable[hashIndex].newIndex;
      } else {
        //while a value exists and it's not the current one, advance
        hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
        while (hashTable[hashIndex].count) {
          if (strcmp(A[hashTable[hashIndex].value], A[arrayIndex])==0) {
            return hashTable[hashIndex].newIndex;
          }
          ++hashIndex;// = (hashIndex + 1) % HASH_TABLE_SIZE;
        }
        
        hashTable[hashIndex].value = arrayIndex;
        clearHashes[clearHashesPlace++] = hashIndex;
        hashTable[hashIndex].count = 1;
        return hashTable[hashIndex].newIndex = high++;
      }
    }
  } 
  

  void clear () {
    for(int i=0;i<clearHashesPlace;i++) {
      hashTable[clearHashes[i]].count = 0;
    }
    clearHashesPlace = 0;
  }
};


class FastOutput {
public:
FastOutput() {
  m_dataOffset = 0;
}
~FastOutput() {
  flush();
}
void flush() {
  if (m_dataOffset) {
    if (fwrite(m_data,1, m_dataOffset,stdout));
    m_dataOffset = 0;
  }
}

void printUnsigned(uint32_t v, char d) {
  if (m_dataOffset + 11 > sizeof(m_data)) flush();
  if (v < 100000) {
    if (v < 1000) {
      if (v < 10) {
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 1;
      } else if (v < 100) {
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 2;
      } else {
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 3;
      }
    } else {
      if (v < 10000) {
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 4;
      } else {
        m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 5;
      }
    }
  } else {
    if (v < 100000000) {
      if (v < 1000000) {
        m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 6;
      } else if (v < 10000000) {
        m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 7;
      } else {
        m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 8;
      }
    } else {
      if (v < 1000000000) {
        m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 9;
      } else {
        m_data[m_dataOffset + 9] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
        m_data[m_dataOffset + 0] = v + 48;
        m_dataOffset += 10;
      }
    }
  }
  m_data[m_dataOffset++] = d;
}
void printChar(char d) {
if (m_dataOffset + 1 > sizeof(m_data)) flush();
  m_data[m_dataOffset++] = d;
}
void replaceChar(int offset, char d) {
  m_data[m_dataOffset + offset] = d;
}

void printStr(const char *str) {
  if (strlen(str) + m_dataOffset > sizeof(m_data)) flush();
  while (m_data[m_dataOffset++] = *str++);
}
public:
  uint8_t m_data[32768];
  size_t m_dataOffset;
}; 
FastOutput output;
int main() {
  ios_base::sync_with_stdio(false);
  int nAnimals, nRelations;
  readAll();
  UnionFind uf;
  while (true) {
    sscanf(A[arrayIndex++],"%d",&nAnimals);
    sscanf(A[arrayIndex++],"%d",&nRelations);
    if (nAnimals == 0 && nRelations == 0) break;
    uf.init(nAnimals);
    high = 0;
    HashTable::clear();
    arrayIndex+=nAnimals;//?
    int maxGroup = 0;
    for(int i=0;i<nRelations;i++) {
      int index1 = HashTable::insert();
      arrayIndex++;
      int index2 = HashTable::insert();
      arrayIndex++;

      maxGroup = max(maxGroup,uf.join(index1,index2));
    }
    output.printUnsigned(max(1,maxGroup),'\n');
  }
  return 0;
}