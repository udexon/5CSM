# 5CSM
5GL C Stack Machine (Fifth Generation Graph Language)

jonesforth or similar Forth implementations primarily aim to implement a program (stack machine) to execute Forth words, with an architecture that is independent and unrelated to GNU C Compiler.

I am thinking of creating a stack machine, similar to Forth of course, that is based on GCC, where the main novelty would be to use EAX (RAX etc.) as top of stack (TOS), so as to reduce memory access using variables.

The background of my idea can be summarized in the following article:

https://www.linkedin.com/pulse/multitiered-stack-machine-nsm-using-5gl-fifth-graph-ng-ph-d-/

To describe it in an abstract manner, Forth has its own way of implementing a stack machine. Alternatively, a stack machine can also be implemented using GCC, which would need to incorporate various C conventions, such as returning function value in EAX.

https://github.com/udexon/5C/blob/master/sc.c

As Forth veterans would recall, Forth words are implemented starting from primitive words to "high level" words.

In the github example above, the 5GL/C stack machine (5CSM) needs to parse a string, to decide if it is an integer, float or leave it as a string. strcspn() is used to detect the position of "e" or "E", for the exponent character in a floating point representation, then the first part is checked to consist of only (+  - . digits)  only and second part to consist of only (+ - digits).

https://github.com/udexon/5C/blob/master/sd.c

The files named sc.c and sd.c simply mean 's' for stack machine, version d and e. A quick comparison of sc.c and sd.c shows the additional functions required to determine if the string is a floating point number.

At this point, a C veteran could probably visualize the next few functions to use. Similarly, a Forth veteran could visualize the series of Forth words to accomplish the above. Here is where the two philosophies of Forth and C can be "married". 

Besides the practical benefits (if achievable) mentioned above (use EAX as TOS), which we believe may greatly enhance cryptocurrency mining, amongst others, 5GL aims to improve the productivity of the younger generation of programmers, by showing them how to bridge their "native" programming languages with the Reverse Polish Notation / Stack Machine programming.

Hand tune optimization?

If we look at se.s (gcc -S se.c) lines 52 to 61, we can easily spot that lines 53 and 54 are redundant. Removing them may result in 25% time saving, at least theoretically!! This is what we hope to achieve by making EAX=TOS.

https://github.com/udexon/5CSM/blob/master/se.s
call	s_strcspn
movl	%eax, -284(%rbp)
movl	-284(%rbp), %eax
subl	$1, %eax
movslq	%eax, %rdx
movq	-280(%rbp), %rcx
leaq	-272(%rbp), %rax
movq	%rcx, %rsi
movq	%rax, %rdi
call	strncpy@PLT
