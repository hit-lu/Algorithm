#include <iostream>
#include <vector>
#define MAXDATA 10000;
using namespace std;

typedef struct HNode * Heap;
typedef struct HNode
{
	int * Data;
	int Size;
	int Capacity;
};

typedef Heap MaxHeap;
typedef Heap MinHeap;

class Solution
{
public:
	MaxHeap createHeap(int Maxize)
	{
		MaxHeap H = new struct HNode;

		H->Data = new int[Maxize];
		H->Size = 0;
		H->Capacity = Maxize;
		H->Data[0] = MAXDATA;               // 定义哨兵：大于堆中所有可能的元素的值

		return H;
	}
	bool insert(MaxHeap H, int X)
	{
		if (H->Size == H->Capacity)
		{
			return false;                   // 堆栈已满，无法插入新的元素
		}
		int i = ++H->Size;
		while (H->Data[i / 2] < X)
		{
			H->Data[i] = H->Data[i / 2];    // 上滤元素
			i = i / 2;
		}
		H->Data[i] = X;                     // 插入新的元素
		return true;

	}
	bool deleteMax(MaxHeap H)                // 最大堆是一种特殊的树结构，每次删除的必为值最大的元素
	{
		if (H->Size == 0)
		{
			return false;                    // 堆为空，返回错误
		}

		int MaxItem = H->Data[1];            // 根节点中存放有当前堆最大值
		int X = H->Data[H->Size--];          // 当前堆的规模要减小
		int Parent = 1, Child;

		while (Parent * 2 <= H->Size)
		{
			Child = Parent * 2;
			if (Child != H->Size && H->Data[Child] < H->Data[Child + 1])
			{
				Child++;                     // 指向左、右子树中值较大者
			}
			if (X >= H->Data[Child])
			{
				break;
			}
			else
			{
				H->Data[Parent] = H->Data[Child];  // 下率元素
			}
			Parent = Child;
		}
		H->Data[Parent] = X;
		return true;

	}
	void PercDown(MaxHeap& H, int p)                   // 将 H->Data[p] 为根节点的树调整为最大堆
	{
		int Parent = p, Child;
		int X = H->Data[p];
		while (Parent * 2 <= H->Size)
		{
			Child = Parent * 2;
			if (Child != H->Size && H->Data[Child] < H->Data[Child + 1])
			{
				Child++;
			}
			if (X > H->Data[Child])
			{
				break;
			}
			else
			{
				H->Data[Parent] = H->Data[Child];
			}
			Parent = Child;
		}
		H->Data[Parent] = X;
	}
	MaxHeap buildHeap(vector<int> data)
	{
		MaxHeap H = createHeap(data.size()+1);    // 此时建立的最大堆是不考虑插入新的元素的
												  // 为哨兵预留一个位置
		for (int i = 0; i < data.size(); i++)
		{
			H->Data[i + 1] = data[i];             // 层序存储元素
		}
		H->Size = data.size();

		for (int i = H->Size / 2; i > 0; i--)
		{
			PercDown(H, i);                       // 从最后一个结点的父节点开始，到根节点
		}

		return H;
	}
};
int main()
{
	Solution s;
	MaxHeap H = s.buildHeap({ 87,43,9,91,83,79,38,72,55,30,66,49 });

	s.deleteMax(H);            // 删除堆栈中的一个元素
	s.insert(H, 86);           // 向最大堆中添加一个元素

	return 0;
}