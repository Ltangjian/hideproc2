// hideproc2Dlg.h : header file
//

#if !defined(AFX_HIDEPROC2DLG_H__1A9DB663_5467_4792_82BC_8ECC5B22D6C2__INCLUDED_)
#define AFX_HIDEPROC2DLG_H__1A9DB663_5467_4792_82BC_8ECC5B22D6C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<windows.h>
#include<Accctrl.h>
#include<Aclapi.h>

#define NT_SUCCESS(Status)((NTSTATUS)(Status) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define STATUS_ACCESS_DENIED ((NTSTATUS)0xC0000022L)

typedef LONG NTSTATUS;

typedef struct _IO_STATUS_BLOCK 
{
    NTSTATUS Status;
    ULONG Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _UNICODE_STRING 
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

#define OBJ_INHERIT                0x00000002L
#define OBJ_PERMANENT            0x00000010L
#define OBJ_EXCLUSIVE            0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF                0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE        0x00000200L
#define OBJ_VALID_ATTRIBUTES    0x000003F2L

typedef struct _OBJECT_ATTRIBUTES 
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES; 

typedef NTSTATUS (CALLBACK* ZWOPENSECTION)(
										   OUT PHANDLE SectionHandle,
										   IN ACCESS_MASK DesiredAccess,
										   IN POBJECT_ATTRIBUTES ObjectAttributes
										   );

typedef VOID (CALLBACK* RTLINITUNICODESTRING)(
											  IN OUT PUNICODE_STRING DestinationString,
											  IN PCWSTR SourceString
											  );


/////////////////////////////////////////////////////////////////////////////
// CHideproc2Dlg dialog

class CHideproc2Dlg : public CDialog
{
// Construction
public:
	BOOL HideProcess();
	CHideproc2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHideproc2Dlg)
	enum { IDD = IDD_HIDEPROC2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHideproc2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHideproc2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL YHideProcess();
	BOOL SetData(PVOID addr,ULONG data);
	ULONG GetData(PVOID addr);
	PVOID LinearToPhys(PULONG BaseAddress, PVOID addr);
	HANDLE OpenPhysicalMemory();
	VOID SetPhyscialMemorySectionCanBeWrited(HANDLE hSection);
	VOID CloseNTDLL();
	BOOL InitNTDLL();
	RTLINITUNICODESTRING RtlInitUnicodeString;
	ZWOPENSECTION ZwOpenSection;
	HMODULE g_hNtDLL;
	PVOID g_pMapPhysicalMemory;
	HANDLE g_hMPM;
	OSVERSIONINFO g_osvi;

/*
	HMODULE g_hNtDLL = NULL;
	PVOID g_pMapPhysicalMemory = NULL;
	HANDLE g_hMPM = NULL;
  */
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIDEPROC2DLG_H__1A9DB663_5467_4792_82BC_8ECC5B22D6C2__INCLUDED_)
