// 2019/08/27  二叉搜索树的插入、删除和查找代码
#include <iostream>

using namespace std;

// ------------------ 为树定义的变量类型 --------------------
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x),left(NULL),right(NULL){ }
};

//class Solution 
//{
//	private:
//		typedef enum
//		{
//			num,             // 操作数
//			opt 		     // 运算符
//		}exp_type;
//		exp_type Type(char ch)
//		{
//			exp_type ret;
//			switch (ch)
//			{
//				case '+':
//				case '-':
//				case '*':
//				case '/':   ret = opt;  break;
//				default:    ret = num;           // 表达式中不包含有其它字符
//			}
//			return ret;
//		}
//	public:
//		TreeNode* CreateBinTree(const string exp)
//		{
//			TreeNode* root;                 
//			return root;
//		}
//};

class Solution
{
	private:
		TreeNode* FindMin(TreeNode* root)
		{
			if (root)         // 防止空树报错
			{
				while (root->left)
				{
					root = root->left;
				}
			}
			return root;
		}
		TreeNode* FindMax(TreeNode* root)
		{
			if (root)
			{
				while (root->right)
				{
					root = root->right;
				}
			}
			return root;
		}
	public:
		TreeNode* Find(TreeNode* root, int x)    // 查找操作
		{
			while (root)
			{
				if (root->val > x)
				{
					root = root->right;
				}
				else if (root->val < x)
				{
					root = root->left;
				}
				else
				{
					break;
				}
			}
			return root;
		}

		TreeNode* Insert(TreeNode* root, int x)      // 向二叉搜素树插入元素，输入：树的的根结点地址，输出：树的插入位置地址
		{
			if (!root)        // 空树直接创建一个结点即可
			{
				root = new TreeNode(x);
			}
			else
			{
				if (x < root->val)
				{
					root->left = Insert(root->left, x);     // 递归插入左子树，并返回插入结点地址
				}
				else if (x > root->val)
				{
					root->right = Insert(root->right, x);
				}
				// 相同元素不进行任何操作进行
			}
			return root;
		}

		TreeNode* CreateTree(vector<int> datas)      // 创建二叉搜索树
		{
			TreeNode* root = NULL;
			for (int i = 0; i < datas.size(); i++)
			{
				if (i == 0)
				{
					root = Insert(root, datas[i]);
				}
				else
				{
					Insert(root, datas[i]);
				}
			}
			return root;
		}

		TreeNode* Delete(TreeNode* root, int x)
		{
			TreeNode* Tmp;
			if (!root)
			{
				cout << "找不到需要删除的元素" << endl;
			}
			else
			{
				if (x > root->val)
				{
					root->right = Delete(root->right, x);
				}
				else if (x < root->val)
				{
					root->left = Delete(root->left, x);
				}
				else            // 确定待删除元素的位置
				{
					if (root->left && root->right)
					{
						Tmp = FindMax(root->left);
						root->val = Tmp->val;
						root->left = Delete(root->left, x);
					}
					else        // 被删除的结点至多只有一个子结点
					{
						Tmp = root;
						if (!Tmp->left)      // 只有右子树
							root = root->right;
						else
							root = root->left;
						delete Tmp;
					}
				}
			}
			return root;
		}

};

int main()
{
	Solution T;
	TreeNode* root = T.CreateTree({ 30,15,41,50,33,35,34 });
	T.Delete(root, 35);
	
	return 0;
}
