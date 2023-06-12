#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_NAME 20
#define MAX_ID 15
#define MAX_ISBN 15
#define MAX_PUBLISHERS 35
#define MAX_AUTHOR 10
#define CLASSNUMBER 10
#define	CAPACITY 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <Windows.h>
typedef struct book
{
	//������
	char publishers[MAX_PUBLISHERS];
	//����
	char name[MAX_NAME];
	//ͼ����
	char id[MAX_ID];
	//ISBN���
	char ISBN[MAX_ISBN];
	//�۸�
	int price;
	//����
	char author[MAX_AUTHOR];
	//�����
	char classNumber[CLASSNUMBER];
	//ͼ��״̬ -1ͼ������޴��� 0�ڹ� 1���
	int status;

}book;
typedef struct booksList
{
	int capacity;
	int size;
	struct book* data;
}booksList;
enum
{
	EXIT,
	ADD,
	DEL,
	QUERY,
	MODIFY,
	SORT,
	SHOW
};

//��ʼ��booksys
void booksysInit(struct booksList* pbooksList);
//���ͼ��
void addBook(struct booksList* pbooksList);
//��ʾ����ͼ��
void showAllBooks(const struct booksList* pbooksList);
//ɾ��ָ����ͼ��
void delBook(struct booksList* pbooksList);
//����ָ����ͼ��
void findBook(const struct booksList* pbooksList);
//�޸�ָ����ͼ��
void modifyBook(struct booksList* pbooksList);
//��ϵͳ�е�ͼ������
void sortData(struct booksList* pbooksList);
//���ͼ��ϵͳ�����Ƿ���㣬������
void chackCapacity(booksList* pbooksList);
//����data�е����ݵ�data.bat��
void saveData(booksList* pbooksList);
//�ͷ�ͼ����Ϣ��dataָ�룩��ָ��Ŀɱ��ڴ�ռ�
void freeData(booksList* pbooksList);