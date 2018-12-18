#include<stdio.h>
#include<stdint.h>

typedef struct str_data {
  char *question;
  char *input_format;
  char *input_val_type;
  int input_mem_size;
  char *output_format;
  intptr_t input_val_ptr;
} data;

/* メモリ解放! */
int mem_free(data *d, int data_n){
  int i;
  for(i = 0; i < data_n; i++){
    free(d[i].input_val_ptr);
    d[i].input_val_ptr = NULL;
  }
}

int main(){

  data  q[] = {
    {
      .question = "アイドルの名前を入力\n", /* 質問内容 */
      .input_format = "%s", /* 入力するfscanfへ渡す書式指定 */
      .input_val_type = "char", /*  */
      .input_mem_size = sizeof(char) * 4096, /* 確保するメモリのサイズ */
      .output_format = "%s", /* 結果を出力する書式指定 */
      .input_val_ptr = NULL, /* 答えを受け取る変数へのポインタ (とりあえずNULL初期化) */
    },
    {
      .question = "アイドルの年齢を入力\n",
      .input_format = "%d",
      .input_val_type = "int",
      .input_mem_size = sizeof(int),
      .output_format = "%d歳、",
      .input_val_ptr = NULL,
    },
    {
      .question = "アイドルのバストサイズを入力\n",
      .input_format = "%d",
      .input_val_type = "int",
      .input_mem_size = sizeof(int),
      .output_format = "B%d!?\n",
      .input_val_ptr = NULL,
    },
  };

  int n_question = sizeof(q) / sizeof(data);
  int i;

  for (i = 0; i < n_question; i++) {
    fprintf(stdout, q[i].question);
    intptr_t m = malloc(q[i].input_mem_size);
    q[i].input_val_ptr = m;
    fscanf(stdin, q[i].input_format, q[i].input_val_ptr);
  }

  for(i = 0; i < n_question; i++){
    if(strcmp(q[i].input_val_type, "char") == 0){
      fprintf(stdout, q[i].output_format, q[i].input_val_ptr);
    }
    if(strcmp(q[i].input_val_type, "int") == 0){
      fprintf(stdout, q[i].output_format, *(int*)(q[i].input_val_ptr));
    }
  }
  /* メモリを開放する */
  mem_free(q, n_question);
  return 0;
}
