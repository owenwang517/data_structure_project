#include<iostream> 
#include<iostream>
using namespace std;
class BinTree;
class BinTreeNode{
	public:
		friend class BinTree;
		BinTreeNode(){Lchild=NULL;Rchild=NULL;}
		BinTreeNode* Getleft(){return Lchild;}
	public:
		char data;
		BinTreeNode* Lchild;
		BinTreeNode* Rchild;
};

class BinTree{
	public:
		BinTree(){root=new BinTreeNode;}
		BinTree(char value,BinTreeNode* left,BinTreeNode* right);
		void Create(BinTreeNode* &root);
		void Create(){
			Create(root);
		}
		void DeleteAll();
		int Isempty();
		void Preorder(BinTreeNode* cur);
		void Inorder(BinTreeNode* cur);
		void Postorder(BinTreeNode* cur);
		void Print();
		int Equal(BinTreeNode* ra,BinTreeNode* rb);
		int Leafnum(BinTreeNode* cur);
		int Depth(BinTreeNode* cur)const;
		BinTreeNode* Getroot(){
			return root;
		}
	protected:
		BinTreeNode* root;
};

void BinTree::Create(BinTreeNode* &r){
	char ch;
	cin>>ch;
	if(ch=='#') r=NULL;
	else{
		r=new BinTreeNode;
		r->data=ch;
		Create(r->Lchild);
		Create(r->Rchild);
	}
}

void BinTree::Preorder(BinTreeNode* cur){
	if(cur!=NULL){
		cout<<cur->data<<" ";
		Preorder(cur->Lchild);
		Preorder(cur->Rchild);
	}
}

void BinTree::Inorder(BinTreeNode* cur){
	if(cur!=NULL){
		Inorder(cur->Lchild);
		cout<<cur->data<<" ";
		Inorder(cur->Rchild);
	}
}

void BinTree::Postorder(BinTreeNode* cur){
	if(cur!=NULL){
		Postorder(cur->Lchild);
		Postorder(cur->Rchild);
		cout<<cur->data<<" ";
	}
}

void BinTree::Print(){
	cout<<"前序遍历结果：";
	Preorder(root);
	cout<<endl;
	cout<<"中序遍历结果：";
	Inorder(root);
	cout<<endl;
	cout<<"后序遍历结果：";
	Postorder(root);
	cout<<endl;
}

int BinTree::Equal(BinTreeNode* a,BinTreeNode* b){
	int i;
	if(a==NULL&&b==NULL) return 1;
	else if(a!=NULL&&b!=NULL&&Equal(a->Lchild,b->Lchild)&&Equal(a->Rchild,b->Rchild)) return 1;
	return 0;
}

int BinTree::Leafnum(BinTreeNode* cur){
	if(cur==NULL) return 0;
	if(cur->Lchild==NULL&&cur->Rchild==NULL) return 1;
	else return Leafnum(cur->Lchild)+Leafnum(cur->Rchild);
}

int Max(int a,int b){
	if(a>b) return a;
	else return b;
}

int BinTree::Depth(BinTreeNode* cur)const{
	if(cur==NULL) return 0;
	else return Max(Depth(cur->Lchild),Depth(cur->Rchild))+1;
}

int main(){
	BinTree tree;
	BinTreeNode* r;
	tree.Create();
	r=tree.Getroot();
	tree.Print();
	return 0;
}
