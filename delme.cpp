#include <iostream>
#include <cmath>
using namespace std;

#define N (1<<22)
double a[N];

int main () {
    /* Make some numbers to work with */
    #pragma omp parallel for
    for ( size_t i=0; i<N; i++ )
        a[i] = (i/4096)*3.0 + (i%4096)*7.0;

    /* Time a loop that gets their square roots */
    #pragma omp parallel for
    for ( size_t i=0; i<N; i++ )
        a[i] = sqrt(a[i]);
    

    cout << a[4780] << endl;
    return 0;
}
