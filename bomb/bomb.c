/***************************************************************************
 * Dr. Evil's Insidious Bomb, Version 1.1
 * Copyright 2011, Dr. Evil Incorporated. All rights reserved.
 *
 * LICENSE:
 *
 * Dr. Evil Incorporated (the PERPETRATOR) hereby grants you (the
 * VICTIM) explicit permission to use this bomb (the BOMB).  This is a
 * time limited license, which expires on the death of the VICTIM.
 * The PERPETRATOR takes no responsibility for damage, frustration,
 * insanity, bug-eyes, carpal-tunnel syndrome, loss of sleep, or other
 * harm to the VICTIM.  Unless the PERPETRATOR wants to take credit,
 * that is.  The VICTIM may not distribute this bomb source code to
 * any enemies of the PERPETRATOR.  No VICTIM may debug,
 * reverse-engineer, run "strings" on, decompile, decrypt, or use any
 * other technique to gain knowledge of and defuse the BOMB.  BOMB
 * proof clothing may not be worn when handling this program.  The
 * PERPETRATOR will not apologize for the PERPETRATOR's poor sense of
 * humor.  This license is null and void where the BOMB is prohibited
 * by law.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
//#include "support.h"
//#include "phases.h"

/* 
 * Note to self: Remember to erase this file so my victims will have no
 * idea what is going on, and so they will all blow up in a
 * spectaculary fiendish explosion. -- Dr. Evil 
 */

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    /* Note to self: remember to port this bomb to Windows and put a 
     * fantastic GUI on it. */

    /* When run with no arguments, the bomb reads its input lines 
     * from standard input. */
    if (argc == 1) {  
	infile = stdin;
    } 

    /* When run with one argument <file>, the bomb reads from <file> 
     * until EOF, and then switches to standard input. Thus, as you 
     * defuse each phase, you can add its defusing string to <file> and
     * avoid having to retype it. */
    else if (argc == 2) {
	if (!(infile = fopen(argv[1], "r"))) {
	    printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	    exit(8);
	}
    }

    /* You can't call the bomb with more than 1 command line argument. */
    else {
	printf("Usage: %s [<input_file>]\n", argv[0]);
	exit(8);
    }

    /* Do all sorts of secret stuff that makes the bomb harder to defuse. */
    initialize_bomb();

    printf("Welcome to my fiendish little bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    /* Hmm...  Six phases must be more secure than one phase! */
    /* objdump -d bomb > bomb.s 获取汇编语言 */
    /* objdump -t bomb > bomb1.s 获取符号表 */
    /* Answer: Border relations with Canada have never been better. */
    /* 
        step1: gdb bomb
        step2: break phase_1    打断点在phase_1
        step3: run              运行起来
        step4: stepi/step       单步调试和跳过当前调用来查看每一步
        step5: print /x $rax    查看寄存器中的值
             : p/x $rax
        step6: disass phase_1   查看函数的汇编语言
             : disasseble phase_1
        step7: x/3sb 0x402400   内存地址0x402400读取3个单字节为单位的内容,s为字符输出
        more gdb info in https://www.cnblogs.com/chengliangsheng/p/3597010.html
                    or   https://www.cnblogs.com/xwt19970518/p/11070170.html
        step8: the details think && answer interpretation in bomb.s
     */
    input = read_line();             /* Get input                   */
    phase_1(input);                  /* Run the phase               */
    phase_defused();                 /* Drat!  They figured it out!
				      * Let me know how they did it. */
    printf("Phase 1 defused. How about the next one?\n");

    /* The second phase is harder.  No one will ever figure out
     * how to defuse this... */

    /* Answer: 1 2 4 8 16 31 */
    /* 
        1. read_six_numbers调用 单步stepi 会出问题
        2. http://csapp.cs.cmu.edu/public/students.html this websit has material book about gdb
        3. detail solution can see bomb.s
     */
    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2.  Keep going!\n");

    /* I guess this is too easy so far.  Some more complex code will
     * confuse people. */
    /* Answer: {{0,207}, {1,311}, {2,707}, {3,256}, {4,389}, {5,206}, {6,682}, {7,327}} */
    /* 
        according to the first input number ensure the second one;
        the detail info in bomb.s
     */
    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there!\n");

    /* Oh yeah?  Well, how good is your math?  Try on this saucy problem! */
    /* Answer: 7 0 */
    /* 
       1.the first input used in the fun4 do search in [0, 0xe], fun4 return the search times
       if times is 1 return will be 0, others will the oringinal one, the return must be 0,
       so the first must be 7(the mid of the boundary [0, 14]);
        2. the second input canbe easy find;
        the detail info in bomb.s
     */
    input = read_line();
    phase_4(input);
    phase_defused();
    printf("So you got that one.  Try this one.\n");
    
    /* Round and 'round in memory we go, where we stop, the bomb blows! */
    /* One of the Answer: ionefg */
    /* 
       1. we can ensure the length of the input should be 6 first;
       2. we can get a secret corresponding table && the test string;
       3. we get the character which can converted to the same string with the test string
            after it mod 0xf;
       4. the mod 0xf table of character shows as following:
        1  2  3  4  5  6  7  8  9 10 11 12 13 14 15  0  1  2  3  4  5  6  7  8  9 10
        a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
        A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
        0  1  2  3  4  5  6  7  8  9
       5. the test string is "flyers";
          the secret table is:
            0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
            m  a  d  u  i  e  r  s  n  f  o  t  v  b  y  l
        so the input string after mod should be 9-15-14-5-6-7
        choose the combination characters in the mod 0xf table that satisfy the command
        6. the detail info are in bomb.s;
     */

    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Good work!  On to the next...\n");

    /* This phase will never be used, since no one will get past the
     * earlier ones.  But just in case, make this one extra hard. */

    /* Answer: 4 3 2 1 6 5 */
    /* 
    the function phase_6 can be divided into 6 parts:
        1. read six numbers
        2. each of them should not be equal to each other (the number should <= 6 && >= 1)
        3. each of deal with 7 - input
        4. get the addr of each node-i
        5. reconstruct the link of these node and add null-ptr in the end
        6. do comparison,the last node should greater than the next one
     */
    input = read_line();
    phase_6(input);
    phase_defused();

    /* Wow, they got it!  But isn't something... missing?  Perhaps
     * something they overlooked?  Mua ha ha ha ha! */
    /* Answer: 22 */
    /* 
    the secret_phase canbe find in function phase_defused, the trigger of secret_phase is that
    in the input string3 should be "7 0 DrEvil";

    1. after enter secret_phase, the first function is strtol which is used to transfer string to a long integer(temp)
    2. the temp - 1 <= 0x3e8, if input > 1001(0x3e8+1) the program will enter loop
    3. then enter fun7 with a linklist node addr && temp
    4. the linklist struct is {data, ptr1, ptr2} 
        if data <= temp choose link ptr2, else choose link ptr1
        ptr2 return 2*rax+1, while ptr1 return 2*rax, cannot find return -1;
        (the condition in secret_phase request the return is 2) 
        so the search procedure is ptr2-->ptr1-->return, then we can find the data in the linklist
    
     */
    return 0;
}
