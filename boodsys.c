#include "booksys.h"
enum
{
	nochange,
	name,
	id,
	price,
	ISBN,
	publishers
};

static void showBook(book* b)
{
	printf("\n图书编号：%s\n书名：    %s\n作者：    %s\n出版社：  %s\nISBN：    %s\n分类号：  %s\n价格：    %d\n图书状态：%s\n\n",
		b->id,
		b->name,
		b->author,
		b->publishers,
		b->ISBN,
		b->classNumber,
		b->price,
		b->status == 0 ? "在馆" : "借出");
}


static void showMenu()
{
	printf("************************\n");
	printf("***1.姓名      2.性别***\n");
	printf("***3.年龄      4.电话***\n");
	printf("***5.住址      0.默认***\n");
	printf("************************\n");
}
int compare_name(const void* a, const void* b)
{
	return strcmp(((struct book*)a)->name, ((struct book*)b)->name);
}
int compare_id(const void* a, const void* b)
{
	return strcmp(((struct book*)a)->id, ((struct book*)b)->id);
}
int compare_price(const void* a, const void* b)
{
	return (((struct book*)a)->price - ((struct book*)b)->price);
}
int compare_ISBN(const void* a, const void* b)
{
	return strcmp(((struct book*)a)->ISBN, ((struct book*)b)->ISBN);
}
int compare_publishers(const void* a, const void* b)
{
	return strcmp(((struct book*)a)->publishers, ((struct book*)b)->publishers);
}

void chackCapacity(booksList* pbooksList)
{
	if (pbooksList->size == pbooksList->capacity)
	{
		book* ret = (book*)realloc(pbooksList->data, (pbooksList->capacity += 2) * sizeof(book));
		if (ret == NULL)
		{
			printf("%s\n", strerror(errno));
		}
		else
		{
			pbooksList->data = ret;
		}
		printf("扩容成功\n");
	}
}

void booksysInit(struct booksList* pbooksList)
{
	FILE* fp = fopen("data.dat", "rb");
	if (fp == NULL)
	{
		perror("open data.dat:");
		return;
	}
	else
	{
		book* ret = NULL;
		book tmp = { 0 };
		ret = (book*)malloc(CAPACITY * sizeof(book));
		if (ret == NULL)
		{
			printf("%s\n", strerror(errno));
		}
		else
		{
			pbooksList->data = ret;
		}
		pbooksList->capacity = CAPACITY;
		pbooksList->size = 0;
		while (fread(&tmp, sizeof(book), 1, fp))
		{
			pbooksList->data[pbooksList->size] = tmp;
			pbooksList->size++;
			chackCapacity(pbooksList);
		}
	}
	fclose(fp);
	fp = NULL;
}

void addBook(struct booksList* pbooksList)
{
	if (pbooksList->size == pbooksList->capacity)
	{
		book* ret = (book*)realloc(pbooksList->data, (pbooksList->capacity += 2) * sizeof(book));
		if (ret == NULL)
		{
			printf("%s\n", strerror(errno));
		}
		else
		{
			pbooksList->data = ret;
		}
		printf("扩容成功\n");
	}
	printf("请输入图书编号：");
	scanf("%s", pbooksList->data[pbooksList->size].id);

	printf("请输入图书名：");
	scanf("%s", pbooksList->data[pbooksList->size].name);

	printf("请输入作者姓名：");
	scanf("%s", pbooksList->data[pbooksList->size].author);

	printf("请输入图书的出版社：");
	scanf("%s", pbooksList->data[pbooksList->size].publishers);

	printf("请输入图书ISBN编号：");
	scanf("%s", pbooksList->data[pbooksList->size].ISBN);

	printf("请输入图书的分类号：");
	scanf("%s", pbooksList->data[pbooksList->size].classNumber);

	printf("请输入图书价格：");
	scanf("%d", &pbooksList->data[pbooksList->size].price);

	printf("请输入图书状态(0在馆 1借出)：");
	scanf("%d", &pbooksList->data[pbooksList->size].status);

	pbooksList->size++;

	system("cls");
	printf("添加成功\n");
}
static int locatByName(const struct booksList* pbooksList, char name[MAX_NAME])
{
	int i = 0;
	for (;i < pbooksList->size;i++)
	{
		if (0 == strcmp(pbooksList->data[i].name, name))
			return i;
	}
	return -1;
}
void delBook(struct booksList* pbooksList)
{
	if (pbooksList->size == 0)
	{
		printf("没有图书，请添加图书后再试\n");
	}
	else
	{
		char name[MAX_NAME];
		int ret = 0;
		printf("请输入图书名：");
		scanf("%s", name);
		if (-1 == (ret = locatByName(pbooksList, name)))
		{
			printf("未查找到该图书\n");
		}
		else
		{
			for (;ret < pbooksList->size;ret++)
			{
				pbooksList->data[ret] = pbooksList->data[ret + 1];
			}
			pbooksList->size--;

			system("cls");
			printf("删除成功\n");
		}
	}
}

void findBook(const struct booksList* pbooksList)
{
	if (pbooksList->size == 0)
	{
		printf("没有图书，请添加图书后再试\n");
	}
	else
	{
		char name[MAX_NAME];
		int ret = 0;
		system("cls");
		printf("请输入图书名：");
		scanf("%s", name);
		ret = locatByName(pbooksList, name);
		if (ret == -1)
		{
			printf("未查找到该图书\n");
		}
		else
		{
			showBook(&(pbooksList->data[ret]));
		}
	}
}

void modifyBook(struct booksList* pbooksList)
{
	if (pbooksList->size == 0)
	{
		printf("通讯录为空，请添加联系人后再试\n");
	}
	else
	{
		char name[MAX_NAME];
		int ret;
		printf("请输入要修改的联系人姓名：");
		scanf("%s", name);
		ret = locatByName(pbooksList, name);
		if (ret == -1)
			printf("未查找到该联系人\n");
		else
		{
			printf("请输入联系人姓名：");
			scanf("%s", pbooksList->data[ret].name);
			printf("请输入联系人性别：");
			scanf("%s", pbooksList->data[ret].id);
			printf("请输入联系电话号码：");
			scanf("%s", pbooksList->data[ret].ISBN);
			printf("请输入联系人年龄：");
			scanf("%d", &pbooksList->data[ret].price);
			printf("请输入联系人住址：");
			scanf("%s", pbooksList->data[ret].publishers);
			printf("修改成功\n");
		}
	}
}

void sortData(struct booksList* pbooksList)
{
	if (pbooksList->size == 0)
	{
		printf("没有图书，请添加图书后再试\n");
	}
	else if (pbooksList->size == 1)
	{
		printf("排序成功\n");
	}
	else
	{
		int input = 0;
		showMenu();
		scanf("%d", &input);
		switch (input)
		{
		case name:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_name);
			printf("排序成功\n");
			break;
		case id:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_id);
			printf("排序成功\n");
			break;
		case price:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_price);
			printf("排序成功\n");
			break;
		case ISBN:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_ISBN);
			printf("排序成功\n");
			break;
		case publishers:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_publishers);
			printf("排序成功\n");
			break;
		case nochange:
			printf("排序成功\n");
			break;
		default:printf("暂无该排序方式\n");
		}
	}
}

void showAllBooks(const struct booksList* pbooksList)
{
	system("cls");
	if (pbooksList->size == 0)
	{
		printf("\n没有图书，请添加图书后再试\n\n");
	}
	else
	{
		int i = 0;
		for (i = 0;i < pbooksList->size;i++)
		{
			showBook(&(pbooksList->data[i]));
		}
	}
}

void saveData(booksList* pbooksList)
{
	FILE* fp = fopen("data.dat", "wb");
	if (fp == NULL)
	{
		perror("open data.dat");
		return;
	}
	else
	{
		fwrite(pbooksList->data, sizeof(book), pbooksList->size, fp);
	}
	fclose(fp);
	fp = NULL;
}

void freeData(booksList* pbooksList)
{
	free(pbooksList->data);
	pbooksList->data = NULL;
}