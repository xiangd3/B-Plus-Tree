#ifndef node_h
#define node_h									
#include <iostream>
#include <queue>
#include<iomanip>
#include <algorithm>
#define m 4
#define l 6		
using namespace std;

typedef int keytype;
typedef double valuetype;

struct record {
    keytype key;//��¼����key
    valuetype value;
	record(keytype key = 0, valuetype value = 0)		
	{
		this->key = key;
		this->value = value;
	}
};

//Ҷ�ڵ㺬leaf��number��block��parents����1+1+12*6+4=78<=80						�����Լ�����+���ֵܽڵ����ڵ�
//��Ҷ�ڵ㺬leaf��number��key��child��parents����1+1+4*4+4*4+4=38<=40
struct node {
    bool leaf;//�ж��Ƿ�ΪҶ�ڵ�
    unsigned char number;//��Ч��key��
	//���һ������ռ���ڷ���ʱʹ�ã����������Ϊm��l
    keytype key[m+1];//���key
    record block[l+1];//��ź�record�Ŀ�
    node* child[m+1];//����ָ��
    node* parents;//��ָ��
	node()												
	{
		leaf = 0;
		number = 0;
		parents = nullptr;
		for (int i = 0; i < m+1; i++)
		{
			key[i] = 0;
			child[i] = nullptr;
		}
		for (int i = 0; i < l+1; i++)
		{
			block[i] = record();
		}
	}
};

bool operator < (const record& a,const record& b) {
    return a.key < b.key;
}

//��ȡ�������������˫�׽��ĵڼ�������λ��
int get_position(node* obj) {
	node* pare = obj->parents;
	if (pare == NULL)return 0;
	for (int i = 0; i < pare->number; i++) {
		if ((pare->child)[i] == obj) {
			return i;
		}
	}
	return 0;
}

//��i֮�󣨲�����i����blockͬ������һλ
void left_move(node* root, int i)
{
	for (int j = i; j < root->number-1; j++)
	{
		(root->block)[j].key = (root->block)[j + 1].key;
		(root->block)[j].value = (root->block)[j + 1].value;
	}
	root->number--;
}

//��i֮�󣨰���i����blockͬ������һλ
void right_move(node* root, int i)
{
	for (int j = i; j < root->number; j++)
	{
		(root->block)[j+1].key = (root->block)[j].key;
		(root->block)[j+1].value = (root->block)[j].value;
	}
	root->number++;
}

//��i֮��Ľ��ͬ������һλ
void right_shift(node* parent, int position) {
	for (int i = parent->number; i > position; i--) {
		(parent->child)[i] = (parent->child)[i - 1];
		(parent->key)[i] = (parent->key)[i - 1];
	}
	parent->number++;
}

void print(node* root) {
    queue<node*>temp;
    temp.push(root);
    while (temp.size() >= 1) {
        if (!temp.front()->leaf) {
            for (int i = 0; i < temp.front()->number; i++) {
                temp.push(temp.front()->child[i]);
            }
            for (int i = 0; i < temp.front()->number; i++) {
                cout << temp.front()->key[i] << " ";
            }
            temp.pop();
            
        }
        else {
            cout << "record(" << (int)temp.front()->number << "):";
            for (int i = 0; i < temp.front()->number; i++) {
                cout << "(" << temp.front()->block[i].key << "," << temp.front()->block[i].value << ") ";
            }
            temp.pop();
        }
        cout << endl;
    }
}

//�������
void display(node* root)
{
	if (root)
	{
		int i = 0;
		queue<node*> tem;
		queue<node*> hold;
		queue<node*> emp;
		tem.push(root);
		node* curr;
		while (tem.size())
		{
			int j = 0;
			hold = tem;
			tem = emp;
			cout << "��" << i++ << "�㣺" << endl;
			while (hold.size())
			{
				curr =hold.front();
				hold.pop();
				int num = 0;
				if(curr) num = curr->number;
				else continue;
				if (curr->leaf)
				{
					cout << "leaf" << j++ <<':'<< endl;
					cout << "   key:";
					for (int i = 0; i < num; i++) cout << setw(5) << (curr->block)[i].key;
					puts("");
					cout << "record:";
					for (int i = 0; i < num; i++) cout << setw(5) << (curr->block)[i].value;
					puts("");
				}
				else {
					cout << "node" << j++ << ':' << endl;
					for (int i = 0; i < num; i++)
					{
						tem.push(curr->child[i]);
						cout << setw(5) << curr->key[i];
					}
				}
				puts("");
			}
		}
	}
	else cout << "EMPTY" << endl;
}

void clear(node*& root) {
	if (root == NULL)return;
	if (!root->leaf) 
	{
		for (int i = 0; i < root->number; i++) clear(root->child[i]);
		delete root;
		root = NULL;
	}
	else {
		delete root;
		root = NULL;
		return;
	}
}

#endif
