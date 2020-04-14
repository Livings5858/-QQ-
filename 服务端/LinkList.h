#ifndef LINKLIST_H
#define LINKLIST_H
#include<stdio.h>
#include"windows.h"
typedef struct node {
	SOCKET sock_c;
    int data;
    struct node *next;
	char number_z[10];
	char number_m[16];
}NODE;
//�ඨ��
class LinkList
{
private:
    NODE *head;
public:
    LinkList() { head = NULL; }
    ~LinkList();
    bool clearSqList();
    bool isEmpty() { return head == NULL; }
    int Length();
    bool Delete(char*);//ɾ��,�ɹ�����true��
	bool add(char*,char*);//������ĩβ���Ԫ��
	int check_ex(char*,char*,char number_m1[]);//�˺ţ�ԭ���룬�����롣,�˺Ų����ڷ���0��ԭ������󷵻�1,���ĳɹ�����2��
	int check(char*,char number_m[16]='\0');//�˶��˺�����  ȫ�Է���2���˺Ŵ���������󷵻�1���˺Ų����ڷ���0��
	int UmsgToFile();
	int FileToUmsg();
    NODE * Reverse();
	void out(HWND hWnd,UINT Msg,WPARAM wParam=0);
	int number_create(char*);//���ɲ��ظ�9λ�˺�
	char*return_nuber_m(char*);//��������
	NODE*Search(char number_z[]);//����ָ��
	int add_sock(NODE *Node,SOCKET sock_c);//���sock		�ɹ�����1��ʧ�ܷ���-1
	NODE* Gethead();//����head
};


#endif