
// DetectFeaturePointDlg.h : ͷ�ļ�
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

// CDetectFeaturePointDlg �Ի���
class CDetectFeaturePointDlg : public CDialogEx
{
// ����
public:
	CDetectFeaturePointDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DETECTFEATUREPOINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CString GetDirectory();//·���ļ���
	Mat m_img1,m_img2;//�����������ƥ���ͼ��
	Mat descriptors1, descriptors2;//������������
	vector<KeyPoint> key_points1, key_points2;//�ؼ���
	Mat img_matches;//ƥ���Ľ��
	double detecttime;
	int MatchPointNum;
	CSliderCtrl m_slider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	
};
