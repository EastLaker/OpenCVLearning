#include"Head.h"
using namespace std;
/*--------------------------------------
template <class T>
SeqQueue<T>::SeqQueue(int mSize)
{
	maxSize = mSize;
	q = new T[maxSize];
	front = rear = 0;
}
template <class T>
bool SeqQueue<T>::EnQueue(T x)
{
	if (IsFull()) //溢出处理
	{	           
		cout << "Full" << endl; return false;
	}
	q[rear = (rear + 1) % maxSize] = x;
	return true;
}
template<class T>
bool SeqQueue<T>::DeQueue()
{
	if (IsEmpty())
	{
		cout << "UnderFlow." << endl;
		return false;
	}
	front = (front + 1) % maxSize;//循环增1
	return true;
}
template <class T>
bool SeqQueue<T>::Front(T &x) const
{
	if (IsEmpty())  //空队列处理
	{
		cout << "Empty" << endl;
		return false;
	}
	x = q[(front + 1) % maxSize];
	return true;
}
template <class T>
int SeqQueue<T>::Length()
{
	if (rear>front)
		return (rear - front);
	else
		return (rear + maxSize - front);
}

-----------------------------------------*/
void InitQueue(LinkQuNode *&q)
{
	q = new LinkQuNode;
	q->front = q->rear = NULL;
}
bool IsEmpty(LinkQuNode *q)
{
	return (q->rear == NULL);
}
void EnQueue(LinkQuNode *&q,ElemType Data)
{
	DataNode *temp = new DataNode;
	temp->data = Data;
	temp->next = NULL;
	if (IsEmpty(q))
	{
		q->rear = temp;
	}
	else
	{
		q->rear->next = temp;
		q->rear = temp;
	}
}
bool DelQueue(LinkQuNode *& q)
{
	if (IsEmpty(q))
	{
		cout << "Empty!" << endl;
		return false;
	}
	DataNode *t=q->front;
	if (t->next == NULL)
	{
		delete t;
		q->front = NULL, q->rear = NULL,t=NULL;
	}
	else
	{
		q->front = t->next;
		delete t;
		t = NULL;
	}
	return true;
}
int LinkQueueLength(LinkQuNode *& q)
{
	if (IsEmpty(q))
		return 0;
	DataNode *CurNode = q->front;
	int counter = 1;
	while (1)
	{
		if (CurNode == q->rear)
		{
			return counter;
			break;
		}
		counter++;
		CurNode = CurNode->next;
	}
}