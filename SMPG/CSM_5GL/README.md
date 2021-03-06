### Stack Machine Parser Generator

(2019-01-09 2010 MYT)

This example illustrates how Forth style colon definition can be used "rename" blocks of code of high level programming langauge (e.g. C/C++), thus making it more legible, structured and manageable.

The original [post](https://groups.google.com/forum/#!topic/comp.lang.forth/cAZURahAnzg) appeared on comp.lang.forth newsgroup.

The [following is the output](https://github.com/udexon/5CSM/blob/master/SMPG/o_blocks) of cparse.php (will be uploaded after clean-up), a C parser written in PHP. It uses one simple rule: look for '{' and '}' as start and end markers, output block label as B_startline_startcol_endline_endcol. Each line starts with the line number, followed by the column number of either '{' or '}'. The number following IN_IF is the nest level of the block.

The input example is taken from https://github.com/supernovaremnant/bazel-android-opencl/blob/master/opencl-info/opencl-info.cc

Even with such a simple example, it shows that the code can quickly grow unintelligible, due to fundamental flaws in the design of high level programming languages.

The next step for cparser.php will be to provide the Forth style colon definition to "rename" the block labels B_* -- to give a legible name, to give it more meaning, structure and make in more manageable.

In the following example, which we call "parses map",

- `S_*`: simple statements ending with ;
- `B_*`: blocks
- `C_*`: conditions
- the numbers following _ are line and column respectively.

```
S_193_39 S_194_19 S_195_62 S_198_18 S_199_42 S_200_29 S_202_21 

C_203_3 if B_203_28_206_0  
else B_206_7_296_0 

S_300_30 S_301_17 S_302_23 S_303_14 S_305_20 S_307_48 
S_310_42 S_313_40 S_314_15 S_316_15 

C_339_6  do B_317_3_338_0  

S_340_27 S_343_40 S_344_20 S_346_32 S_349_36 
```

After parsing into 5GL, a 300 plus line C++ program looks much more intelligible. One may use Forth style colon definition to represent blocks of S_* statements to make it even more compact. These labels may be renamed using additional colon definitions.

Let us continue with Forth style colon definition to give the statements and blocks more meaningful names:

```
: init_setup S_193_39 S_194_19 S_195_62 S_198_18 S_199_42 S_200_29 S_202_21 ;
: get_platformid_fail C_203_3 ;
: fail_message B_203_28_206_0 ;
: get_platform_info B_206_7_296_0 ;
: get_cpuinfo S_300_30 S_301_17 S_302_23 S_303_14 S_305_20 S_307_48 
S_310_42 S_313_40 S_314_15 S_316_15 ;
: eof_cpuinfo C_339_6 ;
: cpu_stream B_317_3_338_0 ;
: end_message ;
```
Now the 5GL code can be rewritten as:

```
init_setup

get_platformid_fail if fail_message 
else get_platform_info 

get_cpuinfo 

eof_cpuinfo do cpu_stream 

end_message 
```


Please note that the 5GL code above is not just cosmetic (informative) but actually "functional". They can be mapped back the original C/C++ source code, via the Forth style colon definition, as well as the initial "parse map" (comprising line and column numbers for Statements, Blocks and Conditions).

Further, the reverse mapping to C/C++ source code can be used for two purposes:

i. editing source code

ii. executing sections of code in interpreter mode

Both facilities are well established features of the Forth  programming environment. This can now be used in C/C++ as well as other similar high level programming languages.
