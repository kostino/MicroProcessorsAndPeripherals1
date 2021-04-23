//By Triaridis Konstantinos and Angelos Vlachos
#include <string.h>


__asm int asm_hash(char *str,int *map){

	MOVS r4,#0						//r4 result
	
	
hash_loop
	LDRB r5,[r0]					//r5 has value of str
	CMP r5,#'Z'						//Compare and check if Higher Than ASCII of Z
	BHI hash_skip					//If yes go to label hash_skip
	CMP r5,#'0'-1					//Compare and check if Equal or less than (ASCII of 0) - 1
	BLS hash_skip					//If yes go to label hash_skip
	CMP r5, #'9'					//Compare and check if equal or less than ASCII of 9 -> we have checked already that it is > 0 so character is a number
	BLS hash_number				//If yes then go to label hash_number
	CMP r5, #'A'-1				//Compare and check if equal or less than (ASCII of A) - 1
	BLS hash_skip					//If yes go to label hash_skip
	//CAPS								//If you reach this that means that the character is an upper case letter so
	SUBS r7, r5, #'A'			//r7 = ASCII of character - ASCII of A
	MOVS r9, #4						//r9=4
	MUL r7, r9, r7				//r7 = r7*4	in order to index an int(sizeof(int) = 4 bytes) array
	ADDS r7, r7, r1				//r7 = r7 + r1(2nd argument, memory of map) r7 is now the index(address) of the value we need from array "map"
	LDRB r8 ,[r7]					//Load element at memory address r7 from array "map"
	ADDS r4, r4, r8				//Add element to hash
	B hash_skip						//Go to label hash_skip
	
hash_number							//If you are here it means that the character is a number (0-9)
	SUBS r8, r5, #'0'			//Subtract ASCII of 0 from the ASCII value of the number so r8 has the number itself(ex. '3' is 51, '0' is 48, so '3'-'0' = 3)
	SUBS r4, r4, r8				//Subtract the number from the hash
	B hash_skip						//Go to label hash skip
	
hash_skip								//This label means that either the character does not affect the hush, or that the hush has been already mofified from the currect character
	ADDS r0, r0, #1				//Move memory pointer of array str to check next char
	CMP r5, #0						//Compare and check if the character we have been checking is '\0', that means the string has ended
	BNE hash_loop					//If not, go to label hash_loop(continue)
	MOVS r0, r4						//If you reach this line then the hash is ready, so we move it to r0 which is the return register too
	BX lr									//return to main

}



int hash(const char *str_in,int *map){										//C implementation
  
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

int main(void)
{
		int map[] = {18,11,10,21,7,5,9,22,17,2,12,3,19,1,14,16,20,8,23,4,26,15,6,24,13,25};	//hash map
		//const char c1[] = "Ar, PE 2!";
		char *c[3]={"Ar, PE 2!","N! N?-1_1N;1","1111"};															//array with string to test
		volatile int result = 0;
		volatile int result_asm = 0;
		char test[30] ="";
		volatile int i=0;
		for(i=0; i<3; i++){																																	//test 
			strcpy(test,c[i]);
			result = hash(c[i],map);
			result_asm = asm_hash(c[i],map);
		}

		while (1);
		return 0;
}
