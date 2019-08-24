// 2019 年 8 月 24 日
// 多种排序算法的实现比较
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>   

using namespace std;
const bool display = false;
class Sort
{
	private:
		clock_t start, end;
		vector<int> data;
		vector<int> origin_data;
		int N;
		void display(vector<int> nums)
		{
			for (auto var : nums)
			{
				cout << var << " ";
			}
			cout << endl;
		}
		void recruiseQuickSort(int left, int right)
		{
			vector<int> less;
			vector<int> greater;

			if (left >= right)
			{
				return;
			}
			int tmp = data[left];

			// 分治法
			for (int i = left + 1; i < right; i++)
			{
				if (data[i] < tmp)
				{
					less.push_back(data[i]);
				}
				else
				{
					greater.push_back(data[i]);
				}
			}

			for (int i = left; i < right; i++)
			{
				if (i < left + less.size())
				{
					data[i] = less[i - left];
				}
				else if (i == left + less.size())
				{
					data[i] = tmp;
				}
				else
				{
					data[i] = greater[i - left - less.size() - 1];
				}
			}

			recruiseQuickSort(left, left + less.size());
			recruiseQuickSort(left + less.size() + 2, right);
			return;
		}
	public:
		Sort(int N = 100)
		{
			for (int i = 0; i <  N; i++)
			{
				origin_data.push_back(i + 1);
			} 

			// 快排是一种不稳定的算法，故采用打乱的不重复序列进行排序
			random_shuffle(origin_data.begin(), origin_data.end());
			return;
		}

		// 快速排序
		void quickSort()
		{
			data = origin_data;
			start = clock();
			recruiseQuickSort(0, data.size());
			end = clock();

			double endtime = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
			cout << "Total time of quick sort : " << endtime  << " ms " << endl;
			return;
		}

		// 选择排序
		void selectSort()
		{
			data = origin_data;
			int tmp;
			start = clock();
			for (int i = 0; i < data.size(); i++)
			{
				for (int j = i + 1; j < data.size(); j++)
				{
					if (data[i] > data[j])
					{
						tmp = data[i];
						data[i] = data[j];
						data[j] = tmp;
					}
				}
			}
			end = clock();
			double endtime = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
			cout << "Total time of select sort : " << endtime << " ms " << endl;

			return;
		}

		// 冒泡排序
		void bubbleSort()
		{
			data = origin_data;
			int tmp;
			start = clock();
			for (int i = 0; i < data.size() - 1; i++)
			{
				for (int j = 0; j < data.size() - 1 - i; j++)
				{
					if (data[j] > data[j + 1])
					{
						tmp = data[j + 1];
						data[j + 1] = data[j];
						data[j] = tmp;
					}
				}
			}

			end = clock();

			
			double endtime = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
			cout << "Total time of buddle sort : " << endtime << " ms " << endl;
			return;
		}
};

int main()
{
	Sort(1e4).quickSort();
	Sort(1e4).selectSort();
	Sort(1e4).bubbleSort();
	return 0;
}