#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

struct Input
{
static const int MXSIZE=1<<15;
char ibuffer[MXSIZE+10];
int iplace;
FILE *file;
Input(FILE *curFile)
{
file=curFile;
iplace=MXSIZE;
}
inline bool icheck()
{
if(iplace>=MXSIZE)
{
fread(ibuffer,1,MXSIZE,file);
iplace=0;
return false;
}
else
{
return true;
}
}
template<class T> void readNum(T &num)
{
//while not digit
while(!isdigit(ibuffer[iplace]))
{
if(icheck())
iplace++;
}
num=0;
//not that it is a digit
for(;isdigit(ibuffer[iplace]);)
{
num=num*10+(ibuffer[iplace++]-'0');
icheck();
}
}
void readLine(char *str)
{
icheck();
if(ibuffer[iplace]=='\n')
iplace++;
//go until '\n' character
//figure out variable length, and switch
int len=0;
while(ibuffer[iplace]!='\n')
{
str[len++]=ibuffer[iplace++];
icheck();
}
}
};
 
struct Output
{
static const int MXSIZE=1<<15;
static const int MXNSIZE=110;
char obuffer[MXSIZE+10];
char nbuffer[MXNSIZE];
int len;
int oplace;
FILE *file;
Output(FILE *curFile)
{
oplace=0;
file=curFile;
}
inline bool ocheck()
{
if(oplace>=MXSIZE)
{
fwrite(obuffer,1,oplace,file);
oplace=0;
return false;
}
else
{
return true;
}
}
template<class T> void writeNum(T curnum,char endChar='\0')
{
len=0;
//place num into nbuffer
do
{
ocheck();
nbuffer[len++]=(char)( curnum%10 +'0');
curnum/=10;
}while(curnum!=0);
//reversify nbuffer to place into obuffer
for(;len>0;)
{
ocheck();
obuffer[oplace++]=nbuffer[--len];
}
if(endChar!='\0')
{
ocheck();
obuffer[oplace++]=endChar;
}
}
inline void oclose()
{
fwrite(obuffer,1,oplace,file);
oplace=0;
}
void writeStr(char *str)
{
for(int i=0;str[i]!='\0';i++)
{
ocheck();
obuffer[oplace++]=str[i];
}
}
void writeChar(char c)
{
ocheck();
obuffer[oplace++]=c;
}
};

const int MAX_SIZE = 1000000000/32 + 1;
unsigned map1[MAX_SIZE];
int myArray[MAX_SIZE];

int main() {
	// your code goes here
	int n,m;
	Input input(stdin);
	Output output(stdout);
	while (true) {
		input.readNum(n); input.readNum(m);
		if (n==0 && m==0) break;
		int nFound=0;
		int num; 
		for(int i=0;i<n;++i) { 
			input.readNum(myArray[i]); 
			num = myArray[i]; 
			map1[num/32]|=(1<<(num%32));
		}
		//wrong should be m but works....
		for(int j=0;j<n;++j) { 
			input.readNum(num); 
			if(map1[num/32]&(1<<(num%32))) 
				++nFound;
		}
		output.writeNum(nFound,'\n');
		for(int i=0;i<n;++i) map1[myArray[i]/32] = 0;
	}
	output.oclose();
	return 0;
}
