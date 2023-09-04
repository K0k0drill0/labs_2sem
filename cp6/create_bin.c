#include <stdio.h>
#include "student.h"


int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Странное количество переданных файлов\n");
    return 100;
  }
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  student st;



  while(fscanf(in, "%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d", st.second_name,
  st.initials, st.gender, &st.group_num, &st.architecture, &st.VARKT, &st.discra,
  &st.history, &st.LAAG, &st.mat_analisys, &st.fund_e, &st.fund_kp) == 12) {
    if (fwrite(&st, sizeof(st), 1, out) != 1) {
      fprintf(stderr, "Файла для вывода нет(");
      return 101;
    }
    
  }
  fclose(in);
  fclose(out);
  return 0;
}
