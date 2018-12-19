``` $ gcc -o smocl *.c -l OpenCL ```

Original: https://github.com/smistad/OpenCL-Getting-Started

Here is my prototype for SMOCL (Stack Machine OpenCL) written in C:

https://github.com/udexon/5CSM/blob/master/SMOCL/README.md

SMOCL is derived from the Multitiered Stack Machine (nSM) as described in:

https://www.linkedin.com/pulse/multitiered-stack-machine-nsm-using-5gl-fifth-graph-ng-ph-d-/

http://5gl.epizy.com/nsm/fgl.html

nSM simply means "a stack machine within a stack machine .... (repeat up to N times)" . It is so named because the initial implementations of nSM are coded in PHP and JavaScript, whose interpreters are themselves stack machines.

nSM was created around July 2018 as a hobby project to implement a Forth like system which accepts reverse Polish notation, with the aim to enable the programmer (myself) to develop simple web applications on the mobile phone itself, as conventional programming languages are to cumbersome to be used on mobile devices,  primarily due to the use of brackets and exotic symbols. 

LISP was ruled out in preference of RPN, initially simply due to a "nerdy" feel about Forth and comp.lang.forth posts. Eventually, as I dug deeper into Forth and LISP, more interesting properties concerning programming languages were discovered. 

Since July 2018, nSM evolved slowly, as I could only work on it during my spare time. It took about a year to reach its current "stable" form, after the fundamental data structures were simplified to their barest forms and conditional branches were implemented. It is now around 50 lines of PHP or JavaScript code, which mainly does 3 things: 

-- push input tokens on to the stack,
-- map input tokens to host functions (PHP or JavaScript) and
-- handles conditional branches.

I was amazed how simple nSM has become, or perhaps I should say I am awed by the how simple a stack machine should be.

I also coined the name Inverse Shunting Yard Algorithm (ISYA) to describe the operations of nSM, as the inverse of Dijkstra's now legendary Shunting Yard Algoritm (DSYA). In my not so humble opinion, ISYA might be the most significant algorithm since DSYA itself -- as it can potentially "unify" ALL programming languages: Programmers need only to write programs in Forth-like reverse Polish notation; using nSM, the program written in RPN is translated into the host programming language and executed. This has an immense implication on beginners learning programming languages, as well as large team using RPN to consolidate codes written in multiple programming languages.

The implementation of RPN for nSM is called 5GL, the Fifth Generation Graph Language, as a pun to Forth.

Besides "unifying" all programming languages, 5GL may also serve as a platform for "stack machine opcode interchange" (SMOPINT) -- as most popular programming languages today actually employ stack machine as interpreter. Is it possible to create a translation layer so that stack machine opcode (SMOP) in one programming language (e.g. PHP) can be executed by the interpreter of another programming language (e.g. JavaScript)?

SMOCL (Stack Machine OpenCL) illustrates some more urgent, practical and interesting issues concerning SMOPINT. These issues include: What are the essential differences between a Forth program and a C program?

A simple problem illustrates the glaring problem concerning Forth and C programming: How do you call a C function from Forth and vice versa?

Unlike other programming languages, age and experience matter when it comes to discussion concerning Forth, as it has a significant following, with the most senior (age) programmers and experts, who recently celebrated Forth's 50th anniversary in the Euroforth 2018 conference. I started using BASIC and Pascal during my teens in 1980s in developing Malaysia, Linux in the UK while at university. I worked on artificial intelligence and computer vision mostly. Somehow I managed to miss Forth until about the second half of 2017.

After about of year hanging out on comp.lang.forth, perhaps the last active Usenet newsgroup, and more recently on Forth Facebook groups, this is how I view Forth and Forth programmers:

(1) There might be a significant number of commercial Forth projects that are rarely mentioned in comp.lang.forth or elsewhere, whose implementation may include Forth-C interface, which is not disclosed.

(2) There are many Forth implementations, whose number of followers or users are unknown. As such, their Forth-C interface is unknown due to lack of documentation.

(3) GNU Forth is perhaps the largest open source Forth. Unfortunately, the number of contributors who are actively contributing to forums is also unclear. The popularity of GForth C interface is also unknown.

So non-Forth programmers may ask, am I wasting my time working on a programming language that seems to be poorly documented on critical areas, such as OpenCL?

So the above is a long winded background to SMOCL. I believe it is necessary as the readers will discover as I explain SMOCL in depth.

