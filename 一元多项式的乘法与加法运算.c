#include <stdio.h>
#include <stdlib.h>




typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef;
    int expon;
    Polynomial link;
    };
void Attach(int c,int e,Polynomial *prear);


Polynomial ReadPoly(){
    int n,c,e;
    Polynomial p,t,rear;

    scanf("%d",&n);
    p = (Polynomial)malloc(sizeof(struct PolyNode));/*链表头空节点*/
    p -> link = NULL;
    rear = p;
    while(n--)
    {
        scanf("%d %d",&c,&e);
        Attach(c,e,&rear);/*将c,e添加到空节点后面*/
    }
    t=p; p = p->link;free(t);/*释放空节点*/
    return p;
    }


void Attach(int c,int e,Polynomial *prear)
{
    Polynomial p;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p ->link = NULL; /*对新节点赋值*/
    p->coef = c;
    p->expon = e;
    (*prear) ->link = p;
    *prear = p; /*修改*prear的值*/
}

Polynomial Add(Polynomial p1, Polynomial p2)
{
    int num;
    Polynomial rear,p,temp,t1,t2;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    rear = p;
    rear -> link = NULL;
    t1 = p1; t2 = p2;
    while(t1 && t2)
    {
        if (t1 -> expon == t2 -> expon)
        {
            num = t1->coef + t2->coef;
            if (num)
                Attach(num,t1->expon,&rear);
            t1 = t1->link;
            t2 = t2->link;

        }
        else if (t1->expon > t2->expon)
        {
            Attach(t1->coef,t1->expon,&rear);
            t1 = t1->link;
        }
        else
        {
            Attach(t2->coef,t2->expon,&rear);
            t2 = t2->link;
        }
    }
        while(t1)
        {

                Attach(t1->coef,t1->expon,&rear);
                t1 = t1->link;
        }
         while(t2)
        {

                Attach(t2->coef,t2->expon,&rear);
                t2 = t2 ->link;
        }
        temp = p;
        p = p->link;
        free(temp);
        return p;

}


Polynomial Mult(Polynomial p1,Polynomial p2)
{
    Polynomial p,rear,temp,t1,t2;
    int c,e;

    t1=p1;t2=p2;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    rear = p;
    rear -> link = NULL;
    while(t2)
    {
        Attach(t1->coef * t2->coef,t1->expon + t2->expon,&rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while(t1)
    {
        t2 = p2; rear = p;
        while(t2)
        {
            c = t1->coef * t2->coef;
            e = t1->expon + t2->expon;
            while(rear->link && rear->link->expon >e)
                rear = rear->link;
            if (rear->link && rear->link->expon == e)
            {
                if (rear->link->coef + c)
                    rear->link->coef +=c;
                else
                {
                   temp = rear->link;
                   rear->link = temp->link;
                   free(temp);
                }
            }
            else
            {
               temp = (Polynomial)malloc(sizeof(struct PolyNode));
               temp->coef = c;
               temp->expon = e;
               temp -> link = rear->link;
               rear->link = temp;
               rear = rear->link;
            }

            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2=p;
    p =p->link;
    free(t2);
    return p;
}

void PrintPoly(Polynomial P)
/*输出多项式*/
{

    int flag = 0;
    if(!P)
    {
        printf("0 0\n");

    }

    while(P)
    {
        if(!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d",P->coef,P->expon);
        P = P->link;
    }
    printf("\n");
}


int main(){
Polynomial P1,P2,PP,PS;

P1 = ReadPoly();
P2 = ReadPoly();
PP = Mult(P1,P2);
PrintPoly(PP);
PS = Add(P1,P2);
PrintPoly(PS);
return 0;
}



