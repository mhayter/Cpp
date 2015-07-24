#include <cstdio>
#include <cstdint>
#include <cstring>
using namespace std;

//tied for #1 7/16/2015 0.002 varies upto 0.007

class FastInput {
public:
FastInput() {
	m_dataOffset = 0;
	m_dataSize = 0;
	m_v = 0x80000000;
}
uint32_t ReadNext() {
	if (m_dataOffset == m_dataSize) {
		r = fread(m_buffer,1,sizeof(m_buffer),stdin);
		if (r <= 0) return m_v;
		m_dataOffset = 0;
		m_dataSize = 0;
		i = 0;
		if (m_buffer[0] < '0') {
			if (m_v != 0x80000000) {
				m_data[m_dataSize++] = m_v;
				m_v = 0x80000000;
			}
			for (; (i < r) && (m_buffer[i] < '0'); ++i);
		}
		for (; i < r;) {
			if (m_buffer[i] >= '0') {
				m_v = (m_v << 3) + (m_v << 1) + m_buffer[i] - 48;
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
	int r,i;
};

class FastOutput {
public:
FastOutput() {
	m_dataOffset = 0;
}
~FastOutput() {
}
void Flush() {
	if (m_dataOffset) {
		if (fwrite(m_data,1, m_dataOffset,stdout));
		m_dataOffset = 0;
	}
}
// 300 * 300 uniform so 58295 >10000
//average comp = 1.41
//prev av comp roughly 2.11 
void PrintUint(uint32_t v, char d) {
if (m_dataOffset + 11 > sizeof(m_data)) Flush();
	
	if (v >= 10000) { //64.5 %
		m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 0] = v + 48;
		m_dataOffset += 5;
	} else if (v >= 1000) { //29.4 %
		m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 0] = v + 48;
		m_dataOffset += 4;
	} else {
		if (v >= 100) { //5.2%
			m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 3;
		} else if (v >= 10) {//0.5%
			m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 2;
		} else { //0.025%
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 1;
		}
	}
	/*
	if (v < 1000) { //0.05725
		if (v < 10) { //0.00025
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 1;
		} else if (v < 100) { //0.005
			m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 2;
		} else { //0.052
			m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 3;
		}
	} else { //0.94275
		if (v < 10000) {//0.294
			m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 4;
		} else {//0.645
			m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
			m_data[m_dataOffset + 0] = v + 48;
			m_dataOffset += 5;
		}
	}*/
	
	m_data[m_dataOffset++] = d;
}
public:
uint8_t m_data[32768];
size_t m_dataOffset;
}; 

int main() {
	int n,m;
	FastInput input;
	FastOutput output;
	while (true) {
		n = input.ReadNext();
		m = input.ReadNext();
		//cout << " n = "<< n<<endl;
		if (n == 0x80000000) break;
		output.PrintUint(n*m-1,'\n');
	}
	output.Flush();
	return 0;
}