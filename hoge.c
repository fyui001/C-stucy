#include<stdio.h>
#include<stdint.h>
#include<string.h>

typedef struct input_data {
  char  *question_str;
  char  *input_format;
  int    input_mem_size;
  char   *input_type;
  char   *input_val_format;
  intptr_t input_ptr;
} data;

/*  */
int mem_free(data *d, int n){
  int i;
  for(i = 0; i < n; i++){
    free(d[i].input_ptr);
    d[i].input_ptr = NULL;
  }
}

/* 書き込み関数 */
int mywrite(FILE *p){
  char *format = "%-15s %-15d\n";
  data d[] = {
    {
      .question_str = "氏名 --- \n", /* 入力する項目 */
      .input_format = "%s", /* 入力を受け取るfscanfの書式指定 */
      .input_mem_size = sizeof(char) * 4096, /* 受け取る入力のサイズ */
      .input_type = "char", /* 入力を受け取る変数の型 */
      .input_val_format = "%-15s", /* ファイルに出力ときのフォーマット */
      .input_ptr = NULL, /* 入力を受け取る変数へのポインタ(とりあえずNULL初期化をする) */
    },
    {
      .question_str = "年齢 --- \n",
      .input_format = "%d",
      .input_mem_size = sizeof(int),
      .input_type =  "int",
      .input_val_format = "%-15d",
      .input_ptr = NULL,
    },
  };

  int i,  n_data;
  char yesno[8];
  n_data = sizeof(d) / sizeof(data); /* 書き込みの要素数 */

  /* メモリの確保とデータの入力 */
  for(i = 0; i < n_data; i++){
    intptr_t m = malloc(d[i].input_mem_size); /* ここでメモリを確保 */
    d[i].input_ptr = m;
    fprintf(stdout, d[i].question_str);
    fscanf(stdin, d[i].input_format, d[i].input_ptr);
  }

  fprintf(stdout, "このデータを書き込みますか (y/n)\n"); /* 書き込み認証 */
  fscanf(stdin, "%s", yesno);

  if(strcmp(yesno, "y") == 0 || strcmp(yesno, "Y") == 0 || strcmp(yesno, "yes") == 0 || strcmp(yesno, "YES") == 0){
    for(i = 0; i < n_data; i++){
      if(strcmp(d[i].input_type, "char") == 0){
        fprintf(p, d[i].input_val_format, d[i].input_ptr);
      }
      if(strcmp(d[i].input_type, "int") == 0){
        fprintf(p, d[i].input_val_format, *(int*)(d[i].input_ptr));
      }
    }
    fprintf(stdout, "さらにデータを書き込みますか? (y/n)\n");
    fscanf(stdin, "%s", yesno);
    mem_free(d, n_data); /* 確保したメモリを開放する */
  }

  if(strcmp(yesno, "n") == 0 || strcmp(yesno, "N") == 0 || strcmp(yesno, "no") == 0 || strcmp(yesno, "NO") == 0){
    mem_free(d, n_data); /* 確保したメモリを開放する */
    return -1;
  }
  return 0;
}


/* 読み込み関数 */
int myread(FILE *p){
  char name[64];
  char age[8];
  char *format = "%-15s %-15s\n"; /* ファイルを読み込むフォーマット(必要に応じて変更の要有り)*/
  while(fscanf(p, "%s%s", name, age) != EOF){
    fprintf(stdout, format, name, age);
  }
  if(fscanf(p, "%s%s", name, age) == EOF){
    return -1;
  }
}


int main(){

  FILE *fp;
  char mode[8];
  char f_name[64];

  fprintf(stdout,"ファイル名(拡張子不要)---\n");
  fscanf(stdin, "%s", f_name);
  strcat(f_name, ".txt");

  fprintf(stdout, "書き込み(追加): a, 読み込み:r\n");
  fscanf(stdin, "%s", mode);

  fp = fopen(f_name, mode);

  if(fp == NULL){
    fprintf(stdout, "やっちまった。\n");
    return -1;
  }

  if(strcmp(mode, "a") == 0){
    while(!mywrite(fp));
    fclose(fp);
  }else if(strcmp(mode, "r") == 0){
    while(!myread(fp));
    fclose(fp);
  }

  return 0;
}
