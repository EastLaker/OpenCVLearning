/*
Basic:顺序存储
任务1：要求实现长度为6的循环队列，能够实现入队、出队、查询队列长度、队列空或溢出现象要有对应的处理
或显示方法，验证方法为入队6个数
任务2：要求实现长度6的栈，能够实现入栈、出栈、查询栈顶、栈底指针、查询当前指针处的值
任务3：要求实现长度可变的链表，根据输入值的个数自动扩充链表长度，要求实现链表的插入、查询、增加
或删除某些节点、查询链表长度
任务4：体会CPU的运算速度，创建超大（1000000或更大）数组（或链表），初始化为1-数组长度，然后遍历数组
直到查询到最后一个数，要windows自带函数记录查询所消耗的时间
Advanced:
1.使用链表实现循环队列，完成与上述相同的功能
2.预处理命令的了解，使用宏在C中实现函数的默认参数
3.了解不同的查找算法，体会其时间复杂度与空间复杂度对程序的影响
4.神将网络初体验，使用神经网络实现10以为的加减法
*/

#include <iostream>  
#include<time.h>
#include<Windows.h>
#include"Head.h"
#include<time.h>
using namespace std;
void PrintArrayTime()
{
	time_t start = GetTickCount();
	//Sleep(1000);

	long int i, j = 0;
	long int *array = new long int[1000000];
	for (i = 0; i<1000000; i++)
	{
		array[i] = i;
		printf("%d", array[i]);
		printf("\n");
	}
	time_t  end = GetTickCount();
	cout << "Time used : " << (end - start)/1000.0<<" seconds" << endl;

}


int main()
{
	int array[11];
	int x;
	for (int i = 0; i < 11; i++)
	{
		array[i] = i;
	}
	SeqStack <int> S1(10);
	for (int j = 0; j < 10; j++)
	{
		S1.Push(array[j]);
	}
	S1.Botton(x);
	cout << "Stack Botton:" << x << endl;
	S1.Top(x);
	cout << "Stack Top:" << x << endl;

	SeqQueue <int> Q1(10);
	for (int i = 0; i<10; i++)
	{
		Q1.EnQueue(array[i]);
	}

	Q1.DeQueue();
	//Q1.DeQueue();
	Q1.Front(x);
	cout << "Queue front:";
	Q1.showLineNode(x);
	cout << "Queue Length:"<< Q1.Length() << endl;

	QNode <int> *pHead = new QNode<int>;
	QNode <int> *pNode = pHead;
	for (int i = 0; i<10; i++)
	{
		pNode->AddData(array[i]);
		pNode = pNode->next;
	}
	//cout<<pNode->data<<endl;
	cout << "Length of Linker:" << pHead->Length() << endl;
	pNode = pHead;
	while (pNode->next != NULL)
	{
		if (pNode->data == 5)   // 
		{
			pNode->Insert(pNode, 998);
			break;
		}
		else
			pNode = pNode->next;
	}
	cout <<"Insert Node after Node5:" <<pNode->next->data << endl;
	pNode = pHead;
	while (pNode->next != NULL)
	{
		if (pNode->data == 4)   // ÔÚÊý¾ÝÎªxµÄ½áµãºóÉ¾³ý½áµã 
		{
			pNode->DelNode(pNode);
			break;
		}
		else
			pNode = pNode->next;
	}
	cout << "The next Node of Node4 After deleting Node5:"<<pNode->next->data << endl;
	system("pause");
	PrintArrayTime();
	system("pause");
	return 0;
}


