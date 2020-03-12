#include <stdio.h>
#include <math.h>
#include <time.h>

#define MIN  -9223372036854775808.0
#define MAX 9223372036854775807.0

double sinus(double i, double w,double sum,double z,int c,int d,int n, int l){
    if(l>n){
        return sum;
    }
    z*=(i*i);
    w*=-1;
    d++;
    c*=d;
    d++;
    c*=d;
    sum+=(double)(w*z)/c;
    l++;
    return sinus(i,w,sum,z,c,d,n,l);
}

void accur(double x,double e, int n){
    double sum=sinus(x,1,0,x,1,1,n,1);
    double S=x+sum;
    double Y=sin(x);
    double R=fabs(Y-S);
    if (R<e) {
        printf("For x=%f and for a given accuracy you need to expand to a member %d\n",x, n);
        printf("S(x)= %lf\tY(x)= %lf\t|Y(x)-S(x)|=%lf\n\n",S,Y,R);
        return;
    }
    n++;
    return accur(x,e,n);
}

void schet(double x, double y, double h, double e){
    if(x>y){
        return;
    }
    accur(x,e,1);
    return schet(x+h,y,h,e);

}

int main(){
   clock_t start1, start2, end1, end2;
   double e, a,b,i,h;
   printf("Enter calculation accuracy\n");
   if(scanf("%lf",&e)==0){
       printf("Error, You entered not a number");
       return 1;
   }
   printf("Enter the initial value of x\n");
   if(scanf("%lf",&a)==0){
       printf("Error, You entered not a number");
       return 1;
   }
   printf("Enter the final value of x>= initial value of x\n");
   if(scanf("%lf",&b)==0){
       printf("Error, You entered not a number");
       return 1;
   }
   printf("Enter step of function\n");
   if(scanf("%lf",&h)==0){
       printf("Error, You entered not a number");
       return 1;
   }
   if(a>b){
       printf("Error the initial value should be<= the final value");
       return 1;
   }
   if(MIN>a||a>MAX){
    printf("Error, invalid argument");
    return 1;
   }
   if(MIN>b||b>MAX){
    printf("Error, invalid argument");
    return 1;
   }
   if(MIN>h||h>MAX){
    printf("Error, invalid step");
    return 1;
   }
   if(MIN>e||e>MAX){
    printf("Error, invalid argument");
    return 1;
   }
   double S=0;
   double Y=0;
   double R=0;
   start1=clock();
   for (i = a; i <=b ; i+=h) {//спросить, почему происходит какая-то странная штука при h=0.1
       double w=1;
       double sum=0;
       double z=i;
       int c=1;
       int d=1;
       int n=1;
       while (1){
           for (int l=1; l<=n; l++) {
               z*=(i*i);
               w*=-1;
               d++;
               c*=d;
               d++;
               c*=d;
               sum+=(double)(w*z)/c;
           }
           S=i+sum;
           Y=sin(i);
           R=fabs(Y-S);
           if (R<e) {
               printf("For x=%lf and for a given accuracy you need to expand to a member %d\n",i, n);
               printf("S(x)= %lf\tY(x)= %lf\t|Y(x)-S(x)|=%lf\n\n",S,Y,R);
               break;
           }
           n++;
       }

   }
   end1=clock();
   printf("Iteration version work %f seconds\n\n",(float)(end1- start1)/ CLK_TCK );
   start2=clock();
   schet(a,b,h,e);
   end2=clock();
   printf("Recursion version work %f seconds\n\n",(float)(end2- start2)/ CLK_TCK );
   return 0;
}
