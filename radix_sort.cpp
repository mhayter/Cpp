
#include <iostream>
using namespace std;


//modified from Quora

void _radix_sort_lsb(unsigned *begin, unsigned *end, unsigned *begin1, unsigned maxshift){
    unsigned *end1 = begin1 + (end - begin);
 
    for (unsigned shift = 0; shift <= maxshift; shift += 8)
    {
        size_t count[0x100] = {};
        for (unsigned *p = begin; p != end; p++)
            count[(*p >> shift) & 0xFF]++;
        unsigned *bucket[0x100], *q = begin1;
        for (int i = 0; i < 0x100; q += count[i++])
            bucket[i] = q;
        for (unsigned *p = begin; p != end; p++)
            *bucket[(*p >> shift) & 0xFF]++ = *p;
        std::swap(begin, begin1);
        std::swap(end, end1);
    }
}

void _radix_sort_msb(unsigned *begin, unsigned *end, unsigned *begin1, unsigned shift)
{
    unsigned *end1 = begin1 + (end - begin);
 
    size_t count[0x100] = {};
    for (unsigned *p = begin; p != end; p++)
        count[(*p >> shift) & 0xFF]++;
    unsigned *bucket[0x100], *obucket[0x100], *q = begin1;
    for (int i = 0; i < 0x100; q += count[i++])
        obucket[i] = bucket[i] = q;
    for (unsigned *p = begin; p != end; p++)
        *bucket[(*p >> shift) & 0xFF]++ = *p;
    for (int i = 0; i < 0x100; ++i)
        _radix_sort_lsb(obucket[i], bucket[i], begin + (obucket[i] - begin1), shift - 8);
}

void radix_sort2(unsigned *begin, unsigned *end)
{
    unsigned *begin1 = new unsigned[end - begin];
    _radix_sort_msb(begin, end, begin1, 24);
    delete[] begin1;
}
void radix_sort1(unsigned *begin, unsigned *end)
{
    unsigned *begin1 = new unsigned[end - begin];
    unsigned *end1 = begin1 + (end - begin);

    for (unsigned shift = 0; shift < 32; shift += 8) {
        size_t count[0x100] = {};
        for (unsigned *p = begin; p != end; p++)
            count[(*p >> shift) & 0xFF]++;
        unsigned *bucket[0x100], *q = begin1;
        for (int i = 0; i < 0x100; q += count[i++])
            bucket[i] = q;
        for (unsigned *p = begin; p != end; p++)
            *bucket[(*p >> shift) & 0xFF]++ = *p;
        std::swap(begin, begin1);
        std::swap(end, end1);
    }

    delete[] begin1;
}
#include <iostream>
#include <algorithm>
unsigned a[1000010];
#include "my_fast_io.h"
FastInput input;
FastOutput output;
int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    int n=input.readNextUnsigned();  
    cerr << "n= " << n << endl;
    for(int i=0;i<n;++i){
        a[i] = input.readNextUnsigned();
        //cerr << "a[i] = " << a[i] << endl;
    }
    stable_sort(a,a+n);
    //radix_sort2(a,a+n);
    //cerr << a[n-1] << endl;
    for(int i=0;i<n;++i) output.printUnsigned(a[i],'\n');
    output.flush();
    return 0;
}