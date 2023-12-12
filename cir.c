#include<stdio.h>
#include<stdlib.h>
#define MAXQ 100
int front=-1,rear=-1;
int items[MAXQ];
int Isempty();
int Isfull();
void Insert(int);
int Delete();
void Display();
void main()
{
int x;
char ch='1';
while(ch !='4')
{
printf("\n 1-INSERT");
printf("\n 2-DELETE");
printf("\n 3-DISPLAY");
printf("\n 4-QUIT");
printf("\n Enter your choice:");
fflush(stdin);
ch=getchar();
switch (ch)
{
case '1':
printf("\n Enter the nos of element to be inserted:");
scanf("%d",$x);
Insert(x);
break;
case "2":
x=Delete();
printf("\n Deleted element is %d\n:",x);
break;
case '3':
Display();
break;
case '4':
break;
default:
printf("\n wrong choice!Try again:");
}
}
}
int Isempty()
{
if(front==-1)
return 1;
else 
return 0;
}
int Isfull()
{
if (front==(rear+1)%MAXQ)
return 1;
elese
return 0;
}
void Insert(int x)
{
if (Isfull())
{
printf("\n Queue full");
return;
}
if(front==-1)
{
front=0;
rear=0;
}else
rear =(rear +1)% MAXIQ;
items[rear]=x;
}
int Delete()
{
int x;
if(Isempty())
{
printf("\n Queue is empty");
exit(0);
}
x=items[front];
if (front==rear)
{
front=-1;
rear=-1;
}
else
front=(front+1)% MAXIQ;
return x;
}
void Display()
{
int i,n;
if(Isempty())
{
printf("\n Queue is empty");
return;
}
printf("\n Elements in the Queue are:\n");
if (front <=rear)
{
for(i=front;i<=rear;i++)
printf("%d\n",items[i]);
}
else
{
for(i=front;i<=MAXIQ-1;i++)
printf("%d\n",items[i];
for(i=0;i<=rear;i++)
printf("%d\n",items[i];
}
}

  
