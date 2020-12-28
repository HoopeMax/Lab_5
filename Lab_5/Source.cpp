#include <iostream>
#include <string>
#include "mySpisok.h"

//Шаблоннный тип 
template <typename T>
//Метод поиска максимального эемента и замены знака на отрицательный 
void Max(Spisok<T>* object);

int main()
{
	setlocale(LC_ALL, "russian");
	Spisok<int> object({-3, 2, 3 ,6, -8, 0 ,7, 4 ,3 });
	object.insert(-2, -5);
	std::cout << "Изначальный список элеменов\n";
	object.show();
	Max(&object);
	std::cout << "Меняем знак у наибольшего элемента \n";
	object.show();
	system("pause");
}

template <typename T>
void Max(Spisok<T>* object)
{
	T min = T();

	std::string check = typeid(T).name();
	{
		if (check == "char")
		{
			min = CHAR_MIN;
		}
		else if (check == "short")
		{
			min = SHRT_MIN;
		}
		else if (check == "int")
		{
			min = INT_MIN;
		}
		else if (check == "long")
		{
			min = LONG_MIN;
		}
		else if (check == "float")
		{
			min = FLT_MIN;
		}
		else if (check == "double")
		{
			min = DBL_MIN;
		}
		else
		{
			std::cout << "Ошибка заданного типа данных \n";
		}
	}
	unsigned short minPos = 1;
	if (object->size() > 1)
	{
		for (int i(0); i < object->size(); i++)
		{
			if (object->front() > min)
			{
				min = object->front();
				minPos = i;
			}
			object->push_back(object->front());
			object->pop_front();
		}
		double* save = new double[minPos];
		for (int i(0); i < minPos; i++)
		{
			save[i] = object->front();
			object->pop_front();
		}
		object->begin()->value *= -1;
		for (int i(minPos - 1); i >= 0; i--)
		{
			object->push_front(save[i]);
		}
	}
	else
	{
		object->begin()->value *= -1;
	}
}