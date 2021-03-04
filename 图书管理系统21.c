#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct book{
	int no;
	int num;
	char name[100];
	char writer[100];
	struct book *next;
};//��������

struct book *head,*tail;//�����ͷβ

void input();//ע������
void search();//��ѯͼ��
void search_name();
void search_no();
void all();
void change();//�޸�ͼ��
void change1();
void del();//ע������
void load();
void borrow();//����ͼ��
void borrow1();
void repay();//�黹ͼ��
void repay1();

void main()	
{
	int a;

	load();

	while(1) 
	{
	    printf("       = = = = ͼ�����ϵͳ = = = =       \n");
	    printf("__________________________________________\n");
	    printf("             �������ѡ����             \n");
	    printf("1.ע������                      2.ע������\n");
        printf("3.��ѯͼ��                      4.�޸�ͼ��\n");
	    printf("5.����ͼ��                      6.�黹ͼ��\n");
		printf("0.�˳�\n");
	    printf("__________________________________________\n");
		scanf("%d",&a);
		if(a>=0&&a<=6)
		  {
			  switch(a)
			  {
			  case 1: input(); break;   //ע������
			  case 2: del();break;   //ע������ 
			  case 3: search(); break;   //��ѯͼ��
			  case 4: change(); break;   //�޸�ͼ��
			  case 5: borrow(); break;   //����ͼ��
			  case 6: repay(); break;   //�黹ͼ��
			  case 0: exit(0);                                                   
			 }
		}
		else
		{
			printf("�������");
			break;
		}
	}
}

void load()
{
	FILE *fp,*fp1;//���������ļ�����
	struct book *q;//����һ���ṹ�����
	char ch;
	
	
	if((fp=fopen("book2.txt","r"))==NULL)
	{
		printf("�ļ���ʧ��!\n");
		return;
	}
	
	ch=fgetc(fp);
	
	if(ch==EOF)
		printf("ϵͳ�ڻ�û���鼮�ɶ�ȡ,������µ��鼮...\n");
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
			printf("�޷��ر��ļ���\n");
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
	FILE*fp;//����һ���ļ�����
	struct book *q,*ptr;//���������ṹ�����
	int a;

	system("cls");
	if((fp=fopen("book2.txt","w"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
		q=(struct book *)malloc(sizeof(struct book));//��̬����
		printf("��������ı�ţ�\n");
		scanf("%d",&q->no);
		printf("������������\n");
		scanf("%s",q->name);
		printf("��������������\n");
		scanf("%s",q->writer);
		printf("�������鱾����\n");
		scanf("%d",&q->num);

		q->next=NULL;

		if(head==NULL)
			head=q;
		else
			tail->next=q;
		tail=q;

		for(ptr=head;ptr!=NULL;ptr=ptr->next)
		{
			fprintf(fp,"%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);//�������б���Ϣ�����ļ�
		}

		printf("����ɹ�����������1����������0��\n");
		scanf("%d",&a);
		if(a==1)
			input();
		else if(a==0)
		{}
		else
			printf("��������\n");

		if(fclose(fp))
		{
			printf("�޷��ر��ļ���\n");
			exit(0);
		}
		system("cls");
}

void search()
{
	int a;

	system("cls");
	printf("1 ͨ��������ѯ  \n2  ͨ����Ų�ѯ\n3  ��ʾȫ��\n");
	printf("���������ѡ���ѯ��ʽ:");
	scanf("%d",&a);
	if(a==1)                      /*����������ѯ*/
		search_name();
    else if(a==2)
		search_no();
	else if(a==3)
		all();
	else
	{
		printf("��������\n");
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
		printf("û�м�¼\n");
		return;
	}

	printf("������Ҫ���ҵ�����:\n");
	scanf("%s",sname);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(strcmp(ptr->name,sname)==0)
		{
			printf("��Ϣ���£�\n");
			printf("%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);
			flag=0;
		}
	}
	if(flag)
		printf("�Բ����Ҳ����������ҵ��鼮...\n");

}

void search_no()
{
	struct book *ptr;
	int flag=1;
	int sno;

	if(head==NULL)
	{
		printf("û�м�¼\n");
		return;
	}

	printf("������Ҫ���ҵ���ı��:\n");
	scanf("%d",&sno);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(ptr->no==sno)
		{
			printf("��Ϣ���£�\n");
			printf("%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);
			flag=0;
		}
	}
	if(flag)
		printf("�Բ����Ҳ����������ҵ��鼮...\n");

}

void all()
{
	FILE *fp;
	int sno,snum;
	char sname[100],swriter[100];
	
	if(head==NULL)
	{
		printf("��Ǹ����û���鱾.��������\n");
		return;
	}
	
	if((fp=fopen("book2.txt","r"))==NULL){
		printf("�ļ��޷���!\n");
		exit(0);
	}
	
	while(!feof(fp))
	{
		fscanf(fp,"%d %s %s %d\n",&sno,sname,swriter,&snum);
		printf("%d %s %s %d\n",sno,sname,swriter,snum);
	}
	
	if(fclose(fp))
	{
		printf("�޷��ر��ļ�1\n");
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
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}

	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		fprintf(fp,"%d %s %s %d\n",ptr->no,ptr->name,ptr->writer,ptr->num);
	}
	if(fclose(fp))
	{
		printf("�޷��ر��ļ��У�\n");
		exit(0);
	}
}
void change1()
 {
	 struct book *ptr;
	 int flag=1,sno,snum;
	 char sname[100],swriter[100];

	 printf("������Ҫ���ĵ��鼮�ı��:\n");
	 scanf("%d",&sno);

	 for(ptr=head;ptr!=NULL;ptr=ptr->next)
	 {
		 if(ptr->no==sno)
		 {
			 printf("����������Ϣ��\n");
			 printf("������������\n");
			 scanf("%s",sname);
			 printf("��������������\n");
			 scanf("%s",swriter);
			 printf("�������鱾������\n");
			 scanf("%d",&snum);
			 strcpy(ptr->writer,swriter);
			 ptr->num=snum;
			 flag=0;
			 printf("�޸��鱾�ɹ���\n");
		 }
	 }
	 if(flag)
		 printf("Ѱ�Ҳ������Ϊ%d���鱾...\n",sno);
 }

void del()
{
	struct book *ptr,*subptr;
	int flag=1,sno;

	printf("��������ɾ���鼮�ı�ţ�\n");
	scanf("%d",&sno);
	
	if(head->no==sno)
	{
		subptr=head;
		head=head->next;
		free(subptr);
		flag=(0);
		printf("ɾ���ɹ���\n");
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
		printf("û�����������ı��Ϊ%d���鼮!\n",sno);
}
void borrow()
{
	struct book *ptr;
	int flag=1;
	int sno,zno,dno,n;

	if(head==NULL)
	{
		printf("û�м�¼\n");
		return;
	}

	printf("������Ҫ���ĵ���ı�� ��Ľ���֤��� ��������:\n");
	scanf("%d %d %d",&sno,&zno,&dno);
	borrow1(sno,zno,dno);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(ptr->no==sno)
		{
			printf("�˶Ը��鼮��Ϣ:\n");
			printf("%d %s %s\n",ptr->no,ptr->name,ptr->writer);
			flag=0;
			printf("�Ƿ���ȷ��\n");
			printf("1��ȷ  2����\n");
			scanf("%d",&n);
			if(n=1)
				ptr->num=ptr->num-1;
		}
	}
	if(flag)
		printf("�Բ����Ҳ����������ҵ��鼮...\n");
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
	if((fp=fopen("�鼮������Ϣ.txt","w"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	
		fprintf(fp,"%d %d %d\n",a,b,c);

		printf("����ɹ�����������1����������0��\n");
		scanf("%d",&d);
		if(d==1)
			input();
		else if(d==0)
		{}
		else
			printf("��������\n");

		if(fclose(fp))
		{
			printf("�޷��ر��ļ���\n");
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
		printf("û�м�¼\n");
		return;
	}

	printf("������Ҫ�黹����ı�� ��Ľ���֤���:\n");
	scanf("%d %d",&sno,&zno);
	repay1(sno,zno);
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		if(ptr->no==sno)
		{
			printf("�˶Ը��鼮��Ϣ:\n");
			printf("%d %s %s\n",ptr->no,ptr->name,ptr->writer);
			flag=0;
			printf("�Ƿ���ȷ��\n");
			printf("1��ȷ  2����\n");
			scanf("%d",&n);
			if(n=1)
				ptr->num=ptr->num+1;
		}
	}
	if(flag)
		printf("�Բ����Ҳ����������ҵ��鼮...\n");

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
	if((fp=fopen("�鼮�黹��Ϣ.txt","w"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	
		fprintf(fp,"%d %d �ѹ黹\n",a,b);

		printf("����ɹ�����������1����������0��\n");
		scanf("%d",&d);
		if(d==1)
			input();
		else if(d==0)
		{}
		else
			printf("��������\n");

		if(fclose(fp))
		{
			printf("�޷��ر��ļ���\n");
			exit(0);
		}
		system("cls");

}