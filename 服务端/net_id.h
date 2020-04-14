//ͨ��ID

#define LOG_IN			0xfa	//��½
#define REGISTER		0xfb	//ע��
#define LOG_SUCCEED		0xea	//��½�ɹ�
#define LOG_FAIL		0xeb	//��½ʧ��
#define LOG_TIME_OUT	0xbd	//��½��ʱ
#define CONNECT_BREAK	0xbe	//�Ͽ�����
#define TRANS_MESSAGE	0xcc	//������Ϣ
#define REGISTER_RETURN 0xfc	//ע�ᷴ��
#define COMMEND			0xfd	//������Ϣ
#define CHANGENUMM		0xfe	//������
#define CHANGESUCCEED	0xff	//���ܳɹ�
#define CHANGEFAIL		0xaa	//����ʧ��
#define SEARCHFRIEND	0xab	//���Һ���
#define FRIENDEXIT		0xac	//���Ѵ���
#define FRIENDNULL		0xad	//���Ѳ�����
#define CM_AGREE		5562	//��֤ͨ��
#define CM_REFUSE		5563	//��֤�ܾ�

//ͨ��ID2
#define GENERALMSG		0xae	//һ����Ϣ
#define CHECKMSG		0xaf	//��֤��Ϣ
#define SYSMSG			5561	//ϵͳ��Ϣ

//ͨ��ID3
#define LOCALMSG		5564	//������Ϣ
#define FRDMSG			5565	//������Ϣ


/***ͨ��Э��***/
struct packet
{
	char commend;
	union
	{
		struct param1
		{
			int		ID;
			int		len;
			char	num_z[10];
			char	num_m[16];
			char	num_mm[16];
			char	*add;
		}info1;

		struct param2
		{
			int  ID;
			tm	 t;				//ʱ��
			char name[16];
			char num_z[10];			//Ҫ���͵�Ŀ��
			char text[512];			//���͵���Ϣ
			char num_z1[10];		//�������˺�
		}info2;

		struct param3
		{
			int ID;
			char num_z[10];
			char name[16];
			char tel[12];
			int  sex;
			int  age;
		}info3;
	}upacket;
};