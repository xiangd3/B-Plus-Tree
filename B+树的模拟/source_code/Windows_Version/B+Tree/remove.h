#ifndef remove_h
#define remove_h
#include "node.h"

//������������
void leaf_balance(node*& root, delay_count& retarder)
{
	//Ҷ�����
	node* pare = root->parents;
	if (root->number < (l + 1) / 2)//���̫�٣���Ҫ����
	{
		if (!pare)//�����ڵ�Ϊnullptr����Ϊ��Ҷ�ڵ�
		{
			if (!(root->number))root = nullptr;//��ȫɾ�գ�����Ϊnullptr
			return;//�����ڽ�ڵ�ͺϲ��Ŀ��ܣ�ֱ�ӷ���
		}
		//��ȡ�������������˫�׽��ĵڼ�������λ��
		int pos = get_position(root);
		if (pos == 0)//��Ϊ����˵Ľڵ�
		{
			node* bro = (pare->child)[1];//�����ܽ���Ľڵ��͸��ϲ�
			retarder.delay();
			if (bro->number == (int)((l + 1) / 2))//�����Ҳֻ�Ǹոպ����㣬�����ڵ�ϲ�
			{
				for (int i = 0; i < bro->number; i++)//���������нڵ㶼���Ƶ�rootԭ�ڵ��
				{
					(root->block)[root->number + i].key = (bro->block)[i].key;
					(root->block)[root->number + i].value = (bro->block)[i].value;
				}
				root->number += bro->number;//����root�ڵ���
				delete bro;//ɾ�����ڵ�
				(pare->key)[0] = (pare->key)[1];//���ĸ��ڵ���root��keyֵ
				for (int i = 1; i < pare->number - 1; i++)//�����ڵ��key��ָ������ǰ��һλ
				{
					(pare->key)[i] = (pare->key)[i + 1];
					(pare->child)[i] = (pare->child)[i + 1];
				}
				pare->number--;//���ĸ��ڵ���
			}
			else {//������ж���Ľڵ㣬���һ��
				//�������С�Ľڵ㸴�Ƶ�rootԭ�ڵ��
				(root->block)[root->number].key = (bro->block)[0].key;
				(root->block)[root->number].value = (bro->block)[0].value;
				root->number++;//����root�ڵ���
				(pare->key)[0] = (bro->block)[0].key;//���ĸ��ڵ���root��keyֵ
				left_move(bro, 0);//�����ڵ��еĿ���������һλ
			}
		}
		else if (pos == pare->number - 1)//��Ϊ���Ҷ˵Ľڵ㣬����������������
		{
			retarder.delay();
			node* bro = (pare->child)[pos - 1];
			if (bro->number == (int)((l + 1) / 2))
			{
				for (int i = 0; i < root->number; i++)
				{
					(bro->block)[bro->number + i].key = (root->block)[i].key;
					(bro->block)[bro->number + i].value = (root->block)[i].value;
				}
				bro->number += root->number;
				delete root;
				root = nullptr;
				(pare->key)[pos - 1] = (pare->key)[pos];
				pare->number--;
			}
			else {
				right_move(root, 0);
				(root->block)[0].key = (bro->block)[bro->number - 1].key;
				(root->block)[0].value = (bro->block)[bro->number - 1].value;
				bro->number--;
				(pare->key)[pos - 1] = (bro->block)[bro->number - 1].key;
			}
		}
		else {//��Ϊ�м�ڵ�
			node* bbro = (pare->child)[pos + 1];
			node* lbro = (pare->child)[pos - 1];
			retarder.delay();
			retarder.delay();
			if (lbro->number > (int)((l + 1) / 2))//���ܵܽڵ��ж࣬���һ��
			{
				right_move(root, 0);
				(root->block)[0].key = (lbro->block)[lbro->number - 1].key;
				(root->block)[0].value = (lbro->block)[lbro->number - 1].value;
				lbro->number--;
				(pare->key)[pos - 1] = (lbro->block)[lbro->number - 1].key;
			}
			else if (bbro->number > (int)((l + 1) / 2))//���ܵܽڵ�ոպã��ָ��ڵ��ж࣬���һ��
			{
				(root->block)[root->number].key = (bbro->block)[0].key;
				(root->block)[root->number].value = (bbro->block)[0].value;
				root->number++;
				(pare->key)[pos] = (bbro->block)[0].key;
				left_move(bbro, 0);
			}
			else {//���ܸܵ��ڵ㶼�ոպã���͵ܵܽڵ�ϲ�
				for (int i = 0; i < root->number; i++)
				{
					(lbro->block)[lbro->number + i].key = (root->block)[i].key;
					(lbro->block)[lbro->number + i].value = (root->block)[i].value;
				}
				lbro->number += root->number;
				delete root;
				root = nullptr;
				(pare->key)[pos - 1] = (pare->key)[pos];
				for (int i = pos; i < pare->number - 1; i++)
				{
					(pare->key)[i] = (pare->key)[i + 1];
					(pare->child)[i] = (pare->child)[i + 1];
				}
				pare->number--;
			}
		}
	}
}

void nleaf_balance(node*& root, delay_count& retarder)
{
	//��Ҷ�����
	node* pare = root->parents;
	if (pare)//���Ǹ������
	{
		if (root->number < ((m + 1) / 2))//���̫�٣���Ҫ����
		{
			int pos = get_position(root);
			if (pos == 0)//��Ϊ����˵Ľڵ�
			{
				node* bro = (pare->child)[1];//�����ܽ���Ľڵ��͸��ϲ�
				retarder.delay();
				if (bro->number == (int)((m + 1) / 2))//�����Ҳֻ�Ǹոպ����㣬�����ڵ�ϲ�
				{
					for (int i = 0; i < bro->number; i++)
					{
						(root->key)[root->number + i] = (bro->key)[i];
						(root->child)[root->number + i] = (bro->child)[i];
						(bro->child)[i]->parents = root;//��Ҷ��ͬ������Ҫ�޸ľ��ƶ����ӽڵ�ĸ��ڵ�
					}
					root->number += bro->number;
					delete bro;
					(pare->key)[0] = pare->key[1];
					for (int i = 1; i < pare->number - 1; i++)
					{
						(pare->key)[i] = (pare->key)[i + 1];
						(pare->child)[i] = (pare->child)[i + 1];
					}
					pare->number--;
				}
				else {//������ж���Ľڵ㣬���һ��
					(root->key)[root->number] = (bro->key)[0];
					(root->child)[root->number] = (bro->child)[0];
					(bro->child)[0]->parents = root;//��Ҷ��ͬ������Ҫ�޸ľ��ƶ����ӽڵ�ĸ��ڵ�
					root->number++;
					(pare->key)[0] = (bro->key)[0];
					for (int i = 0; i < bro->number - 1; i++)
					{
						(bro->key)[i] = (bro->key)[i + 1];
						(bro->child)[i] = (bro->child)[i + 1];
					}
					bro->number--;
				}
			}
			else if (pos == pare->number - 1)//��Ϊ���Ҷ˵Ľڵ㣬����������������
			{
				node* bro = (pare->child)[pos - 1];
				retarder.delay();
				if (bro->number == (int)((l + 1) / 2))
				{
					for (int i = 0; i < root->number; i++)
					{
						(bro->key)[bro->number + i] = (root->key)[i];
						(bro->child)[bro->number + i] = (root->child)[i];
						(root->child)[i]->parents = bro;
					}
					bro->number += root->number;
					delete root;
					root = nullptr;
					(pare->key)[pos - 1] = (pare->key)[pos];
					pare->number--;
				}
				else {
					for (int i = 0; i < root->number; i++)
					{
						(root->key)[i + 1] = (root->key)[i];
						(root->child)[i + 1] = (root->child)[i];
					}
					(root->key)[0] = (bro->key)[bro->number - 1];
					(root->child)[0] = (bro->child)[bro->number - 1];
					(bro->child)[bro->number - 1]->parents = root;
					root->number++;
					bro->number--;
					(pare->key)[pos - 1] = (bro->key)[bro->number - 1];
				}
			}
			else {//��Ϊ�м�ڵ�
				node* bbro = (pare->child)[pos + 1];
				node* lbro = (pare->child)[pos - 1];
				retarder.delay();
				retarder.delay();
				if (lbro->number > (int)((m + 1) / 2))//���ܵܽڵ��ж࣬���һ��
				{
					for (int i = 0; i < root->number; i++)
					{
						(root->key)[i + 1] = (root->key)[i];
						(root->child)[i + 1] = (root->child)[i];
					}
					(root->key)[0] = (lbro->key)[lbro->number - 1];
					(root->child)[0] = (lbro->child)[lbro->number - 1];
					(lbro->child)[lbro->number - 1]->parents = root;//��Ҷ��ͬ������Ҫ�޸ľ��ƶ����ӽڵ�ĸ��ڵ�
					root->number++;
					lbro->number--;
					(pare->key)[pos - 1] = (lbro->key)[lbro->number - 1];
				}
				else if (bbro->number > (int)((l + 1) / 2))//���ܵܽڵ�ոպã��ָ��ڵ��ж࣬���һ��
				{
					(root->key)[root->number] = (bbro->key)[0];
					(root->child)[root->number] = (bbro->child)[0];
					(bbro->child)[0]->parents = root;//��Ҷ��ͬ������Ҫ�޸ľ��ƶ����ӽڵ�ĸ��ڵ�
					root->number++;
					(pare->key)[pos] = (bbro->key)[0];
					for (int i = 0; i < bbro->number - 1; i++)
					{
						(bbro->key)[i] = (bbro->key)[i + 1];
						(bbro->child)[i] = (bbro->child)[i + 1];
					}
					bbro->number--;
				}
				else {//���ܸܵ��ڵ㶼�ոպã���͵ܵܽڵ�ϲ�
					for (int i = 0; i < root->number; i++)
					{
						(lbro->key)[lbro->number + i] = (root->key)[i];
						(lbro->child)[lbro->number + i] = (root->child)[i];
						(root->child)[i]->parents = lbro;//��Ҷ��ͬ������Ҫ�޸ľ��ƶ����ӽڵ�ĸ��ڵ�
					}
					lbro->number += root->number;
					delete root;
					root = nullptr;
					(pare->key)[pos - 1] = (pare->key)[pos];
					for (int i = pos; i < pare->number - 1; i++)
					{
						(pare->key)[i] = (pare->key)[i + 1];
						(pare->child)[i] = (pare->child)[i + 1];
					}
					pare->number--;
				}
			}
		}
	}
	else {//Ϊ�������
		if (root->number == 1)//������һ������
		{
			root = (root->child)[0];//���³�Ϊ�¸�
			delete root->parents;//ɾ��ԭ��
			root->parents = nullptr;//���¸��ĸ��ڵ���Ϊnullptr
		}
	}
}

bool remove(node*& root, keytype target, delay_count& retarder)
{
	//ʹ��bottom-upģʽ�������µ�Ҷ��ɾ��Ҷ�нڵ㣬��ͨ���ݹ����Ͻ��е���
	if (!(root->leaf))
	{
		for (int i = 0; i < root->number; i++)
		{
			if (target <= (root->key)[i])
			{
				retarder.delay();
				bool tem = remove((root->child)[i], target, retarder);//����
				nleaf_balance(root, retarder);//����
				return tem;
			}
		}
		return 0;
	}
	else
	{
		for (int i = 0; i < root->number; i++)
		{
			if ((root->block)[i].key == target)//�ҵ���
			{
				if (i > 0 && i == root->number - 1)//��������һ�������ģ��ӽڵ㣬����Ҫ��������key
				{                                   //��Ϊ��Ҷ�ڵ㣬���ܳ���ֻ��һ���ӽڵ����������·����δ��󣬹���i>0
					keytype tem = (root->block)[i - 1].key;//�ݴ��µ����ֵ�����µ�key
					node* curr = root;
					while (curr->parents)//����Ϊ����������Ҫ�������ڵ��key
					{
						(curr->parents->key)[get_position(curr)] = tem;//�޸ĸ��ڵ�keyֵ
						if (curr->parents->number - 1 == get_position(curr)) curr = curr->parents;//���޸ĵĽڵ��Ǹ��ڵ�������ӣ����������޸�үү��keyֵ
						else break;
					}
				}
				left_move(root, i);//ɾ���ڵ�
				leaf_balance(root, retarder);//����
				return 1;
			}
		}
		return 0;//û�ҵ�
	}
}

#endif
