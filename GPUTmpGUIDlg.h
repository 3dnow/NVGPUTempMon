
// GPUTmpGUIDlg.h: 头文件
//

#pragma once
#include <vector>
#include <afxwin.h>
#include <gdiplus.h>
using namespace Gdiplus;
// CGPUTmpGUIDlg 对话框
class CGPUTmpGUIDlg : public CDialogEx
{
// 构造
public:
	CGPUTmpGUIDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CGPUTmpGUIDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPUTMPGUI_DIALOG };
#endif

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
	DECLARE_MESSAGE_MAP()
private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	struct TemperatureData {
		int coreTemp;
		int hotspotTemp;
		int memoryTemp;
		CString timeLabel;
	};

	std::vector<TemperatureData> temperatureHistory;
	void UpdateTemperatureData();
	int CalculateTemperature(CPoint point);
	CBrush hoverInfoBackgroundBrush; // 添加背景刷
	CFont m_hoverInfoFont;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);


private:
	CStatic hoverInfo;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
