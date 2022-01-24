#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
  int months; // for the number of months it is applicable to
  double contribution;  // how many dollars are contributed (or spent if negative) from the account per month
  double rate_of_return;  // the rate of returns
};
typedef struct _retire_info retire_info;

int year(int month){
  return month/12;
}

int month_left(int month){
  return month%12;
}

// return the balance after 1 month
double balance(double init_balance, double rate, double cb){
  return init_balance + init_balance*rate + cb;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired){
  int age = startAge;
  double saving = initial;
  printf("Age %3d month %2d you have $%.2lf\n", year(age), month_left(age), saving);
  for(int i = 0; i < working.months; i++){
    saving = balance(saving, working.rate_of_return, working.contribution);
    age++;
    printf("Age %3d month %2d you have $%.2lf\n", year(age), month_left(age), saving);
  }
  for(int i=0; i < retired.months-1; i++){
    saving = balance(saving, retired.rate_of_return, retired.contribution);
    age++;
    printf("Age %3d month %2d you have $%.2lf\n", year(age), month_left(age), saving); 
  }
}



int main(){
  retire_info working = {489, 1000, 0.045/12};
  retire_info retired = {384, -4000, 0.01/12};
  int start_month = 327;
  double start_saving = 21345;
  retirement(start_month, start_saving, working, retired);
  return 0;
}
