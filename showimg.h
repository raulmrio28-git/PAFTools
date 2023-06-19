#pragma once
#include <iostream>
#include "AniPAF/AniPAF.h"
#include "RgbManipulate/Main.h"

namespace PAFTools {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for showimg
	/// </summary>
	public ref class showimg : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::PictureBox^  decPic;
	public:
		showimg(TAniPaf *hPAF)
		{
			InitializeComponent();
			hAP = hPAF;
			this->upDownFrames->Maximum = AniPaf_GetFrameNum(hAP);
			this->Width = AniPaf_GetWidth(hAP) + 20;
			this->Height = AniPaf_GetHeight(hAP) + 70;
			this->decPic->Width = AniPaf_GetWidth(hAP);
			this->decPic->Height = AniPaf_GetHeight(hAP);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~showimg()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  frameLbl;
	private: System::Windows::Forms::NumericUpDown^  upDownFrames;
	private: TAniPaf* hAP;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		/// <summary>
		/// Set A value in BGRA buffer to 255
		/// </summary>
		void SetTranspTo255(char* buffer, int bytes)
		{
			for (int w = 3; w < bytes; w += 4)
			{
				buffer[w] = 0xff;
			}
		}
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->frameLbl = (gcnew System::Windows::Forms::Label());
			this->upDownFrames = (gcnew System::Windows::Forms::NumericUpDown());
			this->decPic = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->upDownFrames))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->decPic))->BeginInit();
			this->SuspendLayout();
			// 
			// frameLbl
			// 
			this->frameLbl->AutoSize = true;
			this->frameLbl->Location = System::Drawing::Point(5, 9);
			this->frameLbl->Name = L"frameLbl";
			this->frameLbl->Size = System::Drawing::Size(52, 17);
			this->frameLbl->TabIndex = 0;
			this->frameLbl->Text = L"Frame:";
			// 
			// upDownFrames
			// 
			this->upDownFrames->Location = System::Drawing::Point(60, 6);
			this->upDownFrames->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->upDownFrames->Name = L"upDownFrames";
			this->upDownFrames->Size = System::Drawing::Size(44, 22);
			this->upDownFrames->TabIndex = 1;
			this->upDownFrames->ValueChanged += gcnew System::EventHandler(this, &showimg::upDownFrames_ValueChanged);
			this->upDownFrames->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// decPic
			// 
			this->decPic->Location = System::Drawing::Point(3, 36);
			this->decPic->Name = L"decPic";
			this->decPic->Size = System::Drawing::Size(10, 10);
			this->decPic->TabIndex = 0;
			this->decPic->TabStop = false;
			// 
			// showimg
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(148, 55);
			this->Controls->Add(this->decPic);
			this->Controls->Add(this->upDownFrames);
			this->Controls->Add(this->frameLbl);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"showimg";
			this->ShowIcon = false;
			this->Text = L"View image";
			this->Load += gcnew System::EventHandler(this, &showimg::showimg_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &showimg::showimg_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->upDownFrames))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->decPic))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
		/// <summary>
		/// Decode WICA frame to PictureBox
		/// </summary>
	private: System::Void showimg_WicaDecodeToPictureBox(int no)
	{
		if (hAP)
		{
			BOOL bResult;
			if (no == hAP->CurrentFrameID - 1)
			{
				bResult = AniPaf_DrawPrevFrame(hAP, 0);
			}
			else if (no == hAP->CurrentFrameID + 1)
			{
				bResult = AniPaf_DrawNextFrame(hAP, 0);
			}
			else if (no == 1)
			{
				bResult = AniPaf_DrawFirstFrame(hAP, 0);
			}
			hAP->CurrentFrameID = no;
			if (bResult == FALSE)
			{
				MessageBox::Show("Frame " + System::Convert::ToString(no) + " decode failed", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else
			{
				Bitmap^ bmp = gcnew Bitmap(AniPaf_GetWidth(hAP), AniPaf_GetHeight(hAP), Imaging::PixelFormat::Format32bppArgb);
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, AniPaf_GetWidth(hAP), AniPaf_GetHeight(hAP));
				System::Drawing::Imaging::BitmapData^ bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat);
				IntPtr ptr = bmpData->Scan0;
				ConvertBufferToARGB32(AniPaf_GetCurrentImage(hAP), (QUAD*)((void*)ptr), AniPaf_GetWidth(hAP), AniPaf_GetHeight(hAP), AniPaf_GetColorNum(hAP));
				bmp->UnlockBits(bmpData);
				this->decPic->Image = dynamic_cast<Image^>(bmp);
			}
		}
	}
			 /// <summary>
			 /// Show WICA image
			 /// </summary>
	private: System::Void showimg_Load(System::Object^  sender, System::EventArgs^  e) {
		showimg_WicaDecodeToPictureBox(1);
	}
			 /// <summary>
			 /// Change WICA image frame number
			 /// </summary>
	private: System::Void upDownFrames_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		showimg_WicaDecodeToPictureBox((int)upDownFrames->Value);
	}

	private: System::Void showimg_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		AniPaf_DrawPrevFrame(hAP, 0); //Go back to draw initial frame
	}
	};
}
