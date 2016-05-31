#include <bits/stdc++.h>
using namespace std;

const int SIZE = 5;
int a[SIZE];
int sumToEnd[SIZE];

char parent[SIZE];

const int TARGET = 23;
const int NTESTS = 25;
const int RANGE_CONSTANT = 250;

bool found;
int memoPlace;
int testNum;

class FastInput {
public:
FastInput() {
	m_dataOffset = 0;
	m_dataSize = 0;
	m_v = 0x80000000;
}
uint32_t readNextUnsigned() {
	if (m_dataOffset == m_dataSize) {
		int r = fread(m_buffer,1,sizeof(m_buffer),stdin);
		if (r <= 0) return m_v;
		m_dataOffset = 0;
		m_dataSize = 0;
		int i = 0;
		if (m_buffer[0] < '0') {
			if (m_v != 0x80000000) {
				m_data[m_dataSize++] = m_v;
				m_v = 0x80000000;
			}
			for (; (i < r) && (m_buffer[i] < '0'); ++i);
		}
		for (; i < r;) {
			if (m_buffer[i] >= '0') {
				m_v = m_v * 10 + m_buffer[i] - 48;
				++i;
			} else {
				m_data[m_dataSize++] = m_v;
				m_v = 0x80000000;
				for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
			}
		}
	}
	return m_data[m_dataOffset++];
}
public:
	uint8_t m_buffer[32768];
	uint32_t m_data[16384];
	size_t m_dataOffset, m_dataSize;
	uint32_t m_v;
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
	//if (strlen(str) + m_dataOffset > sizeof(m_data)) flush();
	while (m_data[m_dataOffset++] = *str++);
}
public:
	uint8_t m_data[32768];
	size_t m_dataOffset;
}; 

int permsPlace;
int perms[120][5];

int toPermute[SIZE] = {0,1,2,3,4};

void create23(int depth, int tot) {
	
	//cerr << depth << " " << tot << endl;
	if (depth + 1 == SIZE) {
		if (tot + a[depth] == TARGET) {
			found = true; return;
		}
		if (tot - a[depth] == TARGET) {
			found = true; return;
		}
		if (tot*a[depth] == TARGET) {
			found = true; return;
		}
		return;
	}
	//if (tot > 50*(5-depth) + TARGET ) return;
	//if (tot+50*(5-depth) < TARGET ) return;
	int num = 50*(5-(depth+1));
	if (tot+a[depth] <= num +TARGET) 
		create23(depth+1, tot+a[depth]); 
	if (found) return;

	if (tot-a[depth]+ num >= TARGET )
		create23(depth+1, tot-a[depth]);
	if (found) return;

	if (tot*a[depth] <= num +TARGET && tot*a[depth]+num >= TARGET)
		create23(depth+1, tot*a[depth]);
	if (found) return;
}

//0.040s (tie with recursive)
int sta[100];
int staPlace;

void create23Stack(int depth, int tot) {
	staPlace = 0;
	sta[staPlace++] = depth;
	sta[staPlace++] = tot;
	while (staPlace) {
		int tot = sta[--staPlace];
		int depth = sta[--staPlace];

		if (depth + 1 == SIZE) {
			if (tot + a[depth] == TARGET) {
				found = true; return;
			}
			if (tot - a[depth] == TARGET) {
				found = true; return;
			}
			if (tot*a[depth] == TARGET) {
				found = true; return;
			}
			//return;
		} else {
			if (tot > 50*(5-depth) + TARGET ) continue;
			if (tot+50*(5-depth) < TARGET ) continue;

			sta[staPlace++] = depth+1;
			sta[staPlace++] = tot * a[depth];

			sta[staPlace++] = depth+1;
			sta[staPlace++] = tot - a[depth];

			sta[staPlace++] = depth+1;
			sta[staPlace++] = tot + a[depth];
		}



	}
}

bool visited[SIZE];

void create23New(int depth, int tot) {
	
	//cerr << depth << " " << tot << endl;
	if (depth == SIZE) {
		if (tot == TARGET) found = true;
		return;
	}
	if (tot > 50*(5-depth) + TARGET ) return;
	if (tot+50*(5-depth) < TARGET ) return;
	for(int i = 0;i<SIZE;i++) {
		if (!visited[i]) {
			visited[i] = true;
			create23New(depth+1, tot+a[i]);
			create23New(depth+1, tot-a[i]);
			create23New(depth+1, tot*a[i]);
			visited[i] = false;
			if (found) return;
		}
	}
}

int originalA[SIZE];

bool allZeros() {
	for(int i=0;i<SIZE;i++) {
		if (a[i] !=0) return false;
	}
	return true;
}

FastInput input;
FastOutput output;


int doIt(int num1, int num2, int selector) {
	switch (selector) {
		case 0:
			return num1+num2;
		case 1:
			return num1-num2;
		default:
			return num1*num2;
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	bool permute = true;
	permsPlace = 0;
	while (permute) {
		for(int i=0;i<SIZE;i++)
			perms[permsPlace][i] = toPermute[i];
		permute = next_permutation(toPermute, toPermute+SIZE);
		permsPlace++;
	}
	/*
	for(int i=0;i<SIZE;i++) {
		cerr << perms[0][i] << " ";
	}
	cerr << endl;
	for(int i=0;i<SIZE;i++) {
		cerr << perms[119][i] << " ";
	}
	cerr << endl;
	*/
	while (true) {
		//cerr << "new one " << endl;
		for(int i=0;i<SIZE;i++) {
			a[i] = input.readNextUnsigned();
			//if (a[i] < 0) throw -1;
		}


		//if all zeros
		if (allZeros()) break;
		found = false;
		/*
		for(int i=0;i<SIZE;i++) {
			visited[i] = true;
			create23New(1,a[i]);
			visited[i] = false;
		}
		*/
		/*
		for(permsPlace = 0;permsPlace<120 && !found;permsPlace++) {
			for(int i=0;i<SIZE;i++) a[i] = originalA[perms[permsPlace][i]];
			//cerr << "taking " << perms[permsPlace][0] << " a is " << a[perms[permsPlace][0]] << endl;
			create23(1,a[0]);
			//create23Stack(1,a[0]);
		}
		*/
		/*
		sort(a, a + SIZE);

		bool permute = true;
		while (permute &&  !found) {
			//cerr << "   start" << endl;
			create23(1,a[0]);
			permute = next_permutation(a,a+SIZE);
		}
		*/
		//memset(memo, 0, sizeof(memo));

		//completely interative
		sort(a, a+SIZE);
		do {
			for(int i=0;i<3;i++) {
				int v1 = doIt(a[0],a[1],i);
				if (v1 > 50*(5-2) + TARGET ) continue;
				if (v1+50*(5-2) < TARGET ) continue;

				for (int j=0;j<3;j++) {
					int v2 = doIt(v1,a[2],j);
					if (v2 > 50*(5-2) + TARGET ) continue;
					if (v2+50*(5-2) < TARGET ) continue;

					for(int k=0;k<3;k++) {
						int v3 = doIt(v2,a[3],k);
						//if (v3 > 50*(5-3) + TARGET ) continue;
						//if (v3+50*(5-3) < TARGET ) continue;

						if (v3 + a[4] == TARGET) {
							found = true;
							goto hell;
						} else if ( v3 - a[4] == TARGET) {
							found = true;
							goto hell;
						} else if (v3 * a[4] == TARGET) {
							found = true;
							goto hell;
						}
					}
				}
			}
		} while (next_permutation(a, a+SIZE));

		hell:;
		if (found) {
			cout << "Possible\n";
		} else {
			cout <<"Impossible\n";
		}

	}
	
	return 0;
}