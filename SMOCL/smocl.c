#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE (0x100000)

#define CLOK

#include <CL/cl.h>

struct clVect { 
int dimension;
int *size;
int *V;
} VA, VB;

union body {
    void *p;
    long int i;
};

struct f_node
{
    // int data; // data or pointer
    union body b;
    int type;
    struct f_node *next;
} *headd, *tmp, *head;

// 2018 12 11 5GL/RPN needs to operate on fundamental structure like below
// then build composite structure on it, or dive into more primitive structure?
// e.g. how to build pointer to array?


// need to declare all function prototype, else return value head will be wrong?
struct f_node *f_push(struct f_node *head,union body *b, int type);
// struct f_node *f_pop(struct f_node *head, union body *b, int type);
void f_display(struct f_node *head);
void f_init(struct f_node* head);

// 2018 12 12
struct f_node *f_dup(struct f_node *head); // ,union body *b, int type);
struct f_node *f_vmalloc(struct f_node *head); // must have function declaration, else seg fault!!

int f_type(char *s, union body *b)
{
	int n;
// has e/E (only 1 e/E); 
    // part2 all digits, has +/- (prefix no space); 
    // part 1 has +/- (trim leading space）only one . 
// else part 1 has +/- (trim leading space）only one . 
// else (char *)
n=strcspn(s, "eE");
printf("   f_type 43 %d   ", n);


// the output n can be put on stack for further processing. How? 
// put inputs (string and separator) on stack first
//  after processing, put output on stack
}

void f_display(struct f_node *head);
// struct f_noded *f_vmallocd(struct f_noded *head);
// struct f_noded *f_vmallocpop(struct f_noded *head);
struct f_node *f_vmallocpop(struct f_node *head, struct clVect **pVA);

struct f_node *f_A2V(struct f_node *head); // pop array
struct f_node *f_A2Vx(struct f_node *head); // no pop array
struct f_node *f_dupV(struct f_node *head, struct clVect *VA);
struct f_node *f_tosV(struct f_node *head); // , struct clVect *VA); // display TOS Vector
struct f_node *f_addV(struct f_node *head);
struct f_node *f_pop(struct f_node *head);
struct f_node *f_fillV(struct f_node *head);

int SMOCL1a(int **A, int **B);
int SMOCL1b(int *A, int *B);

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

	struct clVect *VC;
	VC=(struct clVect *) malloc(sizeof(struct clVect));

	// struct clVect *VD;

	// these operations should be done by f_vmalloc?
	VC->dimension=1;
	int VS[]={5};
	VC->size=VS;
	int *VCA;
	int *VCS=VC->size;

	printf( "\n   263 VC->size %d  VS[0] %d  \n", VCS[0], VS[0] );

	VCA = (int *) malloc(sizeof(int)*VCS[0]);
	VC->V=VCA;

	i.p=VC; // int *V declares pointer but memory not allocated
	headd=(struct f_node *) f_push(headd, &i, 1);
	f_display(headd);

	struct clVect *VD; VD=headd->b.p;
	printf( "\n   270 VD size %d   \n", VD->size[0] );

	// headd=(struct f_noded *) f_vmallocd(headd);
	// headd=(struct f_noded *) f_vmallocpop(headd);
	// f_displayd(headd);

	int V[]={ 0, 1, 2, 3, 4}; i.p=V; // int *V declares pointer but memory not allocated
	headd=(struct f_node *) f_push(headd, &i, 1);
	f_display(headd);

	int *VA; VA=(headd->b.p);
	printf("   FD 256 %d %d  ", VA[4], VA[2]);

	headd=f_A2V(headd);
	f_display(headd);

	// if dup VA, need to recursive malloc and memcpy?
	f_tosV(headd); // , VC);

	VD=(struct clVect *) malloc(sizeof(struct clVect));
	printf("\n\n   FD 309   VD %p    \n", VD);
	headd=f_dupV(headd, VD);
	f_display(headd);

	f_tosV(headd); // , VC);

	printf("\n\n   FD 315   VD %p    \n", VD);
	headd=f_addV(headd); f_tosV(headd); f_display(headd);

	headd=f_pop(headd); f_display(headd);

	f_tosV(headd); f_display(headd);

	headd=f_fillV(headd); 
	f_tosV(headd); f_display(headd);

	i.i = 1024;
	headd=(struct f_node *) f_push(headd, &i, 0);
	f_display(headd);

	headd=f_vmallocpop(headd, &VD); 

	printf("    FD 333   VC %p   VD %p   ", VC, VD);

	headd=f_fillV(headd); 
	f_tosV(headd); 
	f_display(headd);

	headd=f_dupV(headd, VC); // pass VC can change it?
	f_tosV(headd); 
	f_display(headd);

	int *VDS; // *VCS;

	VCS=VC->size; VDS=VD->size;

	printf("    FD 344   VC %p   VD %p   VCS %d   VDS %d ", VC, VD, VCS[0], VDS[0]);

	if (0) {
	int *A, *B;
	SMOCL1a(&A, &B);
	SMOCL1b(A, B);
	}

	SMOCL1b(VC->V, VD->V);

}



// int push(){}
int array(){}

char *strdup(const char *src)
{
    char *tmp = malloc(strlen(src) + 1);
    if(tmp)
        strcpy(tmp, src);
    return tmp;
}

void explode(const char *src, const char *tokens, char ***list, size_t *len)
{   
    if(src == NULL || list == NULL || len == NULL)
        return;

    char *str, *copy, **_list = NULL, **tmp;
    *list = NULL;
    *len  = 0;

    copy = strdup(src);

    fprintf(stderr, "%s %s\n", copy, src);

    if(copy == NULL)
        return;

    fprintf(stderr, "%s %s\n", copy, tokens);

    str = strtok(copy, tokens);

    fprintf(stderr, "%s %s\n", copy, str);

    if(str == NULL)
        goto free_and_exit;

    fprintf(stderr, "%s %s\n", copy, str);

    _list = realloc(NULL, sizeof *_list);
    if(_list == NULL)
        goto free_and_exit;

    _list[*len] = strdup(str);
    if(_list[*len] == NULL)
        goto free_and_exit;
    (*len)++;

    fprintf(stderr, "%s %s\n", copy, str);

    while((str = strtok(NULL, tokens)))
    {   
        tmp = realloc(_list, (sizeof *_list) * (*len + 1));
        if(tmp == NULL)
            goto free_and_exit;

        _list = tmp;

        _list[*len] = strdup(str);
        if(_list[*len] == NULL)
            goto free_and_exit;
        (*len)++;
    }


free_and_exit:
    *list = _list;
    free(copy);
}

// int SMOCL1a(void) {
int SMOCL1a(int **A, int **B) {

    int i;
    const int LIST_SIZE = 1024;
//    int *A = (int*)malloc(sizeof(int)*LIST_SIZE);
//    int *B = (int*)malloc(sizeof(int)*LIST_SIZE);
    *A = (int*)malloc(sizeof(int)*LIST_SIZE);
    *B = (int*)malloc(sizeof(int)*LIST_SIZE);
  
    for(i = 0; i < LIST_SIZE; i++) {
        (*A)[i] = i;
        (*B)[i] = LIST_SIZE - i;
    }
}

int SMOCL1b(int *A, int *B) {

    //  f_V2A (convert clVect to array) here for A[] B[]
    //  or f_array 1024 load into A[] B[]

    int i;
    const int LIST_SIZE = 1024;
 
    // Create the two input vectors
    /*
    int i;
    const int LIST_SIZE = 1024;
    int *A = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *B = (int*)malloc(sizeof(int)*LIST_SIZE); */
    for(i = 0; i < LIST_SIZE; i++) {
        printf("   %d %d   ", A[i], B[i]);
    }
    
    // return 0;
    
#ifdef CLOK
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("vector_add_kernel.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1, 
            &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
            LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    
    // Execute the OpenCL kernel on the list
    size_t global_item_size = LIST_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Process in groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), C, 0, NULL, NULL);

    // Display the result to the screen
    for(i = 0; i < LIST_SIZE; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(B);
    free(C);

#endif

// 2018 12 12 use top of stack 5 as input to malloc

    return 0;
}



int SMOCL(void) {
    // Create the two input vectors
    int i;
    const int LIST_SIZE = 1024;
    int *A = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *B = (int*)malloc(sizeof(int)*LIST_SIZE);
    for(i = 0; i < LIST_SIZE; i++) {
        A[i] = i;
        B[i] = LIST_SIZE - i;
    }

    
#ifdef CLOK
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("vector_add_kernel.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1, 
            &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
            LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    
    // Execute the OpenCL kernel on the list
    size_t global_item_size = LIST_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Process in groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), C, 0, NULL, NULL);

    // Display the result to the screen
    for(i = 0; i < LIST_SIZE; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(B);
    free(C);

#endif

// 2018 12 12 use top of stack 5 as input to malloc

    return 0;
}

int main(void) {

    int *A, *B;
    
    // SMOCL();
    SMOCL1a(&A, &B); // 2 in 2 out? put both on stack?
    // f_malloc, f_fill 0 to 1024?, then dup array? or use clVect?
    // need new function, fill array from 0 to N
    // then next function need to transfrom clVect to array?

    // head = f_(head, &A, &B); need parameters for malloc


    SMOCL1b(A, B);

    // head = f_(head); no need parameters, already on stack
    FD();
}



