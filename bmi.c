#include<stdio.h>

struct data{
  char name[64];
  int age;
  double bl;
  double bw;
  double bmi;
};

int struct_input(struct data*);

 int main(){
   struct data mydata;
   char format[] = "%sさん(%d歳)プロフィール 身長:%5.1fcm, 体重:%4.1fkg, BMI = %4.2f\n";
   char buffer[256];

   struct_input(&mydata);

   sprintf(buffer, format, mydata.name, mydata.age, mydata.bl, mydata.bw, mydata.bmi);
   printf(buffer);

   return 0;
 }

 int struct_input(struct data *p){
   char name[32];
   char *format[] ={
     "%s",
     "%d",
     "%5.1f",
     "%5.1f",
     "%5.1f",
   };
   char *info[] ={
     "氏名 --- ",
     "年齢 --- ",
     "身長 --- ",
     "体重 --- ",
   };

   //氏名
   printf("氏名 --- ");
   scanf("%s", &p->name);
   //年齢
   printf("年齢 --- ");
   scanf("%d", &p->age);
   //身長
   printf("身長 --- ");
   scanf("%lf", &p->bl);
   //体重
   printf("体重 --- ");
   scanf("%lf", &p->bw);
   //bmi
   p->bmi = p->bw * 10000.0  / (p->bl * p->bl);
   

   return 0;
 }
