#include <math.h>
#include <stdio.h>
#define db double
int N;
double a, b;
db func(db x) { 
    return log(x);
     }

void simpson() {

  db sm = 0;
  db ans = 0;
  db h = (b - a) / N;
  for (int i = 1; i <N; i++)
   {
    db x = a + i * h;
    sm += (i % 2) ? 4 * func(x) : 2 * func(x);
  }

  ans = h / 3.0 * (sm + func(a) + func(b));
  printf("%lf\n", ans);
}

int main() {
  printf("Enter number of sub intervals\n");
  scanf("%d", &N);
  printf("Enter limits\n");
  scanf("%lf %lf", &a, &b);

  simpson();
}
