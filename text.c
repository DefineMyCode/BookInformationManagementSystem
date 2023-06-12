
#include "booksys.h"
void menu()
{
	system("title BookInformationManagementSystem");
	printf("*************************************\n");
	printf("***1.���ͼ��       2.ɾ��ͼ��    ***\n");
	printf("***3.����ͼ��       4.�޸�ͼ��    ***\n");
	printf("***5.��ͼ������     6.��ʾ����ͼ��***\n");
	printf("***0.�˳�                         ***\n");
	printf("*************************************\n");
}
int main()
{
	struct booksList booksList;
	booksysInit(&booksList);
	int input = 0;
	do
	{
		menu();
		scanf("%d", &input);
		switch (input)
		{
		case EXIT:saveData(&booksList);freeData(&booksList); break;
		case ADD:addBook(&booksList);
			break;
		case DEL:delBook(&booksList);
			break;
		case QUERY:findBook(&booksList);
			break;
		case MODIFY:modifyBook(&booksList);
			break;
		case SORT:sortData(&booksList);
			break;
		case SHOW:showAllBooks(&booksList);
			break;
		default:printf("��δ���Ÿù���\n");
		}
	} while (input);
	return 0;
}