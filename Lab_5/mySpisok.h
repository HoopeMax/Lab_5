#include <iostream>
#include <initializer_list>

template <typename T>
class Spisok
{
private:
	//������� ������ ������ �������� ����������� ������
	template <typename T>
	class Elem
	{
	public:
		Elem* pNext; //��������� �� ��������� ����
		Elem* pPrev; //��������� �� ���������� ����
		T value; 
		Elem(T value, Elem* pNext = nullptr, Elem* pPrev = nullptr)
		{
			this->pNext = pNext;
			this->pPrev = pPrev;
			this->value = value;
		}
	};

public:
	short length;
	Elem<T>* headElement; //������ ������� ������
	Elem<T>* tailElement; //��������� ������� ������
	//���������� �������������
	Spisok();
	Spisok(T value);
	Spisok(std::initializer_list<T> value);
	//���������� ������
	~Spisok();
	//������ �������
	T size();
	//���������� ������ ������
	T front();
	//���������� ��������� �������
	T back();
	//������ ���-�� ��������� ������
	void resize(unsigned short elements);
	void resize(unsigned short elements, T value);
	//������� ���� � ������ 
	void pop_back();
	//������� ���� � ������
	void pop_front();
	//�������� ���� ������
	void push_back(T data);
	//��������� ������� � ������
	void push_front(T data);
	//���������� true ���� ������ ������, �  false ���� ���.
	void assign(unsigned short n, T value);
	//�������� ������� � ����� ����� ������
	void insert(unsigned short pos, T value);
	//������� ������
	void clear();
	//������������� ������
	void show();
	//������ ������� �������� ������
	void swap(int pos_1, int pos_2);
	Elem<T>* begin();
	Elem<T>* end();
	//����� ���������� true ���� ������ ������, �  false ���� ���.
	bool empty();
};

template <typename T>
Spisok<T>::Spisok()
{
	length = 0;
	headElement = nullptr;
	tailElement = nullptr;
}

template <typename T>
Spisok<T>::Spisok(T value)
{
	length = 1;
	headElement = new Elem<T>(value, nullptr, nullptr);
	tailElement = nullptr;

}

template <typename T>
Spisok<T>::Spisok(std::initializer_list<T> value)
{
	length = value.size();
	headElement = new Elem<T>(*(value.begin()), nullptr, nullptr);
	Elem<T>* BUFER = headElement;
	for (unsigned short step(1); step < length; step++)
	{
		BUFER->pNext = new Elem<T>(*(value.begin() + step), nullptr, BUFER);
		BUFER = BUFER->pNext;
	}
	tailElement = BUFER;

}

template<typename T>
void Spisok<T>::push_back(T data)
{
	if (headElement == nullptr)
	{
		headElement = new Elem<T>(data);
		length++;
	}
	else
	{
		Elem<T>* runningElement = this->headElement;
		while (runningElement->pNext != nullptr)
		{
			runningElement = runningElement->pNext;
		}
		runningElement->pNext = new Elem<T>(data, nullptr, runningElement);
		tailElement = runningElement->pNext;
		length++;
	}
}

template<typename T>
void Spisok<T>::push_front(T data)
{
	if (headElement == nullptr)
	{
		headElement = new Elem<T>(data);
		length++;
	}
	else
	{
		Elem<T>* runningElement = new Elem<T>(data, this->headElement);
		headElement->pPrev = runningElement;
		headElement = runningElement;
		length++;
	}
}

// ���������� ���������� N ����������, ������� ����� �������� Value.
template<typename T>
void Spisok<T>::assign(unsigned short n, T value)
{
	Elem<T>* runningElement = tailElement;
	for (unsigned short steps(length); steps > 0; steps--)
	{
		length--;
		runningElement = tailElement->pPrev;
		delete tailElement;
		tailElement = runningElement;
	}
	headElement = nullptr;
	tailElement = nullptr;
	headElement = new Elem<T>(value, nullptr, nullptr);
	runningElement = headElement;
	for (unsigned short step(0); step < n; step++)
	{
		runningElement->pNext = new Elem<T>(value, nullptr, runningElement);
		runningElement = runningElement->pNext;
		tailElement = runningElement;
		length++;
	}
}

// ��������� �������� ������� � ����� ������� ������.
template<typename T>
void Spisok<T>::insert(unsigned short pos, T value)
{
	if (pos < length)
	{
		Elem<T>* runningElement = headElement;
		for (unsigned short place(1); place < pos; place++)
		{
			runningElement = runningElement->pNext;
		}
		if (pos == 0)
		{
			length++;
			Elem<T>* newElement = new Elem<T>(value, headElement, nullptr);
			headElement->pPrev = newElement;
			headElement = newElement;

		}
		else
		{
			Elem<T>* newElement = new Elem<T>(value, runningElement->pNext, runningElement);
			Elem<T>* transit = runningElement->pNext;
			newElement->pNext = transit;
			runningElement->pNext = newElement;
			transit->pPrev = newElement;
			length++;
		}
	}

}

// ����� ������� ���������� ������ ������� � ������.
template<typename T>
T Spisok<T>::front()
{
	return headElement->value;
}

//����� ���������� ��������� ������� � ������.
template<typename T>
T Spisok<T>::back()
{
	return tailElement->value;
}

//����� ��������� ������� ������.
template<typename T>
void Spisok<T>::clear()
{
	Elem<T>* runningElement = tailElement;
	for (unsigned short steps(length); steps != 0; steps--)
	{
		length = steps;
		runningElement = tailElement->pPrev;
		delete tailElement;
		tailElement = runningElement;
	}
	length--;
	headElement = nullptr;
	tailElement = nullptr;
}

//����� ������������� �������� ������.
template<typename T>
void Spisok<T>::show()
{
	if (length != 0)
	{
		Elem<T>* runningElement = headElement;
		for (unsigned short steps(0); steps < length; steps++)
		{
			std::cout << runningElement->value << " ";
			runningElement = runningElement->pNext;
		}
	}
	else
	{
		std::cout << "��������� ��� \n";
	}
	std::cout << "\n\n";
}

//���������� ��������� �� ������ ������� ������.
template<typename T>
Spisok<T>::Elem<T>* Spisok<T>::begin()
{
	return headElement;
}

//���������� ��������� �� ��������� ������� ������.
template<typename T>
Spisok<T>::Elem<T>* Spisok<T>::end()
{
	return tailElement;
}

//���������� 
template <typename T>
Spisok<T>::~Spisok()
{
	Elem<T>* runningElement = tailElement;
	if (length > 1)
	{
		for (unsigned short steps(length); steps > 0; steps--)
		{
			runningElement = tailElement->pPrev;
			delete tailElement;
			tailElement = runningElement;
		}
		delete tailElement, headElement, runningElement;
	}
	else
	{
		delete headElement, runningElement;
	}
}

//����� ���������� ����� ������.
template <typename T>
T Spisok<T>::size()
{
	return length;
}

//���� ��������� ������, ��� Elements, �� ����������� �������� �� ��������� �� ���������.
template<typename T>
void Spisok<T>::resize(unsigned short elements)
{
	if (length > elements)
	{
		Elem<T>* runningElement = tailElement->pPrev;
		while (length != elements)
		{
			length--;
			delete runningElement->pNext;
			runningElement = runningElement->pPrev;
		}
		tailElement = runningElement->pNext;
	}
	else if (length < elements)
	{
		while (length != elements)
		{
			length++;
			tailElement->pNext = new Elem<int>(T(), nullptr, tailElement);
			tailElement = tailElement->pNext;
		}
	}
}

//����������� ��������
template<typename T>
void Spisok<T>::resize(unsigned short elements, T value)
{
	if (length > elements)
	{
		Elem<T>* runningElement = tailElement->pPrev;
		while (length != elements)
		{
			length--;
			delete runningElement->pNext;
			runningElement = runningElement->pPrev;
		}
		tailElement = runningElement->pNext;
	}
	else if (length < elements)
	{
		while (length != elements)
		{
			length++;
			tailElement->pNext = new Elem<int>(value, nullptr, tailElement);
			tailElement = tailElement->pNext;
		}
	}
}

//����� ������� ��������� ������� ������.
template<typename T>
void Spisok<T>::pop_back()
{
	length--;
	Elem<T>* transit = tailElement->pPrev;
	delete transit->pNext;
	tailElement = transit;
}

//����� ������� ������ ������� ������.
template<typename T>
void Spisok<T>::pop_front()
{
	length--;
	Elem<T>* transit = headElement->pNext;
	headElement = transit;
}

//����� ���������� true ���� ������ ������, �  false ���� ���.
template<typename T>
bool Spisok<T>::empty()
{
	if (length == 0)
		return true;
	else
		return false;
}

template<typename T>
void Spisok<T>::swap(int pos_1, int pos_2)
{
	Elem<T>* p_buffer = headElement;
	for (int i(0); i < pos_1 - 1; i++)
	{
		p_buffer = p_buffer->next;
		p_buffer->next->pred = p_buffer;
	}
	Elem<T>* first_point = p_buffer;
	for (int i(pos_1); i < pos_2; i++)
	{
		p_buffer = p_buffer->next;
		if (p_buffer->next != nullptr) p_buffer->next->pred = p_buffer;
	}

	Elem<T>* second_point = p_buffer;
	if (pos_1 > 1)
	{
		first_point->pred->next = second_point;
		first_point->next->pred = second_point;
		second_point->pred->next = first_point;
		second_point->next->pred = first_point;
	}
	else
	{
		headElement = second_point;
		first_point->next->pred = second_point;
		second_point->pred->next = first_point;
		if (second_point->next != nullptr) second_point->next->pred = first_point;
		else tailElement = first_point;
	}

	if (pos_1 > 1)
	{
		Elem<T>* save = new Elem<T>(NULL, second_point->next, second_point->pred);
		second_point->pred = first_point->pred;
		second_point->next = first_point->next;
		first_point->next = save->next;
		first_point->pred = save->pred;
	}
	else
	{
		Elem<T>* save = new Elem<T>(NULL, second_point->next, second_point->pred);
		second_point->pred = nullptr;
		second_point->next = first_point->next;
		first_point->next = save->next;
		first_point->pred = save->pred;
	}
}