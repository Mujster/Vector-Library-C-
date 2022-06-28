#include<iostream>
using namespace std;

template<typename T>
class vector {
	public:
	T* arr;
	int size_, max_size, capacity;

	//Member functions
	vector()
	{
		size_ = 0;
		max_size = 1;
		capacity = 0;
		arr = new T[max_size];
	}
	vector(int s)
	{
		size_ = s;
		arr = new T[size_];
		for (int i = 0; i < size_; i++)
		{
			arr[i] = T();
		}
	}
	vector(const vector& obj)
	{
		size_ = obj.size_;
		arr = new T[size_];
		for (int i = 0; i < size_; i++)
		{
			arr[i] = obj.arr[i];
		}
	}
	~vector()
	{
		size_ = 0;
		max_size = 1;
		delete[]arr;
	}

	//modifiers 
	void push_back(T val)
	{
		if (size_ == max_size)
		{
			T* temp = new T[2 * max_size];
			for (int i = 0; i < max_size; i++)
			{
				temp[i] = arr[i];
			}
			delete[]arr;
			max_size *= 2;
			arr = temp;
		}
		arr[size_] = val;
		size_++;
	}
	void pop_back()
	{
		size_--;
	}
	void insert(T val, int index)
	{
		if (index < 0 || index >= size_)
		{
			cout << "error\n";
		}
		else
		{
			size_ += 1;
			int* temp = new int[size_];
			int i, j;
			for (i = 0; i < index; i++)
			{
				temp[i] = arr[i];
			}
			j = i;
			temp[index] = val;
			i++;
			for (; i < size_; i++)
			{
				temp[i] = arr[j];
				j++;
			}
			delete[]arr;
			arr = temp;
		}
	}
	void clear()
	{
		size_ = 0;
		max_size = 0;
		delete[]arr;
		arr = nullptr;
	}
	void assign(int new_size, int val)
	{
		delete[]arr;
		arr = nullptr;
        size_ = new_size;
		arr = new int[new_size];
		for (int i = 0; i < new_size; i++)
		{
			arr[i] = val;
		}
	}
	void erase(int index)
	{
		if (index<0 || index>size_) {
			cout << "Error index out of bound\n";
		}
		else {
			for (int i = index; i < size_ - 1; i++)
			{
				arr[i] = arr[i + 1];
			}
	     }
		size_--;
	}

	// capacity functions
	bool empty()const
	{
		if (size_ == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int size()
	{
		return size_;
	}
	int maxsize()
	{
		return max_size;
	}
	
	//access elements functions
	T& operator[](int i)
	{
		return this->arr[i];
	}
	T& at(int i)
	{
		if (i > 0 && i <= max_size)
		{
			return this->arr[i];
		}
		else
		{
			cout << "Index out of bound";
			return 0;
		}
	}
	T& front()
	{
		if (!empty())
		{
			return this->arr[0];
		}
		else
		{
			cout << "Error Empty Array\n";
		}
	}
	T& back() 
	{
		if (!empty())
		{
			return this->arr[size_-1];
		}
		else
		{
			cout << "Error empty array\n";
		}
	}
	T* data()
	{
		if (empty())
		{
			cout << "Error array is empty\n";
		}
		else
		{
			return arr;
		//cout << "Error array is empty\n";
		}
	}

	//utility function
	void sort() {
		for (int i = 0; i < this->size_; i++) {
			int key = arr[i];
			int j = i - 1;
			while (key < arr[j] && j >= 0) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}
	void print()
	{
		int i = 0;
		while (i < size_)
		{
			cout << arr[i] << " ";
			i++;
		}
	}
	vector& operator=(const vector& obj)
	{
		if (this != &obj)
		{
			size_ = obj.size_;
			capacity = obj.capacity;
			max_size = obj.max_size;
			arr = new int[obj.size_];
			for (int i = 0; i < size_; i++)
			{
				arr[i] = obj.arr[i];
			}
			return *this;
		}
	}
	
	//iterators
	class iterator;
	iterator begin();
	iterator end();

	//relational bool functions
	template<typename U, typename V> friend bool operator==(const vector<U>& v1, const vector<V>& v2);
	template<typename U, typename V> friend bool operator!=(const vector<U>& v1, const vector<V>& v2);

};
template<typename U, typename V>
bool operator==(const vector<U>& v1, const vector<V>& v2) {
	if (v1.size_ == v2.size_) {
		for (int i = 0; i < v1.size_; i++) {
			if (v1.arr[i] != v2.arr[i])
			{
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		return false;
	}
}
template<typename U, typename V>
bool operator!=(const vector<U>& v1, const vector<V>& v2) {
	if (v1.size_ != v2.size_) {
		return true;
	}
	else {
		for (int i = 0; i < v1.size_; i++) {
			if (v1.arr[i] != v2.arr[i]) {
				return true;
			}
		}
		return false;
	}

}
template<typename T>
class vector<T>::iterator
{
private:
	T* arr;
public:
	iterator(T* p) :arr(p)
	{}
	iterator& operator++()
	{
		++arr;
		return *this;
	}
	iterator& operator++(int)
	{
		iterator temp(*this);
		++arr;
		return temp;
	}
	iterator& operator--()
	{
		--arr;
		return *this;
	}
	T& operator*() //const
	{
		return *arr;
	}
	bool operator==(const iterator& b) const
	{
		return *arr == *b.arr;
	}
	bool operator!=(const iterator& b) const
	{
		return *arr != *b.arr;
	}

};
template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
	return vector<T>::iterator(&arr[0]);
}
template<class T>
typename vector<T>::iterator vector<T>::end()
{
	return vector<T>::iterator(&arr[size_]);
}

//bool specialized class

template<>
class vector<bool>
{
public:
	bool* arr;
	int size_;
	int max_size;

	//member functions
	vector()
	{
		arr = new bool[1];
		size_ = 0;
		max_size = 1;
	}
	vector(int n)
	{
		size_=n;
		arr = new bool[size_];
		for (int i = 0; i < size_; i++)
		{
			arr[i] = 0;
		}
	}
	vector(const vector& obj)
	{
		size_ = obj.size_;
		arr = new bool[size_];
		for (int i = 0; i < size_; i++)
		{
			arr[i] = obj.arr[i];
		}
	}
	~vector()
	{
		delete[]arr;
		arr = nullptr;
		size_ = 0;
		max_size = 0;
	}

	//modifiers
	void push_back(bool val)
	{
		if (size_ == max_size)
		{
			bool* temp = new bool[2 * max_size];
			for (int i = 0; i < max_size; i++)
			{
				temp[i] = arr[i];
			}
			delete[]arr;
			max_size *= 2;
			arr = temp;
		}
		arr[size_] = val;
		size_++;
	}
	void pop_back()
	{
		size_--;
	}
	void erase(int index)
	{
		if (index<0 || index>size_) {
			cout << "Error index out of bound\n";
		}
		else {
			for (int i = index; i < size_ - 1; i++)
			{
				arr[i] = arr[i + 1];
			}
		}
		size_--;
	}
	void clear()
	{
		delete[]arr;
		arr = nullptr;
		size_ = 0;
		max_size = 0;
	}
	void insert(bool val, int index)
	{
		if (index < 0 || index >= size_)
		{
			cout << "error\n";
		}
		else
		{
			size_ += 1;
			bool* temp = new bool[size_];
			int i, j;
			for (i = 0; i < index; i++)
			{
				temp[i] = arr[i];
			}
			j = i;
			temp[index] = val;
			i++;
			for (; i < size_; i++)
			{
				temp[i] = arr[j];
				j++;
			}
			delete[]arr;
			arr = temp;
		}
	}
	void assign(int size, bool val)
	{
		delete[]arr;
		arr = nullptr;
		size_ = size;
		arr = new bool[size_];
		for (int i = 0; i < size_; i++)
		{
			arr[i] = val;
		}
	}

	//capacity functions
	bool empty()
	{
		if (size_ == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	int size()
	{
		return size_;
	}
	int maxsize()
	{
		return max_size;
	}

	//access elements functions
	bool& operator[](int i)
	{
		return this->arr[i];
	}
	bool& at(int i)
	{
		if (i >= 0 && i < size_)
			return arr[i];
	}
	bool& front()
	{
		if (!empty())
		{
			return this->arr[0];
		}
		else
		{
			cout << "Error Empty Array\n";
		}
	}
	bool& back()
	{
		if (!empty())
		{
			return this->arr[size_ - 1];
		}
		else
		{
			cout << "Error empty array\n";
		}
	}
	bool* data()
	{
		if (!empty())
		{
			return arr;
		}
		else
		{
			cout << "Error array is empty\n";
		}
	}

	//utility functions
	void sort() {
		for (int i = 0; i < this->size_; i++) {
			bool key = arr[i];
			int j = i - 1;
			while (key < arr[j] && j >= 0) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}
	void print()
	{
		int i = 0;
		while (i < size_)
		{
			cout << arr[i] << " ";
			i++;
		}
	}
	vector& operator=(const vector& obj)
	{
		if (this != &obj)
		{
			size_ = obj.size_;
			max_size = obj.max_size;
			arr = new bool[size_];
			for (int i = 0; i < size_; i++)
			{
				arr[i] = obj.arr[i];
			}
			return *this;
		}
	}

	//iterators
	bool* begin()
	{
		return &arr[0];
	}
	bool* end()
	{
		return &arr[size_];
	}

	class iterator
	{
		bool* ptr;
	public:
		iterator(bool* p) :ptr(p)
		{

		}
		iterator& operator++()
		{
			++ptr;
			return *this;
		}
		iterator& operator++(int)
		{
			iterator temp(*this);
			++ptr;
			return temp;
		}
	    iterator& operator--()
		{
			--ptr;
			return *this;
		}
	 	bool& operator*() //const
		{
			return *ptr;
		}
		bool operator==(const iterator& b) const
		{
			return *ptr == *b.ptr;
		}

		bool operator!=(const iterator& b) const
		{
			return *ptr != *b.ptr;
		}
	};
};
