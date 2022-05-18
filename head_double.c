#include <stdio.h>
//calloc函数需要
#include <stdlib.h>
//sizeof函数需要
#include <string.h>

typedef int data_type;

typedef struct double_turnlist1
{
    data_type data;
    struct double_turnlist1 *Prev;
    struct double_turnlist1 *Next;
}Node,*P_Node;

//新建节点
P_Node NewNode(data_type *new_data)
{
    //申请空间
    P_Node new = calloc(1,sizeof(Node));
    if (new == NULL)
    {
        perror("calloc error");
        return NULL;
    }
    //数据域初始化
    if (new_data != NULL)
    {
        memcpy(&new->data,new_data,sizeof(data_type));
    }
    //指针域初始化
    new->Prev = new->Next = new;
    return new;
}

//节点头插
void AddListHead(P_Node head,P_Node new)
{
    if (head == NULL|| head->Next == NULL)
    {
        printf("链表为空或异常\n");
        return;
    }
    new->Next = head->Next;
    new->Prev = head;
    head->Next->Prev = new;
    head->Next = new;
    return;
}

//遍历链表
void Display_List(P_Node head)
{
    if (head == NULL|| head->Next == NULL)
    {
        printf("链表为空或异常\n");
        return;
    }
    printf("——————————————————————————————————————————————\n");
    for (P_Node tmp = head->Next; tmp !=head; tmp = tmp->Next)
    {
        printf("%d\t",tmp->data);
    }
    printf("\n");
    return;
}

//节点尾插
void ADDListTail(P_Node head,P_Node new)
{
    if (head == NULL||head->Next == NULL)
    {
        printf("链表异常或为空\n");
        return;
    }
    new->Next = head;
    new->Prev = head->Prev;
    head->Prev->Next = new;
    head->Prev = new;
    return;
}

//查找内容
void Search_List(P_Node head)
{
    if (head == NULL|| head->Next == NULL)
    {
        printf("链表为空或异常\n");
        return;
    }
    printf("输入查找的内容：");
    data_type ToFindContent;
    scanf("%d",&ToFindContent);
    int num=0;
    for (P_Node tmp = head->Next; tmp !=head; tmp = tmp->Next)
    {
        num++;
        if (ToFindContent == tmp->data)
        {
            printf("已找到%d,在链表的第%d个节点\n",ToFindContent,num);
            Display_List(head);
            return;
        }
    }
    printf("未找到内容\n");
    return;
}

//删除特定内容
//思考如何嵌套查找函数?
void Delete_List(P_Node head)
{
    if (head == NULL||head->Next == NULL)
    {
        printf("链表为空或异常\n");
        return;
    }
    printf("输入要删除的内容:");
    data_type DeleteContent;
    scanf("%d",&DeleteContent);
    for (P_Node tmp = head->Next; tmp !=head; tmp=tmp->Next)
    {
        if (tmp->data == DeleteContent)
        {
            tmp->Prev->Next = tmp->Next;
            tmp->Next->Prev = tmp->Prev;
            tmp->Next = tmp->Prev = NULL;
            Display_List(head);
            return;
        }
    }
    printf("没有找到要删除的内容\n");
    return;
}

//修改特定内容
void Modify_List(P_Node head)
{
    if (head == NULL||head->Next == NULL)
    {
        printf("链表为空或异常\n");
        return;
    }
    printf("输入要修改数据:");
    data_type ModifyContent;
    scanf("%d",&ModifyContent);
    for (P_Node tmp = head->Next; tmp !=head; tmp=tmp->Next)
    {
        if (tmp->data == ModifyContent)
        {
            printf("输入修改内容；");
            scanf("%d",&tmp->data);
            Display_List(head);
            return;
        }
    }
    printf("没有找到要修改的内容\n");
    return;
}

//乱序输入，按大小排序
void AddList_OutOrder(P_Node head,P_Node new)
{
    if (head == NULL ||head->Next == NULL)
    {
        printf("链表为空或异常\n");
        return;
    }
    //第一个有效节点，不需要查找比较直接头插
    if (head->Next == head && head->Prev == head)
    {
        //直接头插
        new->Next = head->Next;
        new->Prev = head;
        head->Next->Prev = new;
        head->Next = new;
        return;
    }
    //后面的有效节点需要查找比较
    for (P_Node tmp = head->Next; tmp != head; tmp = tmp->Next)
    {
        //当new小于等于tmp时，插入tmp和tmp前一个节点
        if (new->data <= tmp->data)
        {
            new->Next = tmp;
            new->Prev = tmp->Prev;
            tmp->Prev->Next = new;
            tmp->Prev = new;
            return;
        }
        //new.data比最大的还大
        if (tmp->Next == head && tmp->data < new->data)
        {
            new->Next = tmp->Next;
            new->Prev = tmp;
            tmp->Next->Prev = new;
            tmp->Next = new;
            return;
        }
    }
}

//修改特定内容，并及时排序
void ModifySort_List(P_Node head)
{
    if (head == NULL || head->Next == NULL)
    {
        printf("链表异常或为空\n");
        return;
    }
    printf("输入需要的数据(及时排序)；");
    data_type ModifyContent;
    scanf("%d",&ModifyContent);
    for (P_Node tmp = head->Next; tmp != head; tmp = tmp->Next)
    {
        if (tmp->data == ModifyContent)
        {
            //修改内容
            printf("输入要修改内容：");
            scanf("%d",&tmp->data);
            Display_List(head);
            //断开节点(剔除)
            tmp->Prev->Next = tmp->Next;
            tmp->Next->Prev = tmp->Prev;
            tmp->Next = tmp->Prev = NULL;
            Display_List(head);
            //及时排序
            for (P_Node tmq = head->Next; tmq != head; tmq = tmq->Next)
            {
                if (tmp->data <= tmq->data)
                {
                    tmp->Next = tmq;
                    tmp->Prev = tmq->Prev;
                    tmq->Prev->Next = tmp;
                    tmq->Prev = tmp;
                    return;
                }
                //tmp.data比最大的还大
                if (tmq->Next == head && tmq->data < tmp->data)
                {
                    tmp->Next = tmq->Next;
                    tmp->Prev = tmq;
                    tmq->Next->Prev = tmp;
                    tmq->Next = tmp;
                    return;
                }
            }
            return;
        }
        
    }
    
}

int main(int argc, char const *argv[])
{
    //新建头节点
    P_Node head = NewNode(NULL);
    //添加数据
    // for (int i = 0; i < 10; i++)
    // {
    //     P_Node new = NewNode(&i);
    //     //节点头插
    //     // AddListHead(head,new);
    //     //节点尾插
    //     ADDListTail(head,new);
    // }
    data_type m;
    for (int i = 0; i < 6; i++)
    {
        printf("输入数字：");
        scanf("%d",&m);
        P_Node new = NewNode(&m);
        //乱序插入
        AddList_OutOrder(head,new);
        Display_List(head);
    }
    Display_List(head);
    //查找内容
    Search_List(head);
    //删除（剔除）特定内容
    Delete_List(head);
    //修改特定内容
    Modify_List(head);
    //修改特定内容，并及时排序
    ModifySort_List(head);
    Display_List(head);
    return 0;
}