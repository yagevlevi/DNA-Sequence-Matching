/**
 * Assignment #2: Loops, functions, arrays.
 * This program computes simple DNA matching between 2 sequences.
 **/

#include <stdio.h>
#include <stdbool.h>

#define BASE_SEQ_LEN 20
#define TARGET_SEQ_LEN 5
#define NUM_BASES 4
#define THRESHOLD 3


/**********************************************************************
 *  You should :                                                      *
 *   1) carefully read over the writeup on piazza                     *
 *   2) carefully read over the code                                  *
 *   3) run make test to see how the reference binary behaves         *
 *   4) find the locations you need to add code and progressively     *
 *      update your code till it behaves the same as the reference.   *
 *      Don't forget to commit regularly as you conduct your work     *
 *                                                                    *
 *  Each function documents how it should behave.                     *
 *  If you are unsure about how your program should work use the      *
 *  the reference executable provided to understand what the correct  *
 *  behavior is.  When you run make test you see a series of          *
 *  inputs that we will be testing your program with.                 *
/**********************************************************************/

/* function prototypes */
/*  See function definitions below for documentation */
_Bool read_sequence(char[], int);
_Bool match(const char[], const char[], int, int, int);
void print_sequence_part(const char[], int, int);
void print_sequence(const char[], int);
_Bool is_valid_base(char);

/* external variables */
const char bases[] = {'A', 'T', 'C', 'G'};

/**
 * main: This function needs to read and store a sequence of length
 *       BASE_SEQ_LEN. Then it needs to read and store a sequence of 
 *       TARGET_SEQ_LEN. Finally it needs to call match() with both sequences.
**/
int main() {
    char s1[20], s2[5];

    // 1: Read base input sequence into s1 array
    if (read_sequence(s1, 20) == 0) {
      // if read_sequence returned false then there was an error
      printf("ERROR: sequence 1 is bad.  Exiting\n");
      return -1;
    }
    
    // 2: Read target input sequence into s2 array
    if (read_sequence(s2, 5) == 0) {
      // if read_sequence returned false then there was an error
      printf("ERROR: sequence 2 is bad.  Exiting\n");
      return -1;
    }

    // 3: We run match to see if the base sequence holds the target sequence. Returns and prints whatever match() finds.
    match(s1, s2, 20, 5, 3);
      
    return 0;
}

/****************************************************************************
 * Prints a sequence part indicated by the start and end (excluded) indices.*
 ****************************************************************************/
void print_sequence_part(const char s[], int start, int end) {
    for (int i=start; i<end; i++) {
        printf("%c", s[i]);
    }
}

/****************************************************************************
 * Prints a sequence of bases.                                              *
 ****************************************************************************/
void print_sequence(const char s[], int len) {
    print_sequence_part(s, 0, len);
    printf("\n");
}

/****************************************************************************
 * Prompts the user to input a seq_len sequence and press Enter/Return      *
 * reads a sequence of bases (A, T, C, G) and stores it in s.               *
 * Invalid bases (values that not one of the four valid bases) are ignored. *
 * If the  sequence inputed is too short then return false                  *
 *                                                                          *
 * A newline '\n' is generated when the user presses the Enter or Return    *
 * key. In such cases scanf will read the special ascii value '\n' into the *
 * variable.                                                                *  
 *                                                                          *
 * In our case we should continue to read values until we encounter a       *
 * newline.  Prior to reading a newline each valid base should be stored    *
 * consecutively into the s array until seq_len valid values have been      *
 * read.  Any addtioinal values should be ignored.                          *
 * eg.                                                                      *
 *   assuming seq_len=3                                                     *
 *    INPUT: "AGG\n"->  s[0]='A' s[1]='G' s[2]='G' return true              *
 *    INPUT: "aAgGqGv\n"->  s[0]='A' s[1]='G' s[2]='G' return true          *
 *    INPUT: "A\n"-> s[0]='A' return false                                  *
 *    INPUT: "aaaaaaaaaaaaaa' -> return false                               *
 *    INPUT: "AGGTAGGT" -> s[0]='A' s[1]='G' s[2]='G' return true           *
 ****************************************************************************/
_Bool read_sequence(char s[], int seq_len) {
    char b;
    int i = 0;

    printf("Enter a sequence of length %d: ", seq_len);
    // Read first character in to get us started
    scanf("%c", &b);

    // we continue looping until b holds a newline character which symbolizes the user has pressed enter and finished inputing the sequence
    while (b != '\n') {
      // the first if statement checks to see if we already have 5 elements in our target sequence
      if (i == seq_len) break;
      // second if checks to see if the base is valid, if so it add it to the array and increments i the scans again for the next char
      if (is_valid_base(b)) {
        s[i] = b;
        i++;
        scanf("%c", &b);
      } else {
        // we reach here if the char is not valid in which case we simply move on and scan for the next char
        scanf("%c", &b);
      }
    }

    // When we are done looping i holds the length of valid bases read
    if (i != seq_len) {
      printf("Invalid: input sequence too short\n");
       return 0; // sequence too short
    }
    printf("Valid input sequence: ");
    print_sequence(s, seq_len);
    return 1;
}

/****************************************************************************
 * Checks whether the input character represents a valid base.              *
 * Returns false if b is not in the bases array which is preloaded with     *
 *  'A', 'C', 'G', 'T'.                                                     *
 ****************************************************************************/
_Bool is_valid_base(char b) {
  // this loop iterates through the constant bases array that verifies whether certain characters are indeed valid
  for (int i = 0; i < 4; i++) {
    if (b == bases[i]) {
      return 1;
    }
  }
  // if we got here then we must not have matched any of the bases elements
  return 0;
}

/****************************************************************************
 *  This function will do the real work to try and match the two DNA        *
 *  sequences. In this case, the base sequence (variable s1) will be the    * 
 *  DNA sequence we are trying to reconstruct, and its length is stored in  *
 *  the variable len1. The target sequence (s2) will be the DNA sequence    * 
 *  that we are trying to match to the base sequence to determine if it is  *
 *  a part of that sequence, and its length is stored in len2.              *
 *                                                                          *
 *  This function needs to detect matches, and return whether or not a      *
 *  match was found. Additionally, this function needs to print out one of  *
 *  two possibilities, depending on if a match was found. If a match was    *
 *  found, the function needs to print out "A match was found" and then the *
 *  concatenated sequence. You can use the print_sequence_part function to  *
 *  help with printing out the concatenated sequence. If a match was not    *
 *  found, the function needs to print out "No match found".                *
 *                                                                          *
 *  There are two cases for matching that the function should check for.    *
 *  First is if the target sequence appears inside the base sequence        *
 *  itself.                                                                 *
 *  For example:                                                            *
 *                                                                          *
 *  Base: AAACTGGGT             =>  A match was found.                      *
 *  Target: ACTGG                   AAACTGGGT                               *
 *                                                                          *
 *  This would be a match because the target string ACTGG appears fully     *
 *  within the base seqeunce.                                               *
 *                                                                          *
 *  The other case is if the base sequence is a proper prefix to the target *
 *  string (the last bases of base sequence are the same as the first bases *
 *  of the target sequence) AND the length of the overlap is equal to or    *
 *  greater than the threshold. For example, assuming a threshold of 3:     *
 *                                                                          *
 *  Base: AAACTGGG              =>  A match was found.                      *
 *  Target:    GGGTC                AAACTGGGTC                              *
 *                                                                          *
 *  Base: AAACTGGG              =>  No match found.                         *
 *  Target:     GGACT                                                       *
 *                                                                          *
 *  The first example is a match because GGG is the last 3 bases of the     *
 *  base and the first 3 bases of the target. The second example is NOT a   *
 *  match because only 2 bases overlap.                                     *
 *                                                                          *
 *  One way to implement this is by lining up s2 at the end of s1 so that   *
 *  they have `threshold` bases overlap. If no valid match is found, slide  *
 *  s2 to left by one position. Repeat until either a match is found or no  *
 *  overlap >= threshold is possible anymore.                               *
 *                                                                          *
 *  Example:                                                                * 
 *  --------                                                                * 
 *  s1 = CCGTTACAGG, s2 = TACAG, threshold = 3                              * 
 *                                                                          * 
 *  CCGTTACAGG                                                              * 
 *         TACAG                                                            * 
 *                                                                          * 
 *  CCGTTACAGG                                                              * 
 *        TACAG                                                             * 
 *                                                                          * 
 *  CCGTTACAGG                                                              * 
 *       TACAG                                                              * 
 *                                                                          * 
 *  CCGTTACAGG                  =>  A match was found.                      *
 *      TACAG                       CCGTTACAGG                              *
 *                                                                          *
 *                                                                          *
 *  -----                                                                   *
 *  BONUS                                                                   *
 *  -----                                                                   *
 *  For bonus points, add functionality to detect matches where the target  *
 *  sequence is a proper prefix to the base sequence. For example:          *
 *                                                                          *
 *  Base:     AAACTGGG          =>  A match was found.                      *
 *  Target: GTAAA                   GTAAACTGGG                              *
 *                                                                          *
 *  This would be a match because because AAA is the last 3 bases of the    *
 *  target sequence and the first 3 bases of the base sequence.             *
 *                                                                          *
 ****************************************************************************/
_Bool match(const char s1[], const char s2[],
     int len1, int len2, int threshold) {
  
    int j,k;
    // this big outer loop starts at the minimum threshold point from the end of the base sequence
    for (int i = len1 - threshold; i >= 0; i--) {
        j = i;
        // if we are still checking only the partial part (within the threshold) of the target we enter this if statement
        if (i > len1 - len2) {
          int counter = 0;
          for (int q = 0; q < len1 - i; q++){
            if (s1[j] == s2[q]){
              counter++;
              j++;
            } else {
              j++;
              break;
            }
          }
          // here we check if we found a match by comparing the counter to len1 - i which is always >= threshold
          if (counter == len1 - i){
            printf("A match was found.\n");
            print_sequence_part(s1, 0, len1);
            print_sequence_part(s2, len1 - i, len2);
            return 1;
          }
        } else {
          int counter = 0;
          // here we just loop through the interior of the base sequence and everytime i is incrmeneted, j is too and we mov deeper and deeper
          // into the base sequence
          for (int r = 0; r < len2; r++) {
            if (s1[j] == s2[r]){
              counter++;
              j++;
            } else {
              j++;
              break;
            }
          }
          // here again we check the length of the counter to the length of the target sequence to verify we have checked all characters
          // in the sequence
          if (counter == len2) {
            printf("A match was found.\n");
            print_sequence(s1, len1);
            return 1;
          }
        }
    }
    // we only reach this point if we didn't find a match throughout the whole base sequence so we decalre no match found
    printf("No match found.\n");
    return 0;
}
