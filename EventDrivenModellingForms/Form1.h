#pragma once

//git checkout test

#include "OpenGLPanelExtention.h"
#include "Events.h"
#include "NetEventHandler.h"
#include "Actor.h"
#include "ActorsContainer.h"
#include "CellsContainer.h"
#include "BordersContainer.h"
#include "PriorityQueue.h"
#include "ProcessTimer.h"
#include "Properties.h"
#include "EDM_Math.h"

#include <time.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace OpenGLPanelExtention;
using namespace EDM;
using namespace EDM::Model;
using namespace EDM::Logic;

namespace EDM {

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{

	public:
		Form1(void)
		{
			InitializeComponent();	

			cbShowCellsGrid->Checked = EDM_Prop->ShowCellsGrid;

			pgSettings->SelectedObject = Properties::Instance;

			//srand( (unsigned)time( NULL ) ); // uncomment this to swich on random generation

			InitProcessVars();		

			InitializeOpenGLPanel();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			ClearProcessVars();
		}

	#pragma region Fields
		private: 
			//here is my OpenGL panel
			OpenGLPanelExtention::OpenGLPanel^ m_oglPanel; 		

			CellContainer *cellContInst;
			ActorsContainer *acInst;
			PriorityQueue *queueInst;

	#pragma endregion Fields

	#pragma  region UI Elements

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Timer^  timerDrowing;
	private: System::Windows::Forms::Timer^  timerQueueEvent;
	private: System::Windows::Forms::GroupBox^  gbProcessInfo;
	private: System::Windows::Forms::Label^  lTimeElapsed;
	private: System::Windows::Forms::Label^  lTimeElapsedTxt;
	private: System::Windows::Forms::Label^  lEventsCounter;
	private: System::Windows::Forms::Label^  lEventsCounterTxt;
	private: System::Windows::Forms::GroupBox^  gbSettings;
	private: System::Windows::Forms::PropertyGrid^  pgSettings;
	private: System::Windows::Forms::GroupBox^  gbControl;
	private: System::Windows::Forms::GroupBox^  gbPlayer;

	private: System::Windows::Forms::Button^  bStop;
	private: System::Windows::Forms::Button^  bStart;
	private: System::Windows::Forms::Button^  bReset;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  tsslCrntCoordTxt;
	private: System::Windows::Forms::ToolStripStatusLabel^  tsslCrntCoord;
	private: System::Windows::Forms::GroupBox^  gbViewSettings;
	private: System::Windows::Forms::CheckBox^  cbShowCellsGrid;



	private: System::ComponentModel::IContainer^  components;
#pragma endregion UI Elements

	#pragma region Windows Form Designer generated code

		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timerDrowing = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerQueueEvent = (gcnew System::Windows::Forms::Timer(this->components));
			this->gbProcessInfo = (gcnew System::Windows::Forms::GroupBox());
			this->gbSettings = (gcnew System::Windows::Forms::GroupBox());
			this->pgSettings = (gcnew System::Windows::Forms::PropertyGrid());
			this->lEventsCounter = (gcnew System::Windows::Forms::Label());
			this->lEventsCounterTxt = (gcnew System::Windows::Forms::Label());
			this->lTimeElapsed = (gcnew System::Windows::Forms::Label());
			this->lTimeElapsedTxt = (gcnew System::Windows::Forms::Label());
			this->gbControl = (gcnew System::Windows::Forms::GroupBox());
			this->gbViewSettings = (gcnew System::Windows::Forms::GroupBox());
			this->cbShowCellsGrid = (gcnew System::Windows::Forms::CheckBox());
			this->gbPlayer = (gcnew System::Windows::Forms::GroupBox());
			this->bReset = (gcnew System::Windows::Forms::Button());
			this->bStop = (gcnew System::Windows::Forms::Button());
			this->bStart = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->tsslCrntCoordTxt = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tsslCrntCoord = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->gbProcessInfo->SuspendLayout();
			this->gbSettings->SuspendLayout();
			this->gbControl->SuspendLayout();
			this->gbViewSettings->SuspendLayout();
			this->gbPlayer->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(266, 13);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(440, 440);
			this->panel1->TabIndex = 0;
			this->panel1->Visible = false;
			// 
			// timerDrowing
			// 
			this->timerDrowing->Interval = 32;
			this->timerDrowing->Tick += gcnew System::EventHandler(this, &Form1::timerDrowing_Tick);
			// 
			// timerQueueEvent
			// 
			this->timerQueueEvent->Tick += gcnew System::EventHandler(this, &Form1::timerQueueEvent_Tick);
			// 
			// gbProcessInfo
			// 
			this->gbProcessInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->gbProcessInfo->Controls->Add(this->gbSettings);
			this->gbProcessInfo->Controls->Add(this->lEventsCounter);
			this->gbProcessInfo->Controls->Add(this->lEventsCounterTxt);
			this->gbProcessInfo->Controls->Add(this->lTimeElapsed);
			this->gbProcessInfo->Controls->Add(this->lTimeElapsedTxt);
			this->gbProcessInfo->Location = System::Drawing::Point(12, 12);
			this->gbProcessInfo->Name = L"gbProcessInfo";
			this->gbProcessInfo->Size = System::Drawing::Size(248, 441);
			this->gbProcessInfo->TabIndex = 2;
			this->gbProcessInfo->TabStop = false;
			this->gbProcessInfo->Text = L"Process info";
			// 
			// gbSettings
			// 
			this->gbSettings->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->gbSettings->Controls->Add(this->pgSettings);
			this->gbSettings->Location = System::Drawing::Point(6, 58);
			this->gbSettings->Name = L"gbSettings";
			this->gbSettings->Size = System::Drawing::Size(235, 377);
			this->gbSettings->TabIndex = 4;
			this->gbSettings->TabStop = false;
			this->gbSettings->Text = L"Settings";
			// 
			// pgSettings
			// 
			this->pgSettings->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pgSettings->Location = System::Drawing::Point(3, 16);
			this->pgSettings->Name = L"pgSettings";
			this->pgSettings->Size = System::Drawing::Size(229, 358);
			this->pgSettings->TabIndex = 0;
			this->pgSettings->PropertyValueChanged += gcnew System::Windows::Forms::PropertyValueChangedEventHandler(this, &Form1::pgSettings_PropertyValueChanged);
			// 
			// lEventsCounter
			// 
			this->lEventsCounter->AutoSize = true;
			this->lEventsCounter->Location = System::Drawing::Point(90, 42);
			this->lEventsCounter->Name = L"lEventsCounter";
			this->lEventsCounter->Size = System::Drawing::Size(13, 13);
			this->lEventsCounter->TabIndex = 3;
			this->lEventsCounter->Text = L"0";
			// 
			// lEventsCounterTxt
			// 
			this->lEventsCounterTxt->AutoSize = true;
			this->lEventsCounterTxt->Location = System::Drawing::Point(7, 42);
			this->lEventsCounterTxt->Name = L"lEventsCounterTxt";
			this->lEventsCounterTxt->Size = System::Drawing::Size(82, 13);
			this->lEventsCounterTxt->TabIndex = 2;
			this->lEventsCounterTxt->Text = L"Events counter:";
			// 
			// lTimeElapsed
			// 
			this->lTimeElapsed->AutoSize = true;
			this->lTimeElapsed->Location = System::Drawing::Point(90, 20);
			this->lTimeElapsed->Name = L"lTimeElapsed";
			this->lTimeElapsed->Size = System::Drawing::Size(13, 13);
			this->lTimeElapsed->TabIndex = 1;
			this->lTimeElapsed->Text = L"0";
			// 
			// lTimeElapsedTxt
			// 
			this->lTimeElapsedTxt->AutoSize = true;
			this->lTimeElapsedTxt->Location = System::Drawing::Point(7, 20);
			this->lTimeElapsedTxt->Name = L"lTimeElapsedTxt";
			this->lTimeElapsedTxt->Size = System::Drawing::Size(73, 13);
			this->lTimeElapsedTxt->TabIndex = 0;
			this->lTimeElapsedTxt->Text = L"Time elapsed:";
			// 
			// gbControl
			// 
			this->gbControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gbControl->Controls->Add(this->gbViewSettings);
			this->gbControl->Controls->Add(this->gbPlayer);
			this->gbControl->Location = System::Drawing::Point(712, 12);
			this->gbControl->Name = L"gbControl";
			this->gbControl->Size = System::Drawing::Size(200, 441);
			this->gbControl->TabIndex = 5;
			this->gbControl->TabStop = false;
			this->gbControl->Text = L"Control";
			// 
			// gbViewSettings
			// 
			this->gbViewSettings->Controls->Add(this->cbShowCellsGrid);
			this->gbViewSettings->Location = System::Drawing::Point(6, 135);
			this->gbViewSettings->Name = L"gbViewSettings";
			this->gbViewSettings->Size = System::Drawing::Size(188, 52);
			this->gbViewSettings->TabIndex = 5;
			this->gbViewSettings->TabStop = false;
			this->gbViewSettings->Text = L"View setting";
			// 
			// cbShowCellsGrid
			// 
			this->cbShowCellsGrid->AutoSize = true;
			this->cbShowCellsGrid->Checked = true;
			this->cbShowCellsGrid->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbShowCellsGrid->Location = System::Drawing::Point(7, 20);
			this->cbShowCellsGrid->Name = L"cbShowCellsGrid";
			this->cbShowCellsGrid->Size = System::Drawing::Size(97, 17);
			this->cbShowCellsGrid->TabIndex = 0;
			this->cbShowCellsGrid->Text = L"Show cells grid";
			this->cbShowCellsGrid->UseVisualStyleBackColor = true;
			this->cbShowCellsGrid->CheckedChanged += gcnew System::EventHandler(this, &Form1::cbShowCellsGrid_CheckedChanged);
			// 
			// gbPlayer
			// 
			this->gbPlayer->Controls->Add(this->bReset);
			this->gbPlayer->Controls->Add(this->bStop);
			this->gbPlayer->Controls->Add(this->bStart);
			this->gbPlayer->Location = System::Drawing::Point(6, 19);
			this->gbPlayer->Name = L"gbPlayer";
			this->gbPlayer->Size = System::Drawing::Size(188, 110);
			this->gbPlayer->TabIndex = 4;
			this->gbPlayer->TabStop = false;
			this->gbPlayer->Text = L"Player";
			// 
			// bReset
			// 
			this->bReset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->bReset->ForeColor = System::Drawing::Color::Tomato;
			this->bReset->Location = System::Drawing::Point(6, 77);
			this->bReset->Name = L"bReset";
			this->bReset->Size = System::Drawing::Size(176, 23);
			this->bReset->TabIndex = 3;
			this->bReset->Text = L"Reset";
			this->bReset->UseVisualStyleBackColor = true;
			this->bReset->Click += gcnew System::EventHandler(this, &Form1::bReset_Click);
			// 
			// bStop
			// 
			this->bStop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->bStop->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->bStop->Location = System::Drawing::Point(6, 48);
			this->bStop->Name = L"bStop";
			this->bStop->Size = System::Drawing::Size(176, 23);
			this->bStop->TabIndex = 1;
			this->bStop->Text = L"Stop";
			this->bStop->UseVisualStyleBackColor = true;
			this->bStop->Click += gcnew System::EventHandler(this, &Form1::bStop_Click);
			// 
			// bStart
			// 
			this->bStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->bStart->ForeColor = System::Drawing::Color::ForestGreen;
			this->bStart->Location = System::Drawing::Point(6, 19);
			this->bStart->Name = L"bStart";
			this->bStart->Size = System::Drawing::Size(176, 23);
			this->bStart->TabIndex = 0;
			this->bStart->Text = L"Start";
			this->bStart->UseVisualStyleBackColor = true;
			this->bStart->Click += gcnew System::EventHandler(this, &Form1::bStart_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsslCrntCoordTxt, 
				this->tsslCrntCoord});
			this->statusStrip1->Location = System::Drawing::Point(0, 456);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(924, 22);
			this->statusStrip1->TabIndex = 6;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// tsslCrntCoordTxt
			// 
			this->tsslCrntCoordTxt->Name = L"tsslCrntCoordTxt";
			this->tsslCrntCoordTxt->Size = System::Drawing::Size(84, 17);
			this->tsslCrntCoordTxt->Text = L"Current coord:";
			// 
			// tsslCrntCoord
			// 
			this->tsslCrntCoord->Name = L"tsslCrntCoord";
			this->tsslCrntCoord->Size = System::Drawing::Size(39, 17);
			this->tsslCrntCoord->Text = L"[NaN]";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(924, 478);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->gbControl);
			this->Controls->Add(this->gbProcessInfo);
			this->Controls->Add(this->panel1);
			this->MinimumSize = System::Drawing::Size(500, 510);
			this->Name = L"Form1";
			this->Text = L"Event Driven Modeling [KhAI, Informatics dep, Ruslan Seleznov. 2013]";
			this->gbProcessInfo->ResumeLayout(false);
			this->gbProcessInfo->PerformLayout();
			this->gbSettings->ResumeLayout(false);
			this->gbControl->ResumeLayout(false);
			this->gbViewSettings->ResumeLayout(false);
			this->gbViewSettings->PerformLayout();
			this->gbPlayer->ResumeLayout(false);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 

		void InitializeOpenGLPanel()
		{
			m_oglPanel = gcnew OpenGLPanelExtention::OpenGLPanel(420, 420);
			m_oglPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Top 
				| System::Windows::Forms::AnchorStyles::Bottom
				| System::Windows::Forms::AnchorStyles::Left 
				| System::Windows::Forms::AnchorStyles::Right);
			m_oglPanel->BorderStyle = BorderStyle::FixedSingle;
			m_oglPanel->Location = System::Drawing::Point(266, 13);
			m_oglPanel->Name = L"m_oglPanel";
			m_oglPanel->Size = System::Drawing::Size(420, 420);
			m_oglPanel->TabIndex = 0;							
			m_oglPanel->Resize += gcnew System::EventHandler(this, &Form1::m_oglPanel_Resize);
			m_oglPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::m_oglPanel_Paint);
			m_oglPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::m_oglPanel_MouseMove);
			//m_oglPanel->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::m_oglPanel_MouseClick);
			//m_oglPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::m_oglPanel_MouseDown);
			//m_oglPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::m_oglPanel_MouseUp);
			this->Controls->Add(m_oglPanel);
		}

		void InitProcessVars()
		{
			cellContInst = CellContainer::Instance();
			acInst = ActorsContainer::Instance();
			queueInst = PriorityQueue::Instance();
				 
			EDM_Prop->LocalTime = 0.0;
			EDM_Prop->ActualTime = 0.0;
			EDM_Prop->EventsCounter = 0;
			timerDrowing->Interval = EDM_Prop->DrawingPeriodInSeconds * 1000;
		}

		void ClearProcessVars()
		{
			queueInst->FreeInst();
			acInst->FreeInst();
			cellContInst->FreeInst();
		}

		void DrawSceneAndUpdateUI()
		{
			m_oglPanel->Render(EDM_Prop->ActualTime);
			this->lTimeElapsed->Text = EDM_Prop->ActualTime.ToString();
			this->lEventsCounter->Text = EDM_Prop->EventsCounter.ToString();
		}

		void StartProcess()
		{
			timerDrowing->Start();
		}

		void ResetProcess()
		{
			ClearProcessVars();
			InitProcessVars();
			DrawSceneAndUpdateUI();
		}

	#pragma region Form events

private: System::Void m_oglPanel_Resize(System::Object^  sender, System::EventArgs^  e) 
		 {
			 m_oglPanel->ReSizeGLScene(m_oglPanel->Width, m_oglPanel->Height);
			 DrawSceneAndUpdateUI();
		 }

private: System::Void m_oglPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {
			 DrawSceneAndUpdateUI();
		 }

private: System::Void m_oglPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			Point2F *position = m_oglPanel->GetPointInWorldCoordinates(e->Location.X, e->Location.Y);
			this->tsslCrntCoord->Text = position->x.ToString() + L" " + position->y.ToString();	
		 }

private: System::Void timerDrowing_Tick(System::Object^  sender, System::EventArgs^  e) 
	 	 {
			 queueInst->PlayNetEventsForTime();

			 DrawSceneAndUpdateUI();
	 	 }
private: System::Void timerQueueEvent_Tick(System::Object^  sender, System::EventArgs^  event) 
		 {
			 timerQueueEvent->Stop();
			 timerDrowing->Stop();
			 EDM_Prop->EventsCounter++;

			 int actualActorInd = queueInst->GetFirst();
			 EDM_Prop->LocalTime = acInst->actors[actualActorInd].evnt->args->time;
			 acInst->actors[actualActorInd].evnt->OnHandler();

			 int nextActorInd = queueInst->GetFirst();
			 double newTickTime = (acInst->actors[nextActorInd].evnt->args->time - EDM_Prop->LocalTime) * 1000;
			 if (newTickTime < 1)
				 newTickTime = 1;
			 try
			 {
				 timerQueueEvent->Interval = (int)newTickTime;
				 timerQueueEvent->Start();
				 timerDrowing->Start();
			 }
			 catch (...)
			 {
				 timerQueueEvent->Stop();
				 timerDrowing->Stop();
				 String^ message = "Event number: " + EDM_Prop->EventsCounter.ToString();
				 String^ caption = "Negative time.";
				 MessageBoxButtons buttons = MessageBoxButtons::OK;
				 if(MessageBox::Show(message, caption,buttons) == ::DialogResult::OK)
				 {
					 timerQueueEvent->Start();
					 timerDrowing->Start();
				 }

			 }
			
			 //procTimer->Start(0);
		 }
		 
private: System::Void bStart_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 StartProcess();
			 bStart->Enabled = false;
			 pgSettings->Enabled = false;
		 }

private: System::Void bStop_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 timerDrowing->Stop();
			 timerQueueEvent->Stop();
			 bStart->Enabled = true;
			 pgSettings->Enabled = true;
		 }

private: System::Void bReset_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bStop_Click(sender, e);
			 ResetProcess();
		 }

private: System::Void pgSettings_PropertyValueChanged(
			 System::Object^  s, System::Windows::Forms::PropertyValueChangedEventArgs^  e) 
		 {			 
			 ResetProcess();
			 m_oglPanel->ReSizeGLScene(m_oglPanel->Width, m_oglPanel->Height);
			 DrawSceneAndUpdateUI();
		 }

private: System::Void cbShowCellsGrid_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 EDM_Prop->ShowCellsGrid = !EDM_Prop->ShowCellsGrid;
			 DrawSceneAndUpdateUI();
		 }

#pragma endregion

	};
}