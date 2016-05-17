#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
//插入排序
template<class T>
void PrintArray(T* a, size_t size)
{
	assert(a);
	for (size_t i = 0;i < size;++i)
		cout << a[i] << " ";
	cout << endl;
}
template<class T>
void InsertSort(T* a, size_t size)
{
	//int num = 0;
	assert(a&&size >= 1);
	for (size_t index = 1;index < size;++index)
	{
		for (int i = index - 1;i >= 0;--i)
		{
			if (a[i] > a[i + 1])
			{
				swap(a[i], a[i + 1]);
				//cout << num++ << ":";
				//PrintArray(a, size);
			}
			else
				break;
		}
	}
}

//希尔排序
template<class T>
void ShellSort(T* a, size_t size)
{
	//int num = 0;
	assert(a);
	size_t gap = size;
	//PrintArray(a, size);
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (size_t index = 0;index < size - gap;index += gap)
		{
			for (int i = index - gap;i >= 0;--i)
			{
				if (a[i] > a[i + gap])
				{
					swap(a[i], a[i + gap]);
					//cout << num++ << ":";
					//PrintArray(a, size);
				}
				else
					break;
			}
		}
	}
}
//选择排序
template<class T>
void SelectSort(T* a, size_t size)
{
	assert(a);
	for (size_t left = 0, right = size - 1;left < right;left++, right--)
	{
		T Max = left;
		T Min = right;
		for (size_t index = left;index <= right;++index)
		{
			if (a[index] > a[Max])
				Max = index;
			if (a[index] < a[Min])
				Min = index;
		}
		if (left != Min)
		{
			swap(a[left], a[Min]);
			if (Max == left)//保证当最大值在left时不会被移走
				Max = Min;
		}
		if (right != Max)
			swap(a[right], a[Max]);

	}
}
//堆排序
template<class T>
void AdjustDown(T* a, int parIndex, size_t size)
{
	size_t childIndex = parIndex * 2 + 1;
	while (childIndex < size)
	{
		if (a[childIndex] < a[childIndex + 1] && (childIndex + 1) < size)
			++childIndex;
		if (a[parIndex] < a[childIndex])
		{
			swap(a[childIndex], a[parIndex]);
			parIndex = childIndex;
			childIndex = parIndex * 2 + 1;
		}
		else
			break;
	}

}
template<class T>
void HeapSort(T* a, size_t size)
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0;--i)
	{
		AdjustDown(a, i, size);
	}
	for (int i = 0; i <size;++i)
	{
		swap(a[0], a[size - 1 - i]);
		AdjustDown(a, 0, size - 1 - i);
	}
}

int a[10] = { 2,0,4,9,5,6,8,7,1,5 };
void QuickSort(int* a1, int left, int right)
{
	assert(a);
	if (left < right)
	{
		int key = a[right];
		int cur = left;
		int prev = cur - 1;
		while (cur < right)
		{
			if (a[cur] > key&&prev != cur)
				++cur;
			else
			{
				++prev;
				if (a[prev] > key)
					swap(a[cur], a[prev]);
				++cur;
			}
		}
		swap(a[++prev], a[right]);
		int boundary = prev;
		QuickSort(a, left, boundary - 1);
		QuickSort(a, boundary + 1, right);
	}
}

void QuickSort_2(int* a1, int left, int right)
{
	assert(a);
	if (left < right)
	{
		int key = a[right];
		int begin = left;
		int end = right - 1;
		while (begin < end)
		{
			while (a[begin] <= key&&end >begin)
				++begin;
			while (a[end] >= key&&end > begin)
				--end;
			if(begin<end)
			swap(a[begin], a[end]);
		}
		if (a[end] >= key)
		swap(a[begin], a[right]);
		int boundary = begin;
		QuickSort_2(a, left, boundary - 1);
		QuickSort_2(a, boundary + 1, right);
	}
}

//三数取中法
int GetMidIndex(int* a, int left, int right)
{

	int mid = left + ((right - left)/2);
	if (a[left] < a[right])
	{
		if (a[right] < a[mid])
			return right;
		else if (a[left] > a[mid])
			return left;
		else
			return mid;
	}
	else
	{
		if (a[right] > a[mid])
			return right;
		else if (a[left] < a[mid])
			return left;
		else
			return mid;
	}
}
void QuickSort_3(int* a1, int left, int right)
{
	assert(a);
	if (left < right)
	{
		int tmpIndex = GetMidIndex(a, left, right);
		if (tmpIndex != right)
			swap(a[tmpIndex], a[right]);
		int key = a[right];
		int begin = left;
		int end = right - 1;
		while (begin < end)
		{
			while (a[begin] <= key&&end >begin)
				++begin;
			while (a[end] >= key&&end > begin)
				--end;
			if (begin<end)
				swap(a[begin], a[end]);
		}
		if (a[end] >= key)
		swap(a[begin], a[right]);
		int boundary = begin;
		QuickSort_3(a, left, boundary - 1);
		QuickSort_3(a, boundary + 1, right);
	}
}

//非递归
void QuickSort_Non(int* a1, int l, int r)
{
	stack<int> s;
	s.push(r);
	s.push(l);
	int begin, end, mid;
	while (!s.empty())
	{
		int left = s.top(); s.pop();
		int right = s.top(); s.pop();
		begin = left;
		end = right;
		mid = a[(begin + end) / 2];
		while (begin < end)
		{
			while (a[begin] < mid) begin++;
			while (a[end] > mid) end--;
			if (begin <= end)
				swap(a[begin++], a[end--]);
		}
		if (begin < right)
		{
			s.push(right);
			s.push(begin);
		}
		if (end > left)
		{
			s.push(end);
			s.push(left);
		}
	}
}


//归并排序
void Merge(int* src, int* dest, 
		   int begin1, int end1, int begin2, int end2)
{
	assert(src&&dest);
	int index = begin1;//两个区间挨着
	while (begin1 < end1&&begin2 < end2)
	{
		if (src[begin1] < src[begin2])
		{
			dest[index++] = src[begin1++];
		}
		else
		{
			dest[index++] = src[begin2++];
		}
	}
	if (begin1 < end1)
	{
		while (begin1 < end1)
			dest[index++] = src[begin1++];
	}
	else
	{
		while (begin2 < end2)
			dest[index++] = src[begin2++];
	}
}
void _MergeSort(int* src, int* dst, int left, int right)
{
	if (left < right - 1)
	{
		int mid = left + ((right - left)/2);
		_MergeSort(src, dst, left, mid);
		_MergeSort(src, dst, mid, right);
		Merge(src, dst, left, mid, mid, right);
		memcpy(src + left, dst + left, sizeof(int)*(right - left));
	}
}
void MergeSort(int *a, size_t size)
{
	int *dst = new int[size];
	_MergeSort(a, dst, 0, 10);
	delete[] dst;
}
void SortTest()
{
	
	//InsertSort<int>(a, 10);
	//ShellSort<int>(a, 10);
	//SelectSort<int>(a, 10);
	//HeapSort<int>(a, 10);
	//QuickSort(a, 0, 9);
	//QuickSort_2(a, 0, 9);
	//QuickSort_3(a, 0, 9);
	//MergeSort(a, 10);
	QuickSort_Non(a, 0, 9);
	PrintArray(a, 10);
}
