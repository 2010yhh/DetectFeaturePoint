
// DetectFeaturePointDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
///////////////////
#include<Windows.h>
#include "CvvImage.h"
#include <highgui.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "afxwin.h"
using namespace cv;
///////////////////

// CDetectFeaturePointDlg 对话框
class CDetectFeaturePointDlg : public CDialogEx
{
// 构造
public:
	CDetectFeaturePointDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DETECTFEATUREPOINT_DIALOG };

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
public:
	afx_msg void OnBnClickedOpenimg();
	CListCtrl m_imgList;
	CComboBox m_FeatureType;
	afx_msg void OnBnClickedDetect();
	afx_msg void OnNMClickImagelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult);
	////////////////////
    vector<Mat> m_images;
	void ShowImage(IplImage* img, UINT ID);
	CString GetDirectory();//路径文件夹
	Mat m_img1,m_img2;//输入的两幅待匹配的图像
	Mat descriptors1, descriptors2;//特征点描述子
	vector<KeyPoint> key_points1, key_points2;//关键点
	Mat img_matches;//匹配后的结果
	double detecttime;
	int MatchPointNum;
	CSliderCtrl m_slider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	
};
