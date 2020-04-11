
// GCSCGLDlg.cpp : 实现文件
#include "stdafx.h"
#include "GCSCGL.h"
#include "GCSCGLDlg.h"
#include "afxdialogex.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
// CGCSCGLDlg 对话框
CGCSCGLDlg::CGCSCGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGCSCGLDlg::IDD, pParent)
	, m_edit_ds(9)
	, m_edit_mn(10)
	, m_edit_beta(9)
	, m_edit_k(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_radio1=0;
}
void CGCSCGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl_jieguo);
	DDX_Text(pDX, IDC_EDIT1, m_edit_ds);
	DDX_Text(pDX, IDC_EDIT2, m_edit_mn);
	DDX_Text(pDX, IDC_EDIT3, m_edit_beta);
	DDX_Text(pDX, IDC_EDIT4, m_edit_k);
	DDX_Control(pDX, IDC_BUTTON1, m_js);
	//  DDX_Text(pDX, IDC_EDIT6, m_cdglb);
	DDX_Control(pDX, IDC_EDIT5, m_edit_jd);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
}
BEGIN_MESSAGE_MAP(CGCSCGLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGCSCGLDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_XIANCHENG,ms)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO1, &CGCSCGLDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGCSCGLDlg::OnBnClickedRadio2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CGCSCGLDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()
// CGCSCGLDlg 消息处理程序
BOOL CGCSCGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_edit_jd.SetReadOnly(TRUE);
	m_edit_jd.SetWindowTextA("0.000005");
	int i=0;
	m_listctrl_jieguo.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listctrl_jieguo.InsertColumn(i++,"挂轮比   i", LVCFMT_LEFT,75);
	m_listctrl_jieguo.InsertColumn(i++,"Z1", LVCFMT_LEFT,35);
	m_listctrl_jieguo.InsertColumn(i++,"Z2", LVCFMT_LEFT,35);
	m_listctrl_jieguo.InsertColumn(i++,"Z3", LVCFMT_LEFT,35);
	m_listctrl_jieguo.InsertColumn(i++,"Z4", LVCFMT_LEFT,35);
	m_listctrl_jieguo.InsertColumn(i++,"挂轮实际误差", LVCFMT_LEFT,85);
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	m_wndStatusBar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM,CRect(0,0,0,0),this,3);
	int part[3]={200,310,-1};
	m_wndStatusBar.SetParts(3,part);
	m_wndStatusBar.SetText("请输入计算参数后点击计算按钮",0,0);
	m_wndStatusBar.SetText("灯塔市通用机械厂",1,0);
	SetTimer(1,1000,NULL);
	CTime t;
	t=CTime::GetCurrentTime();
	m_wndStatusBar.SetText(t.Format("%H:%M:%S"),2,0);
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CGCSCGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CGCSCGLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		//使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		//绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGCSCGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
JIEGUO::JIEGUO()
{
	i=0;
	n=0;
	z1=0;
	z2=0;
	z3=0;
	z4=0;
}
JIEGUO::~JIEGUO()
{	
}
void CGCSCGLDlg::OnBnClickedButton1()
{	
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	double PI;
	PI=3.14159326;
	CANSHU *canshu=new CANSHU;
	UpdateData();
	canshu->a=m_edit_ds*sin(m_edit_beta*PI/180)/m_edit_mn/m_edit_k;
	canshu->hwnd=m_hWnd;
	//canshu->zz=this;
	char ch[10];
	m_edit_jd.GetWindowTextA(ch,10);
	canshu->jd=atof(ch);
	//m_cdglb=(canshu->a);
	UpdateData(FALSE);
	m_listctrl_jieguo.DeleteAllItems();
	CloseHandle(CreateThread(NULL,0,XianCheng,(LPVOID)canshu,0,NULL));
	// TODO: 在此添加控件通知处理程序代码
}
LRESULT CGCSCGLDlg::ms(WPARAM wParam,LPARAM lParam)
{		
		CString str[6];
		str[0].Format("%7.7f",((JIEGUO*)lParam)->i);
		str[1].Format("%d",(int)((JIEGUO*)lParam)->z1);
		str[2].Format("%d",(int)((JIEGUO*)lParam)->z2);
		str[3].Format("%d",(int)((JIEGUO*)lParam)->z3);
		str[4].Format("%d",(int)((JIEGUO*)lParam)->z4);
		if(((JIEGUO*)lParam)->z1==1)
			{
				GetDlgItem(IDC_BUTTON1)->EnableWindow();
			}
		else
		{
			if(((JIEGUO*)lParam)->n)
			{
				int nRow = m_listctrl_jieguo.InsertItem(((JIEGUO*)lParam)->n,str[0]);
				m_listctrl_jieguo.SetItemText(nRow, 1, str[1]);
				m_listctrl_jieguo.SetItemText(nRow, 2, str[2]);
				m_listctrl_jieguo.SetItemText(nRow, 3, str[3]);
				m_listctrl_jieguo.SetItemText(nRow, 4, str[4]);
			}
		}
		str[5].Format("计算出%d个结果",((JIEGUO*)lParam)->n);
		m_wndStatusBar.SetText(str[5],0,0);
		return TRUE;
}
DWORD WINAPI CGCSCGLDlg:: XianCheng(LPVOID lpParameter)
{	
	double x=((CANSHU*)lpParameter)->a;
	HWND hwnd=((CANSHU*)lpParameter)->hwnd;
	double jd=((CANSHU*)lpParameter)->jd;
	//CGCSCGLDlg *zz=((CANSHU*)lpParameter)->zz;
	delete lpParameter;
	FILE *file;
	file=fopen("现有齿轮齿数.txt","r");
	if(!file)
	{
	AfxMessageBox("当前目录没有发现“现有齿轮齿数.txt”文件");
	return 0;
	}
	fseek(file,0,SEEK_END);
	int len=ftell(file) ,sum=0;
	char *pBuf;
	pBuf=new char[len+1];
	fseek(file,0,SEEK_SET);
	fread(pBuf,1,len,file);
	pBuf[len]=0;
	for(int i=0;i<=len;i++)
	{
		if(pBuf[i]==',')
			sum++;
	}
	double *z;
	z=new double[sum];
	fseek(file,0,SEEK_SET);
	long le;
	for(int j=0;j<=sum;j++)
	{
		fscanf(file,"%lf",&z[j]);
		le=ftell(file);
		fseek(file,le+1,SEEK_SET);
	}
	fseek(file,0,SEEK_SET);
	fclose(file);
	JIEGUO *stra;
	stra=new JIEGUO;
	for(int z1=0;z1<sum;z1++)
	{
		for(int z2=0;z2<sum;z2++)
		{
			for(int z3=0;z3<sum;z3++)
			{
				for(int z4=0;z4<sum;z4++)
				{
					if(z[z1]<z[z3]&&z[z2]<z[z4])
					{
						if(x<1)
							{
								if(fabs(x-z[z1]/z[z2]*z[z3]/z[z4])<=jd)
								{
									stra->i=z[z1]/z[z2]*z[z3]/z[z4]; 
									stra->z1=z[z1];
									stra->z2=z[z2];
									stra->z3=z[z3];
									stra->z4=z[z4];
									stra->n+=1;
									::SendMessage(hwnd,WM_XIANCHENG,0,(LPARAM)stra);
								}
							}
						else
							{
								if(fabs(x-1/(z[z1]/z[z2]*z[z3]/z[z4]))<=jd)
								{
									stra->i=z[z2]/z[z1]*z[z4]/z[z3]; 
									stra->z1=z[z2];
									stra->z2=z[z1];
									stra->z3=z[z4];
									stra->z4=z[z3];
									stra->n+=1;
									::SendMessage(hwnd,WM_XIANCHENG,0,(LPARAM)stra);
								}
						
							}
					}
				}
			}
		}
	}
	if(!stra->n)
	{
	::SendMessage(hwnd,WM_XIANCHENG,0,(LPARAM)stra);
	}
	stra->z1=1;
	::SendMessage(hwnd,WM_XIANCHENG,0,(LPARAM)stra);
	delete z,stra;
	delete pBuf;
	return 0;
}
void CGCSCGLDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime t;
	t=CTime::GetCurrentTime();
	m_wndStatusBar.SetText(t.Format("%H:%M:%S"),2,0);
	CDialogEx::OnTimer(nIDEvent);
}


void CGCSCGLDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_jd.SetReadOnly(TRUE);
	m_edit_jd.SetWindowTextA("0.000005");
}


void CGCSCGLDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_jd.SetReadOnly(FALSE);
	MessageBox("请重新输入精度","友情提示");
}


void CGCSCGLDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
