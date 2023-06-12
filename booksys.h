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
	//出版社
	char publishers[MAX_PUBLISHERS];
	//书名
	char name[MAX_NAME];
	//图书编号
	char id[MAX_ID];
	//ISBN编号
	char ISBN[MAX_ISBN];
	//价格
	int price;
	//作者
	char author[MAX_AUTHOR];
	//分类号
	char classNumber[CLASSNUMBER];
	//图书状态 -1图书馆暂无此书 0在馆 1借出
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

//初始化booksys
void booksysInit(struct booksList* pbooksList);
//添加图书
void addBook(struct booksList* pbooksList);
//显示所有图书
void showAllBooks(const struct booksList* pbooksList);
//删除指定的图书
void delBook(struct booksList* pbooksList);
//查找指定的图书
void findBook(const struct booksList* pbooksList);
//修改指定的图书
void modifyBook(struct booksList* pbooksList);
//将系统中的图书排序
void sortData(struct booksList* pbooksList);
//检查图书系统容量是否充足，并扩充
void chackCapacity(booksList* pbooksList);
//保存data中的数据到data.bat中
void saveData(booksList* pbooksList);
//释放图书信息（data指针）所指向的可变内存空间
void freeData(booksList* pbooksList);