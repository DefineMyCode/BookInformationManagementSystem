
#include "booksys.h"
void menu()
{
	system("title BookInformationManagementSystem");
	printf("*************************************\n");
	printf("***1.添加图书       2.删除图书    ***\n");
	printf("***3.查找图书       4.修改图书    ***\n");
	printf("***5.将图书排序     6.显示所有图书***\n");
	printf("***0.退出                         ***\n");
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
		default:printf("暂未开放该功能\n");
		}
	} while (input);
	return 0;
}