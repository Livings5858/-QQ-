#ifndef LINKLISTJH_H
#define LINKLISTJH_H
#include"LinkList.h"

void ClrearStruct(unsigned char *pta,int size);


struct net_net
{
	int  ID;				//ID
	char num_z[10];			//Ҫ���͵�Ŀ��
	char text[512];			//���͵���Ϣ
	char num_z1[10];		//�������˺�
};

struct Node_Message	
{
	int	 ID;
	char num_z1[10];
	char text[512];
	Node_Message*next;
};
struct Node_Num		//˫������
{
	//Node_Message*head;
	char num_z[10];
	char name[16];
	//char num_z1[10];
	Node_Message *NodeMessage;	//�ı�����
	Node_Num * next;			
};



Node_Num*Search(char num_z[10]);								//Ҫ���͵��˺�
int add_message(char num_z1[10], char num_z[10], char text[512], int ID, char name[16] = { 0 });	//������,Ҫ����,��Ϣ,ID
bool Delete(char number_z[10]);									//Ҫ���͵��˺�
int Length(Node_Num*Node);										//Node_Num *Node


struct num_friend
{
	char num_frd[10];
	num_friend *next;
};
struct num_msg
{
	HBITMAP hbmap1;
	char name[16];
	char num_z[10];
	int age;
	int sex;
	char tel[12];
	num_msg* next;
	num_friend *frd_head;
};
num_msg* search_msg(char num_z[10]);
int add_msg_num_z(char num_z[10]);
int add_msg_num_all(char num_z[10],char name[16],char tel[12],int age,int sex);
int add_msg_frd_z(char num_z[10],char num_frd[10]);
bool delete_msg(char num_z[10]);
void init_msg(num_msg*p);
//�����ļ�
int Unum_msgToFile();
//������Ϣ
int FileToUnum_msg();
//�����ļ��м����ļ�usermsg.txt,userMessage.txt

void InitDirAndFiles();



#endif