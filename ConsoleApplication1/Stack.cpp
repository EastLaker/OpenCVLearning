/*#include"Head.h"
using namespace std;
template<class T>
SeqStack<T>::SeqStack(int mSize)
{
	maxTop = mSize - 1;
	s = new T[mSize];
	top = -1;
}

template <class T>
bool SeqStack<T>::Push(T x)  //x‘™Àÿ≤Â»Î’ª∂•
{
	if (IsFull())
	{
		cout << "Overflow" << endl;
		return false;
	}
	s[++top] = x;
	return true;
}
template <class T>
bool SeqStack<T>::Pop()
{
	if (IsEmpty())
	{
		cout << "UnderFlow" << endl;
		return false;
	}
	top--;
	return true;
}
template <class T>
bool SeqStack<T>::Top(T &x)const
{
	if (IsEmpty())
	{
		cout << "Empty!" << endl;
		return false;
	}
	x = s[top];
	return true;
}
template <class T>
bool SeqStack<T>::Botton(T &x)
{
	if (IsEmpty())
	{
		cout << "Empty!" << endl;
		return false;
	}
	x = s[0];
	return true;
}*/
