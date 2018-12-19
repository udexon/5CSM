#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct clVect { 
int dimension;
int *size;
int *V;
};

struct node
{
    int data; // data or pointer
    int type;
    struct node* next;
};


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


extern struct f_node *head;
extern struct f_node *tmp;

void f_display(struct f_node *head);

void f_init(struct f_node **phead) // need pointer to pointer to change value of pointer?
{
    *phead = NULL;
}

#define printType(a) printf("%s", _Generic( (a) , int : "int", long : "long", float : "float", default : "other type"))

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

struct f_node *f_dup(struct f_node *head) // ,union body *b, int type)
{

//    struct f_node *tmp = (struct f_node *) malloc(sizeof(struct f_node));

    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?

    // use extern
    tmp = (struct f_node *) malloc(sizeof(struct f_node));

    printf("   f_dup 204 %p    ", tmp);

    if(tmp == NULL)
    {
        exit(0);
    }

    memcpy((struct f_node *) tmp, (struct f_node *) head, sizeof(struct f_node));
    // f_dup: read TOS f_tos, f_push? or duplicate without knowing type?
    
    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?
    return headp;
}

#ifdef F_DBG
struct f_node *f_vmalloc(struct f_node *head) // assume input is TOS; use f_dup as template
{

    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?

    // use extern
    tmp = (struct f_node *) malloc(sizeof(struct f_node));
    // memcpy(tmp, head, sizeof(struct f_node)); // crashed if tmp has undefined pointers
    // program will run normally until the undefined pointer is accessed by f_display

    struct clVect *VA;
    VA =  (struct clVect *) malloc(sizeof(struct clVect));

    printf("\n   f_vmalloc 233 TOS %d sizeof TOS %d sizeof VA %d   ", head->b->i, sizeof(head->b->i), sizeof(VA));

    if(tmp == NULL)
    {
        exit(0);
    }

    memcpy((struct f_node *) tmp, (struct f_node *) head, sizeof(struct f_node));

    int VS[1];

    VA->dimension = 1; VA->size = VS; VS[0]=head->b->i;
    VA->V = (int *) malloc(sizeof(int)*VA->size[0]);
    tmp->b->p = (struct clVect *) VA; // affects other stack item when undefined?
    // tmp->type = 1;
    // f_dup: read TOS f_tos, f_push? or duplicate without knowing type?
    
    // tmp->data = data;
    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    return headp;
}

struct f_noded *f_vmallocd(struct f_noded *head) // assume input is TOS; use f_dup as template
{

    int type; union body *b;

    struct f_noded *headp = head; // local write to pointer?
    struct f_noded *tmp;

    // use extern
    tmp = (struct f_noded *) malloc(sizeof(struct f_noded));
    // memcpy(tmp, head, sizeof(struct f_node)); // crashed if tmp has undefined pointers
    // program will run normally until the undefined pointer is accessed by f_display

    struct clVect *VA;
    VA =  (struct clVect *) malloc(sizeof(struct clVect));

    printf("\n   f_vmalloc 233 TOS %d sizeof TOS %d sizeof VA %d   ", head->b.i, sizeof(head->b.i), sizeof(VA));

    if(tmp == NULL)
    {
        exit(0);
    }

    memcpy((struct f_noded *) tmp, (struct f_noded *) head, sizeof(struct f_noded));

    int VS[1];

    VA->dimension = 1; VA->size = VS; 

    VS[0]=head->b.i; // this is pop

    VA->V = (int *) malloc(sizeof(int)*VA->size[0]);
    tmp->b.p = (struct clVect *) VA; // affects other stack item when undefined?
    tmp->type = 1;
    // f_dup: read TOS f_tos, f_push? or duplicate without knowing type?
    
    // tmp->data = data;
    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    return headp;
}
#endif


struct f_node *f_pop(struct f_node *head);

struct f_node *f_A2V(struct f_node *head) // copy C array to clVect
{

    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    tmp = head->next; // clVect, next = below TOS

    struct clVect *VA;
    VA = (struct clVect *) tmp->b.p;

    int *VS0=VA->size;

    int *VB; VB=head->b.p; // TOS=array

    printf("\n   f_A2V 375 TOS  VB[4] %d   sizeof TOS %d sizeof VA %d   ", VB[4], sizeof(head->b.i), sizeof(VA));

    printf("   tmp %p  head %p  VA size %d   ", tmp, head, VS0[0] );
    printf("\n head next b p %p   VA %p   ", head->next->b.p, VA);

    memcpy(VA->V, VB, VS0[0]*sizeof(int));

    struct clVect *VX=(struct clVect *) (tmp->b.p);
    int *VY=VX->V;
    printf("\n   f_A2V 375 TOS  VY[3] %d %d %d   sizeof TOS %d sizeof VA %d   ", VB[3], VA[3], VY[3], sizeof(head->b.i), sizeof(VA));

    int j; for (j=0; j<VS0[0]; j++) printf("%d ", VY[j]);

    free(headp); headp=tmp; // pop

    return headp;

    if(tmp == NULL)
    {
        exit(0);
    }
    else printf(" %p ", tmp);

    // memcpy((struct f_noded *) tmp, (struct f_noded *) head, sizeof(struct f_noded));

    int VS[1];

    VA->dimension = 1; VA->size = VS; 

    VS[0]=head->b.i; // this is pop

    VA->V = (int *) malloc(sizeof(int)*VA->size[0]);
    tmp->b.p = (struct clVect *) VA; // affects other stack item when undefined?
    tmp->type = 1;
    // f_dup: read TOS f_tos, f_push? or duplicate without knowing type?

    printf(" %p ", tmp->b.p);

    headp=f_pop(headp);
    f_display(headp);

    // tmp->data = data;
    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    return headp;
}

struct f_node *f_A2Vx(struct f_node *head) // copy C array to clVect, no pop array 
{

    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    // use extern
    // tmp = (struct f_noded *) malloc(sizeof(struct f_noded));
    tmp = head->next;
    // memcpy(tmp, head, sizeof(struct f_node)); // crashed if tmp has undefined pointers
    // program will run normally until the undefined pointer is accessed by f_display

    struct clVect *VA;
    // VA =  (struct clVect *) malloc(sizeof(struct clVect));
    VA = (struct clVect *) tmp->b.p;

    int *VS0=VA->size;

    int *VB; VB=head->b.p;

    printf("\n   f_A2V 375 TOS  VB[4] %d   sizeof TOS %d sizeof VA %d   ", VB[4], sizeof(head->b.i), sizeof(VA));

    printf("   tmp %p  head %p  VA size %d   ", tmp, head, VS0[0] );
    printf("\n head next b p %p   VA %p   ", head->next->b.p, VA);

    memcpy(VA->V, VB, VS0[0]*sizeof(int));

    struct clVect *VX=(struct clVect *) (tmp->b.p);
    int *VY=VX->V;
    printf("\n   f_A2V 375 TOS  VY[3] %d %d %d   sizeof TOS %d sizeof VA %d   ", VB[3], VA[3], VY[3], sizeof(head->b.i), sizeof(VA));

    int j; for (j=0; j<VS0[0]; j++) printf("%d ", VY[j]);

    return headp;

    if(tmp == NULL)
    {
        exit(0);
    }
    else printf(" %p ", tmp);

    // memcpy((struct f_noded *) tmp, (struct f_noded *) head, sizeof(struct f_noded));

    int VS[1];

    VA->dimension = 1; VA->size = VS; 

    VS[0]=head->b.i; // this is pop

    VA->V = (int *) malloc(sizeof(int)*VA->size[0]);
    tmp->b.p = (struct clVect *) VA; // affects other stack item when undefined?
    tmp->type = 1;
    // f_dup: read TOS f_tos, f_push? or duplicate without knowing type?

    printf(" %p ", tmp->b.p);

    headp=f_pop(headp);
    f_display(headp);

    // tmp->data = data;
    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    return headp;
}

struct f_node *f_dupV(struct f_node *head, struct clVect *VA) // dup clVect
{

    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    tmp = (struct f_node *) malloc(sizeof(struct f_node));

    if(tmp == NULL)    {        exit(0);      }

    memcpy((struct f_node *) tmp, (struct f_node *) head, sizeof(struct f_node));

    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    printf("\n\n   f_dupV 507 headp %p  tmp %p  VA %p ", headp, tmp, VA);

    struct clVect *VB=(struct clVect *) headp->next->b.p; // source is next

    // printf("\n   FD 517 %d ", VB->dimension);
    printf("\n   FD 517 %p %p ", headp, headp->next);

    int *VS0=VB->size;

    int *VAS, *VBS;

    printf("\n   f_dupV 528 TOS  VS0[0] %d   VB->dimension %d    sizeof VA %d   ", VS0[0], VB->dimension, sizeof(VA));

    printf("   tmp %p  head %p  VA size %d   ", tmp, head, VS0[0] );
    printf("\n head next b p %p   VA %p  VA->V %p   VB->V %p ", head->next->b.p, VA, VA->V, VB->V);

    memcpy(VA, VB, sizeof(struct clVect)); 

    VA->V = (int *) malloc(sizeof(int)*VS0[0]);

    memcpy(VA->V, VB->V, VS0[0]*sizeof(int));

    VAS=VA->size; VBS=VB->size;

    printf("\n\n   f_dupV 542 headp %p  tmp %p  VA %p   VAS %d   VBS %d   ", headp, tmp, VA, VAS[0], VBS[0]);

    headp->b.p=VA;

    return headp;


    struct clVect *VX=(struct clVect *) (tmp->b.p);
    int *VY=VX->V;
    printf("\n   f_dupV 375 TOS  VY[3] %d %d %d   sizeof TOS %d sizeof VA %d   ", VB[3], VA[3], VY[3], sizeof(head->b.i), sizeof(VA));

    int j; for (j=0; j<VS0[0]; j++) printf("%d ", VY[j]);

    return headp;

}


struct f_node *f_addV(struct f_node *head) // struct clVect *VA) // dup clVect
{

    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    printf("\n\n   f_addV 597 "); // %p   %p ", tmp, VA);

    struct clVect *VB=(struct clVect *) headp->b.p; // source is next
    struct clVect *VA=(struct clVect *) headp->next->b.p; 
    
    printf("\n   FD f_addV 615 %p %p    VA %p   VB %p   ", headp, headp->next, VA, VB);

    int *VS0=VB->size;

    printf("\n   f_dupV 528 TOS  VS0[0] %d   VB->dimension %d    sizeof VA %d   ", VS0[0], VB->dimension, sizeof(VA));

    printf("   tmp %p  head %p  VA size %d   ", tmp, head, VS0[0] );
    printf("\n head next b p %p   VA %p  VA->V %p   VB->V %p ", head->next->b.p, VA, VA->V, VB->V);

    int *VX=VA->V; int *VY=VB->V;
    printf("\n   f_addV 644   VX[3] %d %d %d   sizeof TOS %d sizeof VA %d   ", VX[3], VY[3], VY[3], sizeof(head->b.i), sizeof(VA));

    int j; for (j=0; j<VS0[0]; j++) { VX[j]=VX[j]+VY[j]; printf("%d %d   ", VX[j], VY[j]); }

    return headp;

}


struct f_node *f_fillV(struct f_node *head) // fill clVect from 0 to N-1
{
    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    tmp = head;

    struct clVect *VA = (struct clVect *) tmp->b.p;

    int *VS0=VA->size;

    int *VB; VB=head->b.p;

    printf("\n\n   f_fillV 704 "); // TOS  VB[4] %d   sizeof TOS %d sizeof VA %d   ", VB[4], sizeof(head->b.i), sizeof(VA));

    printf("   tmp %p  head %p  VA size %d   ", tmp, head, VS0[0] );
    printf("\n head next b p %p   VA %p   ", head->next->b.p, VA);

    struct clVect *VX=(struct clVect *) (tmp->b.p);
    int *VY=VX->V;
    printf("\n   f_tosV 375 TOS  VY[3] %d %d %d   sizeof TOS %d sizeof VA %d   ", VB[3], VA[3], VY[3], sizeof(head->b.i), sizeof(VA));

    int j; for (j=0; j<VS0[0]; j++) { VY[j]=j; printf("%d ", VY[j]); }

    return headp;

    if(tmp == NULL)
    {
        exit(0);
    }
    else printf(" %p ", tmp);

    int VS[1];

    VA->dimension = 1; VA->size = VS; 

    VS[0]=head->b.i; // this is pop

    VA->V = (int *) malloc(sizeof(int)*VA->size[0]);
    tmp->b.p = (struct clVect *) VA; // affects other stack item when undefined?
    tmp->type = 1;

    printf(" %p ", tmp->b.p);

    headp=f_pop(headp);
    f_display(headp);

    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    return headp;
}


struct f_node *f_tosV(struct f_node *head) // struct clVect *VA) // dup clVect
{
    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    tmp = head;

    struct clVect *VA = (struct clVect *) tmp->b.p;

    int *VS0=VA->size;

    int *VB; VB=head->b.p;

    printf("\n\n   f_tosV 699 "); // TOS  VB[4] %d   sizeof TOS %d sizeof VA %d   ", VB[4], sizeof(head->b.i), sizeof(VA));

    printf("   tmp %p  head %p  VA size %d   ", tmp, head, VS0[0] );
    printf("\n head next b p %p   VA %p   ", head->next->b.p, VA);

//    memcpy(VA->V, VB, VS0[0]*sizeof(int));

    struct clVect *VX=(struct clVect *) (tmp->b.p);
    int *VY=VX->V;
    printf("\n   f_tosV 375 TOS  VY[3] %d %d %d   sizeof TOS %d sizeof VA %d   ", VB[3], VA[3], VY[3], sizeof(head->b.i), sizeof(VA));

    int j; for (j=0; j<VS0[0]; j++) printf("%d ", VY[j]);

    return headp;

}


struct f_node *f_vmallocpop(struct f_node *head, struct clVect **pVA) // assume input is TOS; use f_dup as template
{
    // need input variable so that memory allocated is preserved after function exits.
    int type; union body *b;

    struct f_node *headp = head; // local write to pointer?
    struct f_node *tmp;

    // use extern
    tmp = (struct f_node *) malloc(sizeof(struct f_node));
    // memcpy(tmp, head, sizeof(struct f_node)); // crashed if tmp has undefined pointers
    // program will run normally until the undefined pointer is accessed by f_display

    struct clVect *VA;
    VA =  (struct clVect *) malloc(sizeof(struct clVect)); // destroyed upon exit?
    *pVA=VA;

    printf("\n   f_vmallocpop 327 TOS %d sizeof TOS %d sizeof VA %d   ", head->b.i, sizeof(head->b.i), sizeof(VA));

    if(tmp == NULL)
    {
        exit(0);
    }
    else printf(" %p ", tmp);

    memcpy((struct f_node *) tmp, (struct f_node *) head, sizeof(struct f_node));

    int VS[1];

    VA->dimension = 1; VA->size = VS; 

    VS[0]=head->b.i; // this is pop

    VA->V = (int *) malloc(sizeof(int)*VA->size[0]);
    tmp->b.p = (struct clVect *) VA; // affects other stack item when undefined?
    tmp->type = 1;

    printf(" %p    size %d   ", tmp->b.p, VA->size[0]);

    headp=f_pop(headp);
    f_display(headp);

    tmp->next = headp; // head was TOS, now tmp is TOS, head is NULL when it was sole item on stack?
    headp = tmp; // headp destroyed upon exit? but value saved?

    return headp;
}
  

struct f_node *f_pop(struct f_node *head) //, union body *b, int type)
{
    struct f_node *tmp=head;

    printf("\n  f_pop 301\n");  

    printf("  f_pop 271 %p\n", head);  

    head = head->next;

    printf("  f_pop 275 %p %p\n", head, tmp);  

    free(tmp);

    printf("  f_pop 272\n");  

    return head;
}


#ifdef F_DBG
struct f_node *f_tos(struct f_node *head, union body *b) // , int type)
{

    // use extern
    tmp = head;

    printf("\n\n  f_tos 335 type%d\n\n", head->type);  

    if (head->type==0) (*b).i = head->b->i;
    else { 
	
	printf("  f_tos 340 %s   \n\n", head->b->p);  
	strcpy((*b).p, head->b->p);
	// free(head->b->p); 
	printf("  f_tos 343 %s   \n\n", (*b).p); 

    }

    return head;
}
#endif 

/*
    returns 1 if the stack is empty, otherwise returns 0
*/
int f_empty(struct f_node* head)
{
    return head == NULL ? 1 : 0;
}

    
void f_display(struct f_node *head)
{

	printf("\n\n   f_display 607 %p   ", head);

    struct f_node *current;
    current = head; // printf("   f_display 491 %p   ", current);
    if(current!= NULL)
    {
        printf("  Stack: ");
        do
        {
	    printf("\n   f_display 624 %p   ", current);

            if (current->type==0) printf("   f_display 626 %d %d   ", current->type, (int) current->b.i);
            else printf("   f_display 627 %d %p   ", current->type,  (void *) current->b.p  );
            
            // current->data.i );
            current = current->next;
        }
        while (current!= NULL);
        printf("\n");
    }
    else
    {
        printf("The Stack is empty\n");
    }

}
    
    
