#include <stdio.h>

int hash(const char *str_in);

int main(){
  char c[] = "Ar, PE 2!";
  int result = hash(c);
  printf("Hash for '%s': %d\n", c, result);
  return 0;
}

int hash(const char *str_in){
  int map[] = {18,11,10,21,7,5,9,22,17,2,12,3,19,1,14,16,20,8,23,4,26,15,6,24,13,25};
  int index = 0;
  int hash = 0;
  while(str_in[index] != '\0'){
    if(str_in[index] >= 'A' && str_in[index] <= 'Z'){
      hash += map[str_in[index] - 'A'];
    }
    if(str_in[index] >= '1' && str_in[index] <= '9'){
      hash -= str_in[index] - '0';
    }
    index++;
  }
  return hash;
}
