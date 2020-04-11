
// GCSCGLDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#define WM_XIANCHENG WM_USER+1

// CGCSCGLDlg 对话框
class CGCSCGLDlg : public CDialogEx
{
// 构造
public:
	CGCSCGLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GCSCGL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT ms(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listctrl_jieguo;
	double m_edit_ds;
	double m_edit_mn;
	double m_edit_beta;
	double m_edit_k;
	CStatusBarCtrl m_wndStatusBar;
	afx_msg void OnBnClickedButton1();
	static DWORD WINAPI XianCheng(LPVOID lpParameter);
	CButton m_js;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CEdit m_edit_jd;
	int m_radio1;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
struct CANSHU
{
	double a;
	double jd;
	HWND hwnd;
	//CGCSCGLDlg *zz;传递窗口指针到线程里 控制控件
};
class JIEGUO
{
public:
	 JIEGUO();
	~JIEGUO();
	double i;
	double z1;
	double z2;
	double z3;
	double z4;
	int n;
};
