#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#define NoInfo 0
using namespace std;

// ------------------ 为树定义的变量类型 --------------------
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x),left(NULL),right(NULL){ }
};
typedef enum
{
	PRE_ORDER,
	LEVEL_ORDER
}Method;
class Solution 
{	
	public:
		TreeNode* CreateBinTree(vector<int> data, Method m)
		{
			if (m == PRE_ORDER)
			{
				return preorderCreateBinTree(data);
			}
			else if (m == LEVEL_ORDER)
			{
				return levelorderCreateBinTree(data);
			}
			else
			{
				return NULL;
			}
		}
		// 先序遍历创建二叉树
		// 在创建二叉树时，先序遍历不同于层序遍历，其需要确定所有非空结点左右子树是否为空
		// 相较于层序遍历，其需要提供更多的信息
		TreeNode* preorderCreateBinTree(vector<int>& data)
		{
			TreeNode* T = NULL;
			TreeNode* root = T;
			stack<TreeNode*> NodeAddress;
			bool LTree = true;

			if (data[0] != NoInfo)
			{
				T = new TreeNode(data[0]);
				root = T;
				NodeAddress.push(T);
			}
			for (int i = 1; i < data.size(); i++)
			{
				if (data[i] != NoInfo)
				{
					if (LTree)
					{
						T->left = new TreeNode(data[i]);
						T = T->left;
					}	
					else
					{
						T->right = new TreeNode(data[i]);
						T = T->right;
						LTree = true;
					}	
					NodeAddress.push(T);
				}
				else
				{
					T = NodeAddress.top();
					NodeAddress.pop();
					LTree = false;
				}
			}

			return root;
		}
		TreeNode* levelorderCreateBinTree(vector<int>& data)
		{
			queue<TreeNode*> Q;
			TreeNode* root, *T;

			int i = 0;
			if (data[0] != NoInfo)
			{
				root = new TreeNode(data[0]);
				Q.push(root);
			}
			else
			{
				return NULL;
			}

			while (!Q.empty())
			{
				T = Q.front();
				Q.pop();

				i++;
				if (i >= data.size())
				{
					break;
				}
				if (data[i] == NoInfo)
				{
					T->left = NULL;
				}
				else
				{
					T->left = new TreeNode(data[i]);
					Q.push(T->left);
				}

				i++;
				if (i >= data.size())
				{
					break;
				}
				if (data[i] == NoInfo)
				{
					T->right = NULL;
				}
				else
				{
					T->right = new TreeNode(data[i]);
					Q.push(T->right);
				}
			}
			return root;
		}
		vector<int> inorderTraversal(TreeNode* root)       // 中序遍历
		{
			TreeNode* T = root;
			stack<TreeNode*> Node;

			vector<int> ans;
			while (T || !Node.empty())
			{
				while (T)
				{
					Node.push(T);
					T = T->left;
				}
				T = Node.top();
				Node.pop();
				ans.push_back(T->val);
				T = T->right;

			}
			return ans;
		}
		vector<int> preorderTraversal(TreeNode* root)      // 先序遍历
		{
			TreeNode* T = root;
			stack<TreeNode*> Node;

			vector<int> ans;
			while (T || !Node.empty())
			{
				while (T)
				{
					ans.push_back(T->val);
					Node.push(T);
					T = T->left;
				}
				T = Node.top();
				Node.pop();
				T = T->right;

			}
			return ans;
		}
		vector<int> postorderTraversal(TreeNode* root)     // 后序遍历
		{
			// 重新定义的结构体
			struct SNode
			{ 
				TreeNode* ptr;
				bool reVisit;         // 记录当前树节点的右节点是否被访问过，默认为 false
			}S;                   
			vector<int> ans;          // 记录访问顺序的变量
			stack<SNode> Node;

			S.ptr = root;
			while (S.ptr)             // 沿着左子树的方向不断入栈
			{
				S.reVisit = false;
				Node.push(S);
				S.ptr = S.ptr->left;
			}

			while (!Node.empty())
			{
				S = Node.top();

				if (!S.ptr->right || S.reVisit)   // 右子树不存在 或 右子树已经被访问过
				{
					ans.push_back(S.ptr->val);    // 访问节点
					Node.pop();
				}
				else                              // 右子树存在且没被访问过，则对其进行访问
				{
					Node.top().reVisit = true;
					
					S.ptr = S.ptr->right;         // 转向右子树
					while (S.ptr)
					{
						S.reVisit = false;
						Node.push(S);
						S.ptr = S.ptr->left;
					}
				}
			}
			return ans;
		}
		vector<int> levelorderTraversal(TreeNode* root)    // 层序遍历
		{
			vector<int> ans;
			TreeNode* T;

			if (!root)
			{
				return ans;               // 遍历结果为空
			}
			queue<TreeNode*> Q;

			Q.push(root);
			while (!Q.empty())
			{
				T = Q.front();
				ans.push_back(T->val);
				Q.pop();
				if (T->left)      Q.push(T->left);
				if (T->right)     Q.push(T->right);
			}
			return ans;
		}
		int getHeight(TreeNode* root)                            // 二叉树高度
		{
			int HL, HR, MaxH;
			if (root)
			{
				HL = getHeight(root->left);
				HR = getHeight(root->right);
				MaxH = HL > HR ? HL : HR;
				return MaxH + 1;
			}
			else
			{
				return 0;
			}
		}
};

int main()
{
	vector<int> order;
	// TreeNode* root = Solution().CreateBinTree({ 1,2,4,0,0,5,0,0,3 });
	// TreeNode* root = Solution().CreateBinTree({ 1,2,5,6,0,0,4,0,0,0,3,7,9,0,0,8 }, PRE_ORDER);
	TreeNode* root = Solution().CreateBinTree({ 1,2,3,4,5,6 }, LEVEL_ORDER);
	
	cout << "中序遍历结果: ";
	order = Solution().inorderTraversal(root);
	for (auto v : order)
	{
		cout << v << " ";
	}
	cout << endl;

	cout << "先序遍历结果: ";
	order = Solution().preorderTraversal(root);
	for (auto v : order)
	{
		cout << v << " ";
	}
	cout << endl;

	cout << "后序遍历结果: ";
	order = Solution().postorderTraversal(root);
	for (auto v : order)
	{
		cout << v << " ";
	}
	cout << endl;

	cout << "层序遍历结果: ";
	order = Solution().levelorderTraversal(root);
	for (auto v : order)
	{
		cout << v << " ";
	}
	cout << endl;

	int height = Solution().getHeight(root);
	cout << "树的高度: ";
	cout << height << endl;
	return 0;
}
