// EventDrivenModellingForms.cpp: ������� ���� �������.

#include "stdafx.h"
//#include "vld.h"
#include "Form1.h"

using namespace EDM;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}
