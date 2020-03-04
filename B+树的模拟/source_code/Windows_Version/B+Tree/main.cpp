#include <iostream>
#include <algorithm>
#include <queue>
#include "Retarder.h"
#include "node.h"
#include "insert.h"
#include "search.h"
#include "remove.h"
#include <time.h>
#define test_num 50
record get_rand()
{
	return record(rand() % 201, rand() % 201);
}

void test(node*& root)
{
	delay_count insert_time;
	delay_count remove_time;
	record tem_rec;
	int count = 0;
	for (int i = 0; i < test_num; i++)
	{
		count += insert(root, get_rand(), insert_time);
	}
	int tem = insert_time.get_count();
	cout << "���Բ���" << test_num << "�������¼����" << 0.02 * tem << "s" << endl;
	cout << "�ɹ�����" << count << "����¼��ȫ�������������" << endl;
	display(root);
	while (!insert(root, tem_rec=get_rand(), insert_time))
	{
		tem = insert_time.get_count();
	}
	cout << "��ʱ�ٲ�һ�������¼��" << tem_rec.key << "," << tem_rec.value << "��������" << 0.02 * (insert_time.get_count() - tem) << "s" << endl;
	cout << "��������" << endl;
	display(root);

	count = 0;
	for (int i = 0; i < test_num*2; i++)
	{
		count += remove(root, get_rand().key, remove_time);
	}
	cout << "����ɾ��" << test_num*2 << "�������¼����" << 0.02 * remove_time.get_count() << "s" << endl;
	cout << "�ɹ�ɾ��" << count << "����¼�����������������" << endl;
	display(root);
	while (!remove(root, tem_rec.key=get_rand().key, remove_time))
	{
		tem = remove_time.get_count();
	}
	cout << "��ʱ��ɾ��һ��keyΪ"<<tem_rec.key<<"�������¼������" << 0.02 * (remove_time.get_count() - tem) << "s" << endl;
	cout << "��������" << endl;
	display(root);

	clear(root);
}

int main()
{
	node* root = NULL;
	srand(time(NULL));

	test(root);

	return 0;
}

