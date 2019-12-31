/******************************************************************
* ���� �̸� : FlowChartApp.h
* ��� : CWinApp ���
* �ۼ��� : ����â
* �ۼ����� : 2015�� 4�� 06�� 
*******************************************************************/

#include "FlowChartApp.h"
#include "FlowChartEditor.h"
#include "EditorIntroForm.h"

FlowChartApp flowChartApp;

BOOL FlowChartApp::InitInstance() {
	EditorIntroForm *intro = new EditorIntroForm;
	BOOL ret = intro->Create(NULL, NULL, WS_POPUP | WS_VISIBLE,
		CRect(650, 350, 1250, 750), NULL, NULL, WS_EX_CLIENTEDGE, NULL);
	ret = intro->ShowWindow(SW_NORMAL);
	intro->UpdateWindow();

	Sleep(5000);
	
	intro->DestroyWindow();


	FlowChartEditor *flowChartEditor = new FlowChartEditor;

	flowChartEditor->Create(NULL, "������� - FlowChart",WS_OVERLAPPEDWINDOW);
	this->m_nCmdShow = SW_SHOWMAXIMIZED;
	flowChartEditor->ShowWindow(this->m_nCmdShow);
	flowChartEditor->UpdateWindow();
	this->m_pMainWnd = flowChartEditor;

	return TRUE;
}