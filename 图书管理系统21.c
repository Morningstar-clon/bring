#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct book{
	int no;
	int num;
	char name[100];
	char writer[100];
	struct book *next;
};//单向链表

struct book *head,*tail;//链表的头尾

void input();//注册新书
void search();//查询图书
void search_name();
void search_no();
void all();
void change();//修改图书
void change1();
void del();//注销旧书
void load();
void borrow();//借阅图书
void borrow1();
void repay();//归还图书
void repay1();

void main()	
{
	int a;

	load();

	while(1) 
	{
	    printf("       = = = = 图书管理系统 = = = =       \n");
	    printf("__________________________________________\n");
	    printf("             根据序号选择功能             \n");
	    printf("1.注册新书                      2.注销旧书\n");
        printf("3.查询图书                      4.修改图书\n");
	    printf("5.借阅图书                      6.归还图书\n");
		printf("0.退出\n");
	    printf("__________________________________________\n");
		scanf("%d",&a);
		if(a>=0&&a<=6)
		  {
			  switch(a)
			  {
			  case 1: input(); break;   //注册新书
			  case 2: del();break;   //注销旧书 
			  case 3: search(); break;   //查询图书
			  case 4: change(); break;   //修改图书
			  case 5: borrow(); break;   //借阅图书
			  case 6: repay(); break;   //归还图书
			  case 0: exit(0);                                                   
			 }
		}
		else
		{
			printf("输入错误！");
			break;
		}
	}
}

void load()
{
	FILE *fp,*fp1;//定义两个文件变量
	struct book *q;//定义一个结构体变量
	char ch;
	
	
	if((fp=fopen("book2.txt","r"))==NULL)
	{
		printf("文件打开失败!\n");
		return;
	}
	
	ch=fgetc(fp);
	
	if(ch==EOF)
		printf("系统内还没有书籍可读取,请添加新的书籍...\n");
	else
	{
		fp1=fopen("book2.txt","r");
		while(!feof(fp1))
		{
			q=(struct book *)malloc(sizeof(struct book));
			fscanf(fp1,"%d %s %s %d\n",&q->no,q->name,q->writer,&q->num);
			q->next=NULL;
			if(head==NULL)
				head=q;
			else
				tail->next=q;
			tail=q;
		}
			
		if(fclose(fp1))
		{
			printf("无法关闭文件！\n");
			exit(0);
		}
	}	
	
	if(fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}
}

void input()
{
	FILE*fp;//定义一个文件变量
	struct book *q,*ptr;//定义两个结构体变量
	int a;

	system("cls");
	if((fp=fopen("book2.txt","w"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
		q=(struct book *)malloc(sizeof(struct book));//动态储存
		printf("请输入书的编号：\n");
		scanf("%d",&q->no);
		printf("请输入书名：\n");
		scanf("%s",q->name);
		printf("请输入作者名：\n");
		scanf("%s",q->writer);
		printf("请输入书本数：\n");
		scanf("%d",&q->num);

		q->next=NULL;

		if(head==NULL)
			head=q;
		else
			tail->next=q;
		tail=q;

		for(ptr=head;ptr!=NULL;ptr=ptr->next)
		{
			fprintf(fp,"%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);//将单项列表信息存入文件
		}

		printf("保存成功！继续请输1，返回输入0：\n");
		scanf("%d",&a);
		if(a==1)
			input();
		else if(a==0)
		{}
		else
			printf("输入有误！\n");

		if(fclose(fp))
		{
			printf("无法关闭文件！\n");
			exit(0);
		}
		system("cls");
}

void search()
{
	int a;

	system("cls");
	printf("1 通过书名查询  \n2  通过编号查询\n3  显示全部\n");
	printf("请输入序号选择查询方式:");
	scanf("%d",&a);
	if(a==1)                      /*按照书名查询*/
		search_name();
    else if(a==2)
		search_no();
	else if(a==3)
		all();
	else
	{
		printf("输入有误！\n");
		main();
	}
}

void search_name()
{
	struct book *ptr;
	int flag=1;
	char sname[100];

	if(head==NULL)
	{
		printf("没有记录\n");
		return;
	}

	printf("输入需要查找的书名:\n");
	scanf("%s",sname);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(strcmp(ptr->name,sname)==0)
		{
			printf("信息如下：\n");
			printf("%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);
			flag=0;
		}
	}
	if(flag)
		printf("对不起，找不到你所查找的书籍...\n");

}

void search_no()
{
	struct book *ptr;
	int flag=1;
	int sno;

	if(head==NULL)
	{
		printf("没有记录\n");
		return;
	}

	printf("输入需要查找的书的编号:\n");
	scanf("%d",&sno);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(ptr->no==sno)
		{
			printf("信息如下：\n");
			printf("%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);
			flag=0;
		}
	}
	if(flag)
		printf("对不起，找不到你所查找的书籍...\n");

}

void all()
{
	FILE *fp;
	int sno,snum;
	char sname[100],swriter[100];
	
	if(head==NULL)
	{
		printf("抱歉，还没有书本.。。。。\n");
		return;
	}
	
	if((fp=fopen("book2.txt","r"))==NULL){
		printf("文件无法打开!\n");
		exit(0);
	}
	
	while(!feof(fp))
	{
		fscanf(fp,"%d %s %s %d\n",&sno,sname,swriter,&snum);
		printf("%d %s %s %d\n",sno,sname,swriter,snum);
	}
	
	if(fclose(fp))
	{
		printf("无法关闭文件1\n");
		exit(0);
	}

}

void change()
{
	FILE *fp;
	struct book *ptr;
	
	change1();

	if((fp=fopen("book2.txt","w"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}

	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		fprintf(fp,"%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);
	}
	if(fclose(fp))
	{
		printf("无法关闭文件夹！\n");
		exit(0);
	}
}
void change1()
 {
	 struct book *ptr;
	 int flag=1,sno,snum;
	 char sname[100],swriter[100];

	 printf("输入需要更改的书籍的编号:\n");
	 scanf("%d",&sno);

	 for(ptr=head;ptr!=NULL;ptr=ptr->next)
	 {
		 if(ptr->no==sno)
		 {
			 printf("请输入新信息：\n");
			 printf("请输入书名：\n");
			 scanf("%s",sname);
			 printf("请输入作者名：\n");
			 scanf("%s",swriter);
			 printf("请输入书本数量：\n");
			 scanf("%d",&snum);
			 strcpy(ptr->writer,swriter);
			 ptr->num=snum;
			 flag=0;
			 printf("修改书本成功！\n");
		 }
	 }
	 if(flag)
		 printf("寻找不到编号为%d的书本...\n",sno);
 }

void del()
{
	struct book *ptr,*subptr;
	int flag=1,sno;

	printf("输入所需删除书籍的编号：\n");
	scanf("%d",&sno);
	
	if(head->no==sno)
	{
		subptr=head;
		head=head->next;
		free(subptr);
		flag=(0);
		printf("删除成功！\n");
	}
	else
	{
		for(ptr=head;ptr!=NULL;ptr=ptr->next)
			if(ptr->no==sno)
				for(subptr=head;subptr!=NULL;subptr=subptr->next)
					if(subptr->next==ptr)
					{
						subptr->next=ptr->next;
						free(ptr);
					}
	}
	if(flag)
		printf("没有你所搜索的编号为%d的书籍!\n",sno);
}
void borrow()
{
	struct book *ptr;
	int flag=1;
	int sno,zno,dno,n;

	if(head==NULL)
	{
		printf("没有记录\n");
		return;
	}

	printf("输入需要借阅的书的编号 你的借书证序号 借阅天数:\n");
	scanf("%d %d %d",&sno,&zno,&dno);
	borrow1(sno,zno,dno);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(ptr->no==sno)
		{
			printf("核对该书籍信息:\n");
			printf("%d %s %s\n",ptr->no,ptr->name,ptr->writer);
			flag=0;
			printf("是否正确？\n");
			printf("1正确  2错误\n");
			scanf("%d",&n);
			if(n=1)
				ptr->num=ptr->num-1;
		}
	}
	if(flag)
		printf("对不起，找不到你所查找的书籍...\n");
}
void borrow1(int a,int b,int c)
{
	FILE * fp;
	struct jy
	{
		int a;
		int b;
		int c;
	};
	struct jy;
	int d;

	system("cls");
	if((fp=fopen("书籍借阅信息.txt","w"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	
		fprintf(fp,"%d %d %d\n",a,b,c);

		printf("保存成功！继续请输1，返回输入0：\n");
		scanf("%d",&d);
		if(d==1)
			input();
		else if(d==0)
		{}
		else
			printf("输入有误！\n");

		if(fclose(fp))
		{
			printf("无法关闭文件！\n");
			exit(0);
		}
		system("cls");

}
void repay()
{
	struct book *ptr;
	int flag=1;
	int sno,zno,n;

	if(head==NULL)
	{
		printf("没有记录\n");
		return;
	}

	printf("输入需要归还的书的编号 你的借书证序号:\n");
	scanf("%d %d",&sno,&zno);
	repay1(sno,zno);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(ptr->no==sno)
		{
			printf("核对该书籍信息:\n");
			printf("%d %s %s\n",ptr->no,ptr->name,ptr->writer);
			flag=0;
			printf("是否正确？\n");
			printf("1正确  2错误\n");
			scanf("%d",&n);
			if(n=1)
				ptr->num=ptr->num+1;
		}
	}
	if(flag)
		printf("对不起，找不到你所查找的书籍...\n");

}
void repay1(int a,int b)
{
	FILE * fp;
	struct jy
	{
		int a;
		int b;
	};
	struct jy;
	int d;

	system("cls");
	if((fp=fopen("书籍归还信息.txt","w"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	
		fprintf(fp,"%d %d 已归还\n",a,b);

		printf("保存成功！继续请输1，返回输入0：\n");
		scanf("%d",&d);
		if(d==1)
			input();
		else if(d==0)
		{}
		else
			printf("输入有误！\n");

		if(fclose(fp))
		{
			printf("无法关闭文件！\n");
			exit(0);
		}
		system("cls");

}