#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std; 
int p,q,r,s,t,u;
 
double f(double x){
  return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}
//maybe wrong but don't really care right now
double bisection(){
  double low = 0, high = 1;
  for(int i=0;i<100;i++) {
    double x = (low+high)/2;
    if (f(x) < 0){
      high = x;
    } else {
      low = x;
    }
  }
  return (low+high)/2;
}
 
int main(){
  ios_base::sync_with_stdio(false);
  while (cin >> p >> q >> r >> s >> t >> u){
    double ans = bisection();
    if (fabs(f(ans))> 5e-5) 
      printf("No solution\n");
    else
      printf("%.4lf\n", ans);
  }
  return 0;
}
