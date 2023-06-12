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
	printf("\nͼ���ţ�%s\n������    %s\n���ߣ�    %s\n�����磺  %s\nISBN��    %s\n����ţ�  %s\n�۸�    %d\nͼ��״̬��%s\n\n",
		b->id,
		b->name,
		b->author,
		b->publishers,
		b->ISBN,
		b->classNumber,
		b->price,
		b->status == 0 ? "�ڹ�" : "���");
}


static void showMenu()
{
	printf("************************\n");
	printf("***1.����      2.�Ա�***\n");
	printf("***3.����      4.�绰***\n");
	printf("***5.סַ      0.Ĭ��***\n");
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
		printf("���ݳɹ�\n");
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
		printf("���ݳɹ�\n");
	}
	printf("������ͼ���ţ�");
	scanf("%s", pbooksList->data[pbooksList->size].id);

	printf("������ͼ������");
	scanf("%s", pbooksList->data[pbooksList->size].name);

	printf("����������������");
	scanf("%s", pbooksList->data[pbooksList->size].author);

	printf("������ͼ��ĳ����磺");
	scanf("%s", pbooksList->data[pbooksList->size].publishers);

	printf("������ͼ��ISBN��ţ�");
	scanf("%s", pbooksList->data[pbooksList->size].ISBN);

	printf("������ͼ��ķ���ţ�");
	scanf("%s", pbooksList->data[pbooksList->size].classNumber);

	printf("������ͼ��۸�");
	scanf("%d", &pbooksList->data[pbooksList->size].price);

	printf("������ͼ��״̬(0�ڹ� 1���)��");
	scanf("%d", &pbooksList->data[pbooksList->size].status);

	pbooksList->size++;

	system("cls");
	printf("��ӳɹ�\n");
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
		printf("û��ͼ�飬�����ͼ�������\n");
	}
	else
	{
		char name[MAX_NAME];
		int ret = 0;
		printf("������ͼ������");
		scanf("%s", name);
		if (-1 == (ret = locatByName(pbooksList, name)))
		{
			printf("δ���ҵ���ͼ��\n");
		}
		else
		{
			for (;ret < pbooksList->size;ret++)
			{
				pbooksList->data[ret] = pbooksList->data[ret + 1];
			}
			pbooksList->size--;

			system("cls");
			printf("ɾ���ɹ�\n");
		}
	}
}

void findBook(const struct booksList* pbooksList)
{
	if (pbooksList->size == 0)
	{
		printf("û��ͼ�飬�����ͼ�������\n");
	}
	else
	{
		char name[MAX_NAME];
		int ret = 0;
		system("cls");
		printf("������ͼ������");
		scanf("%s", name);
		ret = locatByName(pbooksList, name);
		if (ret == -1)
		{
			printf("δ���ҵ���ͼ��\n");
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
		printf("ͨѶ¼Ϊ�գ��������ϵ�˺�����\n");
	}
	else
	{
		char name[MAX_NAME];
		int ret;
		printf("������Ҫ�޸ĵ���ϵ��������");
		scanf("%s", name);
		ret = locatByName(pbooksList, name);
		if (ret == -1)
			printf("δ���ҵ�����ϵ��\n");
		else
		{
			printf("��������ϵ��������");
			scanf("%s", pbooksList->data[ret].name);
			printf("��������ϵ���Ա�");
			scanf("%s", pbooksList->data[ret].id);
			printf("��������ϵ�绰���룺");
			scanf("%s", pbooksList->data[ret].ISBN);
			printf("��������ϵ�����䣺");
			scanf("%d", &pbooksList->data[ret].price);
			printf("��������ϵ��סַ��");
			scanf("%s", pbooksList->data[ret].publishers);
			printf("�޸ĳɹ�\n");
		}
	}
}

void sortData(struct booksList* pbooksList)
{
	if (pbooksList->size == 0)
	{
		printf("û��ͼ�飬�����ͼ�������\n");
	}
	else if (pbooksList->size == 1)
	{
		printf("����ɹ�\n");
	}
	else
	{
		int input = 0;
		showMenu();
		scanf("%d", &input);
		switch (input)
		{
		case name:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_name);
			printf("����ɹ�\n");
			break;
		case id:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_id);
			printf("����ɹ�\n");
			break;
		case price:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_price);
			printf("����ɹ�\n");
			break;
		case ISBN:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_ISBN);
			printf("����ɹ�\n");
			break;
		case publishers:qsort(pbooksList->data, pbooksList->size, sizeof(pbooksList->data[0]), compare_publishers);
			printf("����ɹ�\n");
			break;
		case nochange:
			printf("����ɹ�\n");
			break;
		default:printf("���޸�����ʽ\n");
		}
	}
}

void showAllBooks(const struct booksList* pbooksList)
{
	system("cls");
	if (pbooksList->size == 0)
	{
		printf("\nû��ͼ�飬�����ͼ�������\n\n");
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