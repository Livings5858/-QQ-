#include<windows.h>
#include<iostream>
#include<time.h>
#include"tchar.h"
#include"net_id.h"
#include"LinkList.h"
#include"Linklist����.h"
#pragma comment(lib,"WS2_32.lib")
using namespace std;

#define num					100
#define IDC_TEXT_SHOW		0xff
#define IDC_TEXT_NUMBER_Z	0x16
#define IDC_BTN_DEL			0x17
#define IDC_BTN_CHECK		0x18
#define IDC_BTN_SHOW_ALL	0x19
#define IDC_BTN_SHOW_ON		0x20
#define IDC_BTN_TO_FILE		0x21
#define IDC_BTN_CLEAR		0x22
HINSTANCE happ;
//struct nMsg
//{
//	int		ID;
//	int		len;
//	char	num_z[10];
//	char	num_m[16];
//	char	num_mm[16];
//	char	*add;
//};
LinkList LI_1;//�����û�
LinkList LI_2;//�����û�
LinkList LI_3;//�����û�
num_msg *num_msg1;//���Һ����õ��ڴ�
time_t tt ;//��䷵�ص�ֻ��һ��ʱ��cuo
tm t;
//����Ϣ
void ForMessage(SOCKET sock_c,char num_z[10],LinkList LI_2);
//����
DWORD WINAPI connect_s(LPVOID lpParameter);
//�ص���������
LRESULT CALLBACK WinProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	
	InitDirAndFiles();//��ʼ���ļ�
	LI_1.FileToUmsg();//�����ļ�
	FileToUnum_msg();//�����ļ�
	
	CreateThread(NULL,0,/*(LPTHREAD_START_ROUTINE)*/connect_s,NULL,0,NULL);

	WNDCLASS wndclass;	//����һ��������
	wndclass.cbClsExtra = 0;	//����������չ
	wndclass.cbWndExtra = 0;	//����ʵ������չ
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���ڰ�ɫ
	wndclass.hCursor = LoadCursor(NULL,/*IDC_HAND*/IDC_ARROW);	//����	//��ͷ
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);	//Ĭ����С��ͼ��
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WinProc;	//���崰�ڴ�����
	wndclass.lpszClassName =_T("win_s");	//��������
	wndclass.lpszMenuName = NULL;	//�����޲˵�
	wndclass.style = CS_HREDRAW|CS_PARENTDC;	//���ô�������
	//ע�ᴰ����
	RegisterClass(&wndclass);
	HWND hWnd;
	hWnd = CreateWindow(_T("win_s"),_T("win_s����"),WS_OVERLAPPEDWINDOW,250,10,800,750,NULL,NULL,hInstance,NULL);//��������
	
	ShowWindow(hWnd,SW_SHOWNORMAL);//��ʾ����
	UpdateWindow(hWnd);	//���´���
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);	//������Ϣ����Ϣ����
		DispatchMessage(&msg);	//������Ϣ�����ڳ���
	}
	return 0;
}

static HWND hWrite, hShow, hBtn;

LRESULT CALLBACK WinProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	/*int x;
	int y;
	 x=LOWORD(lParam);
	 y=HIWORD(lParam);*/
	char number_z[10];
	//static HWND hWrite, hShow, hBtn;
	switch(uMsg)
	{
	case WM_CREATE:
		CreateWindow(_T("Button"), _T("ɾ��"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									450, 100 , 80, 40, hWnd, HMENU(IDC_BTN_DEL), happ, NULL);

		CreateWindow(_T("Button"), _T("�鿴����"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									550, 100, 80, 40, hWnd, HMENU(IDC_BTN_CHECK), happ, NULL);

		CreateWindow(_T("Button"), _T("��ʾ�����û�"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									450, 150, 150, 40, hWnd, HMENU(IDC_BTN_SHOW_ALL), happ, NULL);
		CreateWindow(_T("Button"), _T("��ʾ�����û�"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									450, 200, 150, 40, hWnd, HMENU(IDC_BTN_SHOW_ON), happ, NULL);
		CreateWindow(_T("Button"), _T("����Ϣ�����ļ�"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									450, 250, 150, 40, hWnd, HMENU(IDC_BTN_TO_FILE), happ, NULL);
		CreateWindow(_T("Button"), _T("���LISTBOX"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									450, 300, 150, 40, hWnd, HMENU(IDC_BTN_CLEAR), happ, NULL);

		CreateWindow(_T("LISTBOX"), _T(""), 

									WS_CHILD|WS_VISIBLE|ES_LEFT|WS_BORDER| ES_READONLY|WS_VSCROLL,

									20, 20, 400, 680, hWnd, HMENU(IDC_TEXT_SHOW), happ, NULL);

		CreateWindow(_T("edit"), NULL, WS_VISIBLE|WS_CHILD | WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE, 

									444,20, 241, 50, hWnd, HMENU(IDC_TEXT_NUMBER_Z), happ, NULL);


		hWrite = GetDlgItem(hWnd, IDC_TEXT_NUMBER_Z);

		hShow = GetDlgItem(hWnd, IDC_TEXT_SHOW);
		break;
	case WM_COMMAND:
		if(LOWORD(wParam)==IDC_BTN_DEL)
		{
			if(GetWindowTextLength(hWrite)==9)
			{
			memset(number_z,'\0',10);

			SendMessage(hWrite, WM_GETTEXT,  10/*(WPARAM)(strlen(number_z) + 1)*/,(LPARAM)number_z);

				if (0 == GetWindowTextLength(hWrite))

				{

					SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)_T("δ�����˺�"));

				}
				else
				{
					if(LI_1.Length())
					if(LI_1.Delete(number_z))
						SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)_T("��ɾ��"));
				}
			}
		}
		if(LOWORD(wParam)==IDC_BTN_CHECK)
		{
			if(GetWindowTextLength(hWrite)==9)
			{

			memset(number_z,'\0',10);
			SendMessage(hWrite, WM_GETTEXT, 10/*(WPARAM)(strlen(number_z) + 1)*/,(LPARAM)number_z);				
			
			if (0 == GetWindowTextLength(hWrite))

				{
					
					SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)_T("δ�����˺�"));

				}
				else
				{
					char number_m[16];
					memset(number_m,'\0',16);
					strcpy_s(number_m,LI_1.return_nuber_m(number_z));
					if(number_m==NULL)
						SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)_T("�˺Ų�����"));
					else
					{
						SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)number_z);
						SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)number_m);
					}
				}
			}
		}
		if(LOWORD(wParam)==IDC_BTN_CLEAR)
		{
			int count=SendMessage(hShow,LB_GETCOUNT,0,0);
			for(int i=0;i<count;i++)
			SendMessage(hShow,LB_DELETESTRING,0,0);
		}

		if(LOWORD(wParam)==IDC_BTN_SHOW_ALL)
		{
			LI_1.out(hShow,LB_ADDSTRING);
		}
		if(LOWORD(wParam)==IDC_BTN_SHOW_ON)
		{
			LI_2.out(hShow,LB_ADDSTRING);
		}
		if(LOWORD(wParam)==IDC_BTN_TO_FILE)
		{
			Unum_msgToFile();
			LI_1.UmsgToFile();
			SendMessage(hShow,LB_ADDSTRING,0,(LPARAM)_T("����ɹ�"));
		}
		break;
	case WM_CLOSE:
		/*Unum_msgToFile();
		LI_1.UmsgToFile();*/
		DestroyWindow(hWnd);
	case WM_DESTROY:
		Unum_msgToFile();
		LI_1.UmsgToFile();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;
}
/************************************************************************************/
//
//packet pack_1,pack_2;

/***************************************************************************************/
DWORD WINAPI com(LPVOID lpParameter)
	{
		//char buff[256];
		/*nMsg msg_1;
		nMsg msg_2;*/

		packet pack_1,pack_2;//���գ�����
		char num_z1[10];
		char num_m1[16]="123456";
		char num_z[10];
		char num_m[16];
		num_friend *pfriend;
		SOCKET sock_c=*(SOCKET*)lpParameter;
		NODE*p_search;			//search���ص�ָ��
		Node_Num*p_num;		//��������ָ��
		Node_Message *p_message;//��Ϣ����ָ��
		num_msg *p_search_num_msg,*p_search_num_msg_1;//������Ϣ����ͷ
		memset(num_z,'\0',10);
		memset(num_m,'\0',16);
		while(1)
		{
		ClrearStruct((unsigned char*)&pack_1,sizeof(packet));
		int r=recv(sock_c,(char*)&pack_1,sizeof(packet),0);
		if(r<=0&&r!=EINTR)
		{
			if((num_z[0]!='\0')&&(num_m[0]!='\0'))
		{
			if(LI_2.check(num_z,num_m)==2)
			LI_2.Delete(num_z);
			if(LI_3.check(num_z,num_m)==2)
			LI_3.Delete(num_z);
		}
		closesocket(sock_c);
			return 0;
		}
		if(r>0)
		{
			switch(pack_1.commend)
			{
			case 1:
				switch(pack_1.upacket.info1.ID)
				{
				case LOG_IN:
					if(LI_1.check(pack_1.upacket.info1.num_z,pack_1.upacket.info1.num_m)==2)
					{
						ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
						pack_2.commend=1;
						pack_2.upacket.info1.ID=LOG_SUCCEED;				//��½�ɹ�
						send(sock_c,(char*)&pack_2,sizeof(packet),0);

						//���͸�����Ϣ
						ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
						pack_2.commend=3;
						pack_2.upacket.info3.ID=LOCALMSG;				
						p_search_num_msg=search_msg(pack_1.upacket.info1.num_z);
						if(p_search_num_msg!=NULL)
						{
							strcpy_s(pack_2.upacket.info3.name,p_search_num_msg->name);
							strcpy_s(pack_2.upacket.info3.tel,p_search_num_msg->tel);
							strcpy_s(pack_2.upacket.info3.num_z,p_search_num_msg->num_z);
							pack_2.upacket.info3.age=p_search_num_msg->age;
							pack_2.upacket.info3.sex=p_search_num_msg->sex;
						}
						send(sock_c,(char*)&pack_2,sizeof(packet),0);
						if(p_search_num_msg!=NULL)
						{
						pfriend=p_search_num_msg->frd_head;
						while(1)
						{
							
							if(pfriend==NULL)break;
							ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
							pack_2.commend=3;
							pack_2.upacket.info3.ID=FRDMSG;				
							p_search_num_msg_1=search_msg(pfriend->num_frd);
							if(p_search_num_msg_1!=NULL)
							{
							strcpy_s(pack_2.upacket.info3.name,p_search_num_msg_1->name);
							strcpy_s(pack_2.upacket.info3.tel,p_search_num_msg_1->tel);
							strcpy_s(pack_2.upacket.info3.num_z,p_search_num_msg_1->num_z);
							pack_2.upacket.info3.age=p_search_num_msg_1->age;
							pack_2.upacket.info3.sex=p_search_num_msg_1->sex;
							}
							//MessageBox(NULL,pfriend->num_frd,"666",MB_OK);
							send(sock_c,(char*)&pack_2,sizeof(packet),0);
								pfriend=pfriend->next;
								//MessageBox(NULL,pfriend->num_frd,"666",MB_OK);
						}
						}

						if(LI_2.check(pack_1.upacket.info1.num_z,pack_1.upacket.info1.num_m)!=2)
						{
							LI_2.add(pack_1.upacket.info1.num_z,pack_1.upacket.info1.num_m);	//��ӵ�����
							LI_2.add_sock(LI_2.Search(pack_1.upacket.info1.num_z),sock_c);		//���sock
							strcpy_s(num_z,pack_1.upacket.info1.num_z);
								strcpy_s(num_m,pack_1.upacket.info1.num_m);
							p_num=Search(pack_1.upacket.info1.num_z);
							//MessageBox(NULL,p_num->num_z,"666",MB_OK);
							if(p_num!=NULL)//���͵��ͻ�
							{
								p_message=p_num->NodeMessage;
								while(1)
								{
									if(p_message==NULL)break;
									ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
									pack_2.commend=2;
									pack_2.upacket.info2.ID=p_message->ID;
									if((p_num->name[0])!='\0')
									strcpy_s(pack_2.upacket.info2.name,p_num->name);
									if(p_message->ID==CM_AGREE||p_message->ID==CM_REFUSE)
									{
										strcpy_s(pack_2.upacket.info2.num_z1,pack_1.upacket.info1.num_z);
										strcpy_s(pack_2.upacket.info2.num_z,p_message->num_z1);
									}
									else
									{
										strcpy_s(pack_2.upacket.info2.num_z,pack_1.upacket.info1.num_z);
										strcpy_s(pack_2.upacket.info2.num_z1,p_message->num_z1);
									}
									strcpy_s(pack_2.upacket.info2.text,p_message->text);
									send(sock_c,(char*)&pack_2,sizeof(packet),0);
									p_message=p_message->next;
								}
								Delete(pack_1.upacket.info1.num_z);
							}
						}
					}
					else
					{
						ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
						pack_2.commend=1;
						pack_2.upacket.info1.ID=LOG_FAIL;
						send(sock_c,(char*)&pack_2,sizeof(packet),0);
						//LI_2.add(msg_1.num_z,msg_1.num_m);
					}
					break;
				case REGISTER:
					LI_1.number_create(num_z1);
					LI_1.add(num_z1,num_m1);
					add_msg_num_z(num_z1);//��ӵ�������Ϣ����
					ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
					pack_2.commend=1;
					pack_2.upacket.info1.ID=REGISTER_RETURN;
					strcpy_s(pack_2.upacket.info1.num_z,num_z1);
					strcpy_s(pack_2.upacket.info1.num_m,num_m1);
					send(sock_c,(char*)&pack_2,sizeof(packet),0);
					break;
				case CONNECT_BREAK:
					if(LI_2.check(num_z,num_m)==2)
					LI_2.Delete(num_z);
						//MessageBox(NULL,"666","666",MB_OK);
					if(LI_3.check(num_z,num_m)==2)
					LI_3.Delete(num_z);
					//��֪���ò�������
					closesocket(sock_c);
					return 0;
					break;
				//case TRANS_MESSAGE:
				//	ClrearStruct((unsigned char*)&msg_2,sizeof(nMsg));
				//	msg_2.ID=TRANS_MESSAGE;
				//	send(sock_c,(char*)&msg_2,sizeof(nMsg),0);
				//	net_net net_2;
				//	LI_3.add(num_z,num_m);
				//	p=Search(num_z);		//��������ָ��
				//	p1=p->NodeMessage;//��Ϣ����ָ��
				//	if(p!=NULL)
				//	{
				//		int len = Length(p);
				//		send(sock_c,(char*)&len,sizeof(int),0);
				//		for(;p1!=NULL;)
				//		{
				//			ClrearStruct((unsigned char*)&net_2,sizeof(net_net));
				//			strcpy_s(net_2.num_z1,p->num_z1);
				//			strcpy_s(net_2.text,p1->text);
				//			send(sock_c,(char*)&net_2,sizeof(net_net),0);
				//			p1=p1->next;
				//		}
				//	}
				//	ForMessage(sock_c,num_z,LI_3);
				//	break;
				case COMMEND:
					break;
				case CHANGENUMM:
					if(LI_1.check_ex(pack_1.upacket.info1.num_z,pack_1.upacket.info1.num_m,pack_1.upacket.info1.num_mm)==2)
					{
					ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
					pack_2.commend=1;
					pack_2.upacket.info1.ID=CHANGESUCCEED;
					send(sock_c,(char*)&pack_2,sizeof(packet),0);
					}
					else
					{
					ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
					pack_2.commend=1;
					pack_2.upacket.info1.ID=CHANGEFAIL;
					send(sock_c,(char*)&pack_2,sizeof(packet),0);;
					}
				break;
				case SEARCHFRIEND:
					num_msg1=search_msg(pack_1.upacket.info1.num_z);
					if(num_msg1!=NULL)
					{
						ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
						pack_2.commend=1;
						pack_2.upacket.info1.ID=FRIENDEXIT;
						strcpy_s(pack_2.upacket.info1.num_z,num_msg1->num_z);
						strcpy_s(pack_2.upacket.info1.num_mm,num_msg1->name);
						send(sock_c,(char*)&pack_2,sizeof(packet),0);
					}
					else
					{
						ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
						pack_2.commend=1;
						pack_2.upacket.info1.ID=FRIENDNULL;
						send(sock_c,(char*)&pack_2,sizeof(packet),0);
					}
					break;
			
					}
				break;
			case 2:
				switch(pack_1.upacket.info2.ID)
				{
				case CM_AGREE:
					
					add_msg_frd_z(pack_1.upacket.info2.num_z,pack_1.upacket.info2.num_z1);
					add_msg_frd_z(pack_1.upacket.info2.num_z1,pack_1.upacket.info2.num_z);

					/*ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
					pack_2.commend=2;
					pack_2.upacket.info2.ID=CM_AGREE;
					strcpy_s(pack_2.upacket.info2.num_z,pack_1.upacket.info2.num_z);*/
					p_search_num_msg=search_msg(pack_1.upacket.info2.num_z);
					if(p_search_num_msg->name[0]!='\0')
					strcpy_s(pack_1.upacket.info2.name,p_search_num_msg->name);
					p_search=LI_2.Search(pack_1.upacket.info2.num_z1);
					if(p_search==NULL)	
					{
						add_message(pack_1.upacket.info2.num_z,pack_1.upacket.info2.num_z1
							,pack_1.upacket.info2.text,pack_1.upacket.info2.ID,search_msg(pack_1.upacket.info2.num_z)->name);
						
					}
					else
					{
						strcpy_s(pack_1.upacket.info2.name,search_msg(pack_1.upacket.info2.num_z)->name);
						send(p_search->sock_c,(char*)&pack_1,sizeof(packet),0);
					}
					break;



					break;
				case CM_REFUSE:
					/*ClrearStruct((unsigned char*)&pack_2,sizeof(packet));
					pack_2.commend=1;
					pack_2.upacket.info1.ID=CM_REFUSE;
					strcpy_s(pack_2.upacket.info1.num_z,pack_1.upacket.info2.num_z);
					p_search_num_msg=search_msg(pack_1.upacket.info2.num_z);
					if(p_search_num_msg->name[0]!='\0')
					strcpy_s(pack_2.upacket.info1.num_mm,p_search_num_msg->name);
					p_search=LI_2.Search(pack_1.upacket.info2.num_z1);*/
					p_search=LI_2.Search(pack_1.upacket.info2.num_z1);
					if(p_search==NULL)	
						add_message(pack_1.upacket.info2.num_z,pack_1.upacket.info2.num_z1
							,pack_1.upacket.info2.text,pack_1.upacket.info2.ID,search_msg(pack_1.upacket.info2.num_z)->name);
					else
					{
						send(p_search->sock_c,(char*)&pack_1,sizeof(packet),0);
					}
					break;

				case GENERALMSG:
				case CHECKMSG:
				case SYSMSG:
				p_search=NULL;
				p_search=LI_2.Search(pack_1.upacket.info2.num_z);
				 tt = time(NULL);//��䷵�ص�ֻ��һ��ʱ��cuo
				localtime_s(&t,&tt);
				 pack_1.upacket.info2.t=t;
				if(p_search==NULL)	
					add_message(pack_1.upacket.info2.num_z1,pack_1.upacket.info2.num_z
					,pack_1.upacket.info2.text,pack_1.upacket.info2.ID,search_msg(pack_1.upacket.info2.num_z1)->name);
				else
				{
					strcpy_s(pack_1.upacket.info2.name,search_msg(pack_1.upacket.info2.num_z1)->name);
					send(p_search->sock_c,(char*)&pack_1,sizeof(packet),0);
				}

				break;
				}
				break;
			case 3:
				//MessageBox(NULL,pack_1.upacket.info3.name,pack_1.upacket.info3.num_z,MB_OK);
				p_search_num_msg=search_msg(pack_1.upacket.info3.num_z);
				if(p_search_num_msg==NULL)add_msg_num_all(pack_1.upacket.info3.num_z,pack_1.upacket.info3.name,pack_1.upacket.info3.tel,
					pack_1.upacket.info3.age,pack_1.upacket.info3.sex);
				else
				{
					p_search_num_msg->age=pack_1.upacket.info3.age;
					p_search_num_msg->sex=pack_1.upacket.info3.sex;
					strcpy_s(p_search_num_msg->name,pack_1.upacket.info3.name);
					strcpy_s(p_search_num_msg->num_z,pack_1.upacket.info3.num_z);
					strcpy_s(p_search_num_msg->tel,pack_1.upacket.info3.tel);
				}
				break;
			}
		}
		}
		return 0;
	}

DWORD WINAPI connect_s(LPVOID lpParameter)
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		return -1;
	}
	sockaddr_in addr_s;
	//sockaddr_in addr_c;
	SOCKET sock_s;
	//SOCKET sock_c;
	sock_s=socket(AF_INET,SOCK_STREAM,0);
	memset(&addr_s,0,sizeof(addr_s));
	addr_s.sin_family = AF_INET;
	addr_s.sin_port=htons(5000);
	addr_s.sin_addr.s_addr=INADDR_ANY;
	if(bind(sock_s,(const sockaddr*)&addr_s,sizeof(addr_s))!=0)
	{
		//cout<<"��ʧ��"<<WSAGetLastError()<<endl;
		return -2;
	}
	if(listen(sock_s,5)!=0)
	{
		//cout<<"����ʧ��"<<WSAGetLastError()<<endl;
		return -3;
	}

	//int i=0;
	//sockaddr_in addr_c[num];
	//int len = sizeof(addr_c[0]);
	//SOCKET sock_c[num];
	//HANDLE ph[num];
	//DWORD p[num];
	//
	//while(i<num)
	//{
	//	sock_c[i]=accept(sock_s,(sockaddr*)&addr_c[i],&len);
	//	//cout<<inet_ntoa(addr_c[i].sin_addr)<<ntohs(addr_c[i].sin_port)<<endl;
	//	ph[i]=CreateThread(NULL,0,/*(LPTHREAD_START_ROUTINE)*/com,&sock_c[i],0,&p[i]);
	//	i++;
	//}
	while(1)
	{
		SOCKET sock_c;
		sockaddr_in addr_c;
		int len = sizeof(addr_c);
		sock_c=accept(sock_s,(sockaddr*)&addr_c,&len);
		CreateThread(NULL,0,/*(LPTHREAD_START_ROUTINE)*/com,&sock_c,0,NULL);
	}
	
	return 0;
}



//�Զ�������
void MakeFont(HDC hdc)
		{

			 HFONT hFont;    //������

			 hFont = CreateFont

                        (

                            30,13,    //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ

                            0, 0,    //�ı���б����������б��Ϊ0

                            FW_HEAVY,    //����

                            0,1,0,        //��б�壬���»��ߣ����л���

                            GB2312_CHARSET,    //�ַ���

                            OUT_DEFAULT_PRECIS,        

                            CLIP_DEFAULT_PRECIS,        

                            DEFAULT_QUALITY,        //һϵ�е�Ĭ��ֵ

                            DEFAULT_PITCH | FF_DONTCARE,    

                           // (TCHAR*)"����ϸ��"    //��������

						   (TCHAR*)"����"
                        );

			 SelectObject(hdc, hFont);

		}

struct SandLi
{
	char num_z[10];
	SOCKET sock_c;
	LinkList LI;
};

////�ͻ���������Ϣ�����߳�
//DWORD WINAPI ForRecv(LPVOID lpParameter)
//{
//	SandLi Sl=*(SandLi*)lpParameter;
//	net_net net_1;
//	while(1)
//	{
//		ClrearStruct((unsigned char*)&net_1,sizeof(net_net));
//		recv(Sl.sock_c,(char*)&net_1,sizeof(net_net),0);
//		NODE*p=LI_3.Search(net_1.num_z);
//		strcpy_s(net_1.num_z1,Sl.num_z);
//		if(p!=NULL)
//		{
//			send(p->sock_c,(char*)&net_1,sizeof(net_net),0);
//		}
//		else
//		{
//			add_message(net_1.num_z,net_1.num_z1,net_1.text);
//		}
//	}
//}
////�ͻ���������Ϣ����
//void ForMessage(SOCKET sock_c,char num_z[10],LinkList LI)
//{
//	SandLi Sl;
//	Sl.LI=LI;
//	Sl.sock_c=sock_c;
//	CreateThread(NULL,0,ForRecv,&Sl,0,NULL);
//}