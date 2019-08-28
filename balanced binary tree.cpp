// 2019/08/28   平衡二叉树
// 测试样例：  12 月份缩写
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ------------------ 为树定义的变量类型 --------------------
typedef struct AVLNode *AVLTree;
typedef struct AVLNode
{
	string Data;
	AVLTree Left;
	AVLTree Right;
	int Height;           // 树高
	AVLNode(string x): Data(x),Left(NULL),Right(NULL),Height(1){}
};


class Solution
{
	private:
		int Max(int a, int b)
		{
			return a > b ? a : b;
		}
		int GetHeight(AVLTree root)              // 计算树的高度 
		{
			if (root)
			{
				int MaxL, MaxR, MaxH;
				MaxL = GetHeight(root->Left);    // 计算左子树的高度
				MaxR = GetHeight(root->Right);   // 计算右子树的高度
				MaxH = Max(MaxL, MaxR) + 1;
				return MaxH;
			}
			return 0;
		}
		// 树的旋转操作作为私有成员函数，不对用户开放
		AVLTree SingleLeftRotation(AVLTree A)
		{
			AVLTree B = A->Left;
			A->Left = B->Right;
			B->Right = A;
			
			// 更新树的高度
			A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
			B->Height = Max(GetHeight(B->Left), A->Height) + 1;

			return B;
		}
		AVLTree SingleRightRotation(AVLTree A)
		{
			AVLTree B = A->Right;
			A->Right = B->Left;
			B->Left = A;

			// 更新树的高度
			A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
			B->Height = Max(GetHeight(B->Right), A->Height) + 1;

			return B;
		}
		AVLTree DoubleLeftRightRotation(AVLTree A)
		{
			A->Left = SingleRightRotation(A->Left);
			return SingleLeftRotation(A);
		}
		AVLTree DoubleRightLeftRotation(AVLTree A)
		{
			A->Right = SingleLeftRotation(A->Right);
			return SingleRightRotation(A);
		}
	public:
		AVLTree Find(AVLTree root, string x)     // 查找操作
		{
			while (root)
			{
				if (root->Data > x)
				{
					root = root->Right;
				}
				else if (root->Data < x)
				{
					root = root->Left;
				}
				else
				{
					break;
				}
			}
			return root;
		}

		AVLTree Insert(AVLTree root, string s)
		{
			if (!root)
			{
				root = new AVLNode(s);
			}
			else if (s < root->Data)
			{
				root->Left = Insert(root->Left, s);
				if (GetHeight(root->Left) - GetHeight(root->Right) == 2)
				{
					// 二叉树的平衡性被破坏，需要进行旋转操作
					if (s < root->Left->Data)     // LL 不平衡，需要进行左单旋
					{
						root = SingleLeftRotation(root);
					}                             // LR 不平衡，需要进行左-右双旋          
					else
					{
						root = DoubleLeftRightRotation(root);
					}
				}
			}
			else if (s > root->Data)
			{
				root->Right = Insert(root->Right, s);
				if (GetHeight(root->Left) - GetHeight(root->Right) == -2)
				{
					// 二叉树的平衡性被破坏，需要进行旋转操作
					if (s > root->Right->Data)    // RR 不平衡，需要进行右单旋
					{
						root = SingleRightRotation(root);
					}
					else                          // RL 不平衡，需要进行右-左单旋
					{
						root = DoubleRightLeftRotation(root);
					}
				}

			}
			//  默认二叉树中不存在相同的元素（这种情况需要另外进行讨论）

			root->Height = Max(GetHeight(root->Left), GetHeight(root->Right)) + 1;
			return root;
		}

};

int main()
{
	// constexpr int null = 0, *p = null;
	vector<string> month{ "Jan","Feb","Mar","Apr","May","Jun",
								"Jul","Aug","Sept","Oct","Nov","Dec" };
	//vector<string> month{ "Mar","May","Nov","Aug","Apr","Jan",
	//						"Dec","July","Feb" };
	Solution t;
	AVLTree root = NULL;
	for (auto m : month)
	{
		root = t.Insert(root, m);      // 依次插入十二个月份的信息构造二叉平衡树
	}
	
	return 0;
}
