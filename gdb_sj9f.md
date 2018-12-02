(gdb) r < jfc.f
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/hongwu/devel/5gl/asm/5CSM/sj9f < jfc.f
7    123��t�������
7 9 11 13 15

Breakpoint 2, mod_array1 () at sj.c:25
25	mod_array1() {
(gdb) fin
Run till exit from #0  mod_array1 () at sj.c:25
1 2 3 4 5
main () at sj.c:58
58	    _start1(FDSEG);
Value returned is $4 = 0
(gdb) c
Continuing.

Breakpoint 1, _start1 () at jonesforth9f.S:567
567		pushl %ebp		// called from C, save ebp, how to monitor these?
(gdb) fin
Run till exit from #0  _start1 () at jonesforth9f.S:567
JONESFORTH VERSION 47 
32843 CELLS REMAINING
OK 3 
Breakpoint 3, f_ret () at jonesforth9f.S:730
730		popl %esi		// 9f mod
(gdb) bt
#0  f_ret () at jonesforth9f.S:730
#1  0xf7faa000 in ?? () from /lib/i386-linux-gnu/libc.so.6
Backtrace stopped: previous frame inner to this frame (corrupt stack?)
