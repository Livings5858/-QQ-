#ifndef LINKLISTJH_H
#define LINKLISTJH_H
/*****************************************************************************************/
#include<time.h>

//struct net_net
//{
//	char num_z[10];			//Ҫ���͵�Ŀ��
//	char text[512];			//���͵���Ϣ
//	char num_z1[10];		//�������˺�
//};
//
//struct Node_Message	
//{
//	char text[512];
//	Node_Message*next;
//};
//struct Node_Num		//˫������
//{
//	//Node_Message*head;
//	char num_z[10];
//	char num_z1[10];
//	Node_Message *NodeMessage;	//�ı�����
//	Node_Num * next;			
//};
//
//Node_Num*Search(char num_z[10]);
//int add_message(char num_z[10],char num_z1[10],char text[512]);
//bool Delete(char number_z[10]);
//int Length(Node_Num*Node);

//��սṹ��
void ClearStruct(unsigned char *pta,int size);

/************************************************************************************************/


//�����б�
struct pMsg
{
	//HBITMAP hbmp1;			//ͷ��
	int  sex;
	int  age;
	char tel[12];
	int	 Ynat;				//�Ƿ�����
	char Name[16];			//�ǳ�
	char Remark[16];		//��ע
	char Num_z[10];			//�˺�
	pMsg*next;
};

//��Ӻ���
int add_pMsg(char num_z[10], char Name[16], int sex, int age, char tel[12], char Remark[16]);
int add_pMsg(char num_z[10], char Name[16]);
int add_pMsg(char num_z[10], char Name[16], int sex, int age, char tel[12]);
//int add_pMsg(char num_z[10], char Name[16] = { 0 }, int sex = 0, int age = 0,
//	char tel[12] = { 0 }, char Remark[16] = { 0 });
//int add_pMsg(char num_z[10], char Name[16], int sex, int age,char tel[12], char Remark[16]);
//int add_pMsg(char num_z[10],char Name[16]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",int sex=0,int age=0,
//			 char tel[12]="\0\0\0\0\0\0\0\0\0\0\0\0",char Remark[16]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
//ɾ�����ѣ��ɹ�����true��ʧ�ܷ���false��
bool delete_pMsg(char num_z[10]);
//���Һ��ѣ�����pMsgָ�룩
pMsg *search_pMsg(char num_z[10]);
//���ı�ע(�ɹ�����1��ʧ�ܷ���0)
int change_pMsg_Remark(char num_z[10],char name[16]);

/**********************************************************************************************/
////��Ϣ�б�
//struct msg_list
//{
//	tm* t;					//ʱ��
//	int	 to_or_from;		//1.�������ͣ�2.���͵�����
//	char text[512];			//�ı���Ϣ
//	msg_list*next;
//};
//
////��Ϣ����
//struct trans_msg
//{
//	char num_z[10];			//�˺�
//	msg_list* msg_head;		//��Ϣ�б�ͷָ��
//	trans_msg*next;
//};
//
////�����Ϣ
//int add_msg(char num_z[10],tm*time,int to_or_from,char text[512]);
////�����Ϣ
//bool delete_msg(char num_z[10]);
////������Ϣ����ͷָ��
//msg_list *search_msg(char num_z[10]);

/**************************************************************************/
//������Ϣ
struct personalmsg
{
			int ID;
			char num_z[10];
			char name[16];
			char tel[12];
			int  sex;
			int  age;
};
/******************************************************************************/
struct search_for
{
	int line;//δ����Ϣ
	int index;
	char num_z[10];
	search_for*next;
};
void add_search_for(int index,char num_z_search[10],int line=0);
char*Search_for(int index);
search_for*Search_for(char num_z_search[10]);
bool Delete_search(int index);
bool Delete_search(char num_z_search[10]);


////��֤��Ϣ
//struct check_msg
//{
//	char num_z[10];
//	char text[512];
//	check_msg *next;
//};
//int add_check_msg(char num_z[10],char text[512]);
//void delete_check_msg(char num_z[10]);


//��֤����
struct check_num
{
	char num_z[10];
	check_num*next;
};
int add_check_num(char num_z[10]);
int delete_check_num(char num_z[10]);
check_num*search_check_num(char num_z[10]);


//������Ϣ
struct out_msg
{
	char buff[530];
	out_msg *next;
};
int Empty();
int add_out_msg(char buff[530]);
char* out_out_msg();
#endif