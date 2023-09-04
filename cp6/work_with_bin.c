#include <stdio.h>
#include "student.h"
#include <string.h>

int main(int argc, char* argv[]) {
  //Первым передаем bin
  //Вторым передаем базу переданных
  //Третьим 
  printf("%d\n", argc);
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Некорректное число переданных файлов\n");
    return 100;
  }
  printf("|Фамилия|Инициалы|Пол\t|Ном. гр.|Архитектура|ВАРКТ|ДМ|История|ЛААГ|МА|ФИ(э)|ФИ(кп)\n");
  student st;
  float min_average = 100000.0;
  FILE *in = fopen(argv[1],  "r");
  while (fread(&st, sizeof(st), 1, in) == 1){ //тут нашли минимальный средний балл
    float average = (float)(st.architecture + st.VARKT + st.discra + st.history + st.LAAG
    + st.mat_analisys + st.fund_e + st.fund_kp) / 8.0;
    if (min_average > average) {
      min_average = average;
    }
    printf("|%s|%s\t|%s|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\n", st.second_name,
    st.initials, st.gender, st.group_num, st.architecture, st.VARKT, st.discra,
    st.history, st.LAAG, st.mat_analisys, st.fund_e, st.fund_kp);
  }

  //тут будем искать студентов с минимальным средним баллом
  int amount_in_groups[14] = {0};
  fseek(in, 0, SEEK_SET);

  while (fread(&st, sizeof(st), 1, in) == 1) {
    float average = (float)(st.architecture + st.VARKT + st.discra + st.history + st.LAAG
    + st.mat_analisys + st.fund_e + st.fund_kp) / 8.0;
    if (average == min_average) {
      amount_in_groups[st.group_num % 100]++;
    }
  }
  //printf("%f\n", min_average);
  int max_amount_of_min_students = 0;
  int ans = 101;
  for (int i = 1; i < 14; i++) {
    //printf("%d\n", amount_in_groups[i]);
    if (amount_in_groups[i] >= max_amount_of_min_students) {
      max_amount_of_min_students = amount_in_groups[i];
      ans = i+100;
    }
  }
  printf("Группа с максимальным количеством студентом с минимальным на курсе средним баллом: %d\n", ans);
}
