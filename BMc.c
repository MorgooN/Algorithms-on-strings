#include <stdio.h>
#include <limits.h>
#include <string.h>

#define NO_OF_CHARS 256

int max(int a,int b){ return (a>b)? a:b;}

void badCharHeuristic(char* str, int size,
int badChar[NO_OF_CHARS]){
   int i;
   // all occurences as -1
   for(i = 0; i < NO_OF_CHARS;++i){
      badChar[i]=-1;
   }

   // Fill the actual value of last occurrence
    // of a character
   for(i = 0; i < size; ++i){
      badChar[(int)str[i]]=i;
   }
}

void search(char* txt, char* pat){
   int m = strlen(txt);
   int n = strlen(pat);

   int badChar[NO_OF_CHARS];

   badCharHeuristic(pat,n,badChar);

   int s =0;

   while(s <= m-n){
      int j = n-1;
      while(j >=0 && pat[j]==txt[s+j])
         j--;
      
      if(j < 0 ){
         printf("Pattern match at position = %d",s);
         /*
         Shift the pattern so that the next
         character in text aligns with the last
         occurrence of it in pattern.
         */
         s += (s+n<m) ? n - badChar[txt[s+n]]:1;               
      }
      else{
         /* Shift the pattern so that the bad character
               in text aligns with the last occurrence of
               it in pattern. The max function is used to
               make sure that we get a positive shift.
               We may get a negative shift if the last
               occurrence  of bad character in pattern
               is on the right side of the current
               character. */
         s += max(1, j - badChar[txt[s + j]]);
      }
   }
}

int main()
{
    char txt[] = "ABAAABCD";
    char pat[] = "BCD";
    search(txt, pat);
    return 0;
}

