``` $ gcc -o smocl *.c -l OpenCL ```

Original: https://github.com/smistad/OpenCL-Getting-Started

Here is my prototype for SMOCL (Stack Machine OpenCL) written in C:

https://github.com/udexon/5CSM/blob/master/SMOCL/README.md

## What is NOT a stack machine?

  - _ALL programs or functions can be represented as reverse Polish notation and executed by a stack machine._

  - _The reverse Polish notation is simply THE simplest notation to represent ANYTHING mathematically._

### Introduction

SMOCL (Stack Machine OpenCL) is derived from the Multitiered Stack Machine (nSM) as described in:

https://www.linkedin.com/pulse/multitiered-stack-machine-nsm-using-5gl-fifth-graph-ng-ph-d-/

http://5gl.epizy.com/nsm/fgl.html

nSM simply means "a stack machine within a stack machine .... (repeat up to N times)" . It is so named because the initial implementations of nSM are coded in PHP and JavaScript, whose interpreters are themselves stack machines.

nSM was created around July 2018 as a hobby project to implement a Forth like system which accepts reverse Polish notation, with the aim to enable the programmer (myself) to develop (write code and test!) simple web applications on the mobile phone itself, as conventional programming languages are too cumbersome to be used on mobile devices,  primarily due to the use of brackets and exotic symbols. 

LISP was ruled out in preference of RPN, initially simply due to a "nerdy" feel about Forth and comp.lang.forth posts. Eventually, as I dug deeper into Forth and LISP, more interesting properties concerning programming languages were discovered. 

Since July 2018, nSM evolved slowly, as I could only work on it during my spare time. It took about a year to reach its current "stable" form, after the fundamental data structures were simplified to their barest forms and conditional branches were implemented. It is now around 50 lines of PHP or JavaScript code, which mainly does 3 things: 

- pushes input tokens on to the stack,
- maps input tokens to host functions (PHP or JavaScript) and
- handles conditional branches.

I was amazed how simple nSM has become, or perhaps I should say I am awed by how simple a stack machine should be.

I also coined the name Inverse Shunting Yard Algorithm (ISYA) to describe the operations of nSM, as the inverse of Dijkstra's now legendary Shunting Yard Algoritm (DSYA). In my not so humble opinion, ISYA might be the most significant algorithm since DSYA itself -- as it can potentially "unify" ALL programming languages: Programmers need only to write programs in Forth-like reverse Polish notation; using nSM, the program written in RPN is translated into the host programming language and executed. This has immense implications on beginners learning programming languages, as well as large teams, as using RPN helps to consolidate codes written in multiple programming languages.

The version of RPN for nSM is called 5GL, the Fifth Generation Graph Language, as a pun to Forth.

Besides "unifying" all programming languages, 5GL may also serve as a platform for "stack machine opcode interchange" (SMOPINT) -- as most popular programming languages today actually employ stack machine as interpreter: PHP, JavaScript, Java, Python, Ruby, .... Is it possible to create a translation layer so that stack machine opcodes (SMOP) in one programming language (e.g. PHP) can be executed by the interpreter of another programming language (e.g. JavaScript)? It does not seem to be an overtly complicated task after you spend a few days studying examples given in this article.

SMOCL (Stack Machine OpenCL) illustrates some of the more urgent, practical and interesting issues concerning SMOPINT. These issues include: What are the essential differences between a Forth program and a C program?

A simple problem illustrates one glaring problem concerning Forth and C programming: How do you call a C function from Forth and vice versa?

Unlike other programming languages, age and experience matter when it comes to discussion concerning Forth, as it has a significant following, with the most senior (age) programmers and experts, who recently celebrated Forth's 50th anniversary in the Euroforth 2018 conference. I started using BASIC and Pascal during my teens in 1980s in developing Malaysia, Linux in the UK while at university. I worked on artificial intelligence and computer vision mostly. Somehow I managed to miss Forth until about the second half of 2017.

After about a year of hanging out on comp.lang.forth, perhaps the last active Usenet newsgroup, and more recently on Forth Facebook groups, this is how I view Forth and Forth programmers:

(1) There might be a significant number of commercial Forth projects that are rarely mentioned in comp.lang.forth or elsewhere, whose implementation may include Forth-C interface, which is not disclosed.

(2) There are many Forth implementations, whose number of followers or users are unknown. As such, their Forth-C interface is unknown due to lack of documentation.

(3) GNU Forth is perhaps the most popular open source Forth. Unfortunately, the number of contributors who are actively contributing to forums is also unclear. The popularity of GForth C interface is also unknown.

So non-Forth programmers may ask, am I wasting my time working on a programming language that seems to be poorly documented on critical areas, such as OpenCL?

The main motivation lies in mobile GPU cryptocurrency mining. By rejecting OpenCL, Google has caused a huge unfortunate side effect -- tens of millions if not hundred of millions of Android mobile phone with GPU effectively become underutilized. SMOCL is a project to bridge the gap using stack machine methodologies, to utilize the hundred of millions of GPU in Android phones, especially for cryptocurrency mining. SMOCL will provide the much needed Forth-like interactive development enviroment to develop cryptocurrency mining programs ON THE MOBILE DEVICE ITSELF, as well as potential novel optimization schemes, as described below.

So the above is a long winded background on SMOCL. I believe it is necessary as the readers will discover as I explain SMOCL in depth.


### Assembly Forth vs. C Forth

Here is a link which I believe is one of the most important reference for non-Forth programmers to understand Forth: a collection of Forth systems written in C:

http://uwiki.strotmann.de/view/forth-implemented-in-cc

Forth has such a long history that it would be unfair to say that a certain topic has not been documented. Yet some of the most important work and documentation predated the Internet. Although the number of programmers worldwide increased dramatically along with the growth the Internet and mobile phone usage, Forth popularity remained relatively low as younger programmers are seduced by "propaganda" accompanying the currently popular programming languages. In absolute terms, the number of Forth programmers worldwide might be increasing, as the older Forth programmers may not disappear so quickly as yet (sorry!), touch wood, and we do not have sufficient statistics or mechanism to collect such statistics, yet, although one potential application of nSM would be a Unified Collaborative Programming Environment (UCPE), where nSM can be run on millions of mobile devices and data centre hosts collaboratively using one Universal Stack Machine Language (USML), to create truly distributed Cloud / Fog services that does not have a single point of ownership . 

A new comer to Forth may find [jonesforth](https://github.com/nornagon/jonesforth/blob/master/jonesforth.S) the de facto introduction to Forth internals, against which some older Forthers have expressed their opinions concerning their preferences.

A study of jonesforth and some C Forths given above, together with the [C calling jonesforth example](https://github.com/udexon/5CSM/blob/master/Progress_20181203.md) in this repository should give readers sufficient background knowledge to investigate SMOCL.

SMOCL began as an implementation of [nSM](http://5gl.epizy.com/nsm/fgl.html) in C, where the original ISYA (Inverse Shunting Yard Algorithm) was written in PHP. The first stumbling block would be the stack itself: in PHP, pushing a item on to the stack is simply `$S[] = 'a token';` . However, the following code is required in [SMOCL](https://github.com/udexon/5CSM/blob/master/SMOCL/linkedstack.c):

```
union body 
{
    void *p;
    long int i;
};

struct f_node
{
    // int data; // data or pointer
    union body b;
    int type;
    struct f_node *next;
};

/*
    push an element onto stack
*/
struct f_node *f_push(struct f_node *headd, union body *b, int type)
{

//    struct f_node *tmp = (struct f_node *) malloc(sizeof(struct f_node));

    struct f_node *headp = headd; // local write to pointer?
    struct f_node *tmp;
    // use extern
    tmp = (struct f_node *) malloc(sizeof(struct f_node));

    printf("\n   f_pushd 217 %p    ", tmp);

    if(tmp == NULL)
    {
        exit(0);
    }
    
    if (type==1) { printf("   f_pushd 224 %p    ", (*b).p);
    
	tmp->b = *b;
    // tmp->b->p=malloc(strlen((*b).p)+1);
    // strcpy(tmp->b->p, (*b).p); // cannot assign? must copy?
    tmp->type=1;
    }
    else { // tmp->b->i = (*b).i;
        tmp->b = *b;
        printf("    f_pushd 233 i %d tmp b i %d __  ", (*b).i, tmp->b.i);
        tmp->type=0;
    }
    
    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?
    return headp;
}
```

Readers who are familiar with Forth written in C may ask -- are you reinventing the wheel?

Yes and No. Most of the C Forth systems that I have reviewed seems to have one common goal: to execute Forth programs (in RPN).

However, as stated above, nSM has a different goal: to map 5GL functions (equivalent to Forth words) to native C functions.

Then some readers may ask: can that not be done in any of the C Forth? Perhaps, but I suspect additional data structure might hinder this objective.

In short SMOCL/nSM is a compiler / interpreter to translate Forth-like (RPN) programs into native C functions.

Currently, [SMOCL stack machine functions `f_*()`](https://github.com/udexon/5CSM/blob/master/SMOCL/smocl.c) (line 78) are invoked using plain C syntax, as the RPN parser is being developed:

```
int FD() // use f_node
{
	headd=(struct f_node *) NULL;
	f_display(headd);

	union body i; i.i = 230;
	headd=(struct f_node *) f_push(headd, &i, 0);
	f_display(headd);

	i.i = 5;
	headd=(struct f_node *) f_push(headd, &i, 0);
	f_display(headd);
	
	....
```
The [original example of the OpenCL code](https://github.com/smistad/OpenCL-Getting-Started) adds 2 vectors of length 1024. 

In SMOCL, a vector of length 1024 is created ([`f_vmallocpop()` line 153](https://github.com/udexon/5CSM/blob/master/SMOCL/smocl.c)), filled with integers from 0 to 1023 (`f_fillV()`). `f_dupV()` is called to duplicate the vector. Finally `SMOCL1b()` is called to add the two vectors.

Here are several areas concerning the differences of C programs vs. Forth programs:

1. The stack machine mechanism in Forth makes it possible to create an interactive development environment. With SMOCL or 5CSM (5GL C Stack Machine), similar interactive development environment for C can be created, providing huge benefits to cryptocurrency as well as other applications.

2. The reverse Polish notation can be used to create a Universal Stack Machine Language (USML) so as to unify all programming languages including C.

3. The very core of GCC optimization engine is based on RTL, itself a stack machine. 

As such, Forth code optimization is a manual process, while C code optimization is a black box, automated process based on algorithms written by compiler developers.

SMOCL or 5CSM can make C code optimization a manual process like Forth, opening up the black art of code optimization to a wider audience.


### What is NOT a stack machine?

The readers are invited to port nSM to other programming languages of your choice or work together to build SMOCL / 5CSM. 

As veteran Forthers used to say, implementing Forth yourself is an eye opener. nSM is a light weight, modern approach to the same discipline as Forth. 

When you actually do that, you will start to understand that the question "What is NOT a stack machine?" is not a sematic trick. It simply means **_all programs or functions can be represented as reverse Polish notation and executed by a stack machine_**. One of the proofs is the x86 instruction set:

`sub %ah, %al` — AL is set to AL - AH

which of course dated back to the old days of stack machine architecture of the 1960s.

In modern Intel or ARM microprocessors, there is this "virtually undocumented" proprietary "stack engine", which outside mortals like us can only assume they are stack machines.

Then you might say there is "register machine", which can be transformed into a stack machine almost trivially.

Where does this lead us?

Stack machine is only the portal into the bigger world of graph theory, which some believe to be the very foundation of mathematics. **_The reverse Polish notation is simply the simplest notation to represent ANYTHING mathematically._**

Consider the distributive law described in [this article](https://www.linkedin.com/pulse/learning-forth-2018-%E4%BC%8D%E6%A8%91%E7%9B%9B-%E5%8D%9A%E5%A3%AB-liang-ng-ph-d-/). How many lines of code would you need to implement the distributive law in other programming languages? The solution in RPN is almost trivial.

[HOL Light](https://www.cl.cam.ac.uk/~jrh13/hol-light/), based on LISP, is another good point of entry to the abstract world of mathematics. However, I believe Forth and RPN, which are homoiconic as with LISP, are closer to hardware, and thus more appealing to some programmers like myself. In any case, when you understand the fundamentals of stack machine, which I think you can achieve in one week by following examples given here, the differences between LISP and RPN are trivial, as there are more interesting problems to pursue.

(Additional references: [SageMath](http://www.sagemath.org/), [Python Sympy](https://www.sympy.org/en/index.html), [Maxima](http://maxima.sourceforge.net/).)
