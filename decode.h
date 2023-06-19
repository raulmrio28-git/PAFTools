#pragma once
#include <iostream>
#include "AniPAF/AniPAF.h"
#include "RgbManipulate/Main.h"
#include "showimg.h"

namespace PAFTools {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	/// <summary>
	/// Summary for decode
	/// </summary>
	public ref class decode : public System::Windows::Forms::Form
	{
		OpenFileDialog^ openFileDialog;
	public:
		decode(void)
		{
			InitializeComponent();
			openFileDialog = gcnew OpenFileDialog();
			openFileDialog->Filter = "PDK Animation Format (*.paf)|*.paf|All files(*.*)|*.*";
			openFileDialog->DefaultExt = "paf";
			openFileDialog->Title = "Select PAF file";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~decode()
		{
			//DO NOT DELETE hPAF, otherwise error occurs...
			if (hPAF)
			{
				AniPaf_Destroy(hPAF);
			}
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  getButton;
	private: TAniPaf* hPAF;
	protected:
	private: System::Windows::Forms::Button^  decodeButton;
	private: System::Windows::Forms::Label^  InfoLabel;
	private: System::Windows::Forms::Button^  fileButton;
	private: System::Windows::Forms::Button^  viewButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->getButton = (gcnew System::Windows::Forms::Button());
			this->decodeButton = (gcnew System::Windows::Forms::Button());
			this->InfoLabel = (gcnew System::Windows::Forms::Label());
			this->fileButton = (gcnew System::Windows::Forms::Button());
			this->viewButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// getButton
			// 
			this->getButton->Location = System::Drawing::Point(12, 12);
			this->getButton->Name = L"getButton";
			this->getButton->Size = System::Drawing::Size(134, 37);
			this->getButton->TabIndex = 0;
			this->getButton->Text = L"Get PAF info";
			this->getButton->UseVisualStyleBackColor = true;
			this->getButton->Click += gcnew System::EventHandler(this, &decode::getButton_Click);
			// 
			// decodeButton
			// 
			this->decodeButton->Location = System::Drawing::Point(542, 12);
			this->decodeButton->Name = L"decodeButton";
			this->decodeButton->Size = System::Drawing::Size(134, 37);
			this->decodeButton->TabIndex = 1;
			this->decodeButton->Text = L"Decode";
			this->decodeButton->UseVisualStyleBackColor = true;
			this->decodeButton->Click += gcnew System::EventHandler(this, &decode::decodeButton_Click);
			// 
			// InfoLabel
			// 
			this->InfoLabel->AutoSize = true;
			this->InfoLabel->Location = System::Drawing::Point(12, 52);
			this->InfoLabel->Name = L"InfoLabel";
			this->InfoLabel->Size = System::Drawing::Size(0, 17);
			this->InfoLabel->TabIndex = 2;
			// 
			// fileButton
			// 
			this->fileButton->Location = System::Drawing::Point(152, 12);
			this->fileButton->Name = L"fileButton";
			this->fileButton->Size = System::Drawing::Size(134, 37);
			this->fileButton->TabIndex = 3;
			this->fileButton->Text = L"Open file";
			this->fileButton->UseVisualStyleBackColor = true;
			this->fileButton->Click += gcnew System::EventHandler(this, &decode::fileButton_Click);
			// 
			// viewButton
			// 
			this->viewButton->Location = System::Drawing::Point(402, 12);
			this->viewButton->Name = L"viewButton";
			this->viewButton->Size = System::Drawing::Size(134, 37);
			this->viewButton->TabIndex = 4;
			this->viewButton->Text = L"View image";
			this->viewButton->UseVisualStyleBackColor = true;
			this->viewButton->Click += gcnew System::EventHandler(this, &decode::viewButton_Click);
			// 
			// decode
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(688, 336);
			this->Controls->Add(this->viewButton);
			this->Controls->Add(this->fileButton);
			this->Controls->Add(this->InfoLabel);
			this->Controls->Add(this->decodeButton);
			this->Controls->Add(this->getButton);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"decode";
			this->ShowIcon = false;
			this->Text = L"Decode menu";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &decode::decode_FormClosing);
			this->Load += gcnew System::EventHandler(this, &decode::decode_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/// <summary>
		/// PAF information detail
		/// </summary>
	private: System::Void getButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!hPAF) {
			this->InfoLabel->Text = "You haven't opened a file yet...\n";
			return;
		}
		this->InfoLabel->Text = "PAF Information:\n";
		this->InfoLabel->Text += "Width: " + System::Convert::ToString(AniPaf_GetWidth(hPAF)) + "\n";
		this->InfoLabel->Text += "Height: " + System::Convert::ToString(AniPaf_GetHeight(hPAF)) + "\n";
		this->InfoLabel->Text += "Frames: " + System::Convert::ToString(AniPaf_GetFrameNum(hPAF)) + "\n";
		this->InfoLabel->Text += "BPP: " + System::Convert::ToString(AniPaf_GetColorNum(hPAF)) + "\n";
	}
			 /// <summary>
			 /// Destroy WICA data on form close
			 /// </summary>
	private: System::Void decode_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		//AniPaf_Destroy(hPAF);
		Application::Exit();
	}
			 /// <summary>
			 /// Decode WICA to frames
			 /// </summary>
	private: System::Void decodeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
		saveFileDialog->Filter = "BMP files (*.bmp)|*.bmp|PNG files (*.png)|*.png|JPG files (*.jpg)|*.jpg|All files (*.*)|*.*";
		saveFileDialog->Title = "Type output name";
		if (!hPAF) {
			this->InfoLabel->Text = "You haven't opened a file yet...\n";
			return;
		}
		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			this->InfoLabel->Text = "PAF Decode:\n";
			for (int c = 0; c < AniPaf_GetFrameNum(hPAF); c++) {
				BOOL result;
				this->InfoLabel->Text += "Frame " + System::Convert::ToString(c + 1) + "->Decode: ";
				if (c == 0)
					result = AniPaf_DrawFirstFrame(hPAF, 0);
				else
					result = AniPaf_DrawNextFrame(hPAF, 0);
				if (result == FALSE)
				{
					MessageBox::Show("Frame " + System::Convert::ToString(c + 1) + " decode failed", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Error);
					this->InfoLabel->Text += "FAILED";
				}
				else
				{
					this->InfoLabel->Text += "PASSED";
					Bitmap^ bmp = gcnew Bitmap(AniPaf_GetWidth(hPAF), AniPaf_GetWidth(hPAF), Imaging::PixelFormat::Format32bppArgb);
					System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, AniPaf_GetWidth(hPAF), AniPaf_GetWidth(hPAF));
					System::Drawing::Imaging::BitmapData^ bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat);
					IntPtr ptr = bmpData->Scan0;
					int bytes = AniPaf_GetWidth(hPAF) * AniPaf_GetWidth(hPAF) * 4;
					ConvertBufferToARGB32(AniPaf_GetCurrentImage(hPAF), (QUAD*)((void*)ptr), AniPaf_GetWidth(hPAF), AniPaf_GetHeight(hPAF), AniPaf_GetColorNum(hPAF));
					bmp->UnlockBits(bmpData);
					String^ ext = System::IO::Path::GetExtension(saveFileDialog->FileName)->ToLower();
					String^ fnWithNumber = System::IO::Path::GetDirectoryName(saveFileDialog->FileName) + "\\" + System::IO::Path::GetFileNameWithoutExtension(saveFileDialog->FileName) + "-" + System::Convert::ToString(c + 1) + System::IO::Path::GetExtension(saveFileDialog->FileName)->ToLower();
					if (ext == ".bmp") {
						bmp->Save(fnWithNumber, Imaging::ImageFormat::Bmp);
					}
					else if (ext == ".png") {
						bmp->Save(fnWithNumber, Imaging::ImageFormat::Png);
					}
					else if (ext == ".jpg") {
						bmp->Save(fnWithNumber, Imaging::ImageFormat::Jpeg);
					}
					else {
						MessageBox::Show("Extension is not correct", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Error);
						this->InfoLabel->Text += "\nFailed to save image";
					}
				}
				this->InfoLabel->Text += "\n";
			}
		}
	}
			 /// <summary>
			 /// Open button action
			 /// </summary>
	private: System::Void fileButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			hPAF = (TAniPaf*)AniPaf_Create((T_CSTR)(void*)Marshal::StringToHGlobalAnsi(openFileDialog->FileName), 0, 0, 0, 0);
			this->InfoLabel->Text = "";
		}
	}
			 /// <summary>
			 /// View WICA button action
			 /// </summary>
	private: System::Void viewButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!hPAF) {
			this->InfoLabel->Text = "You haven't opened a file yet...\n";
			return;
		}
		showimg^ frmView = gcnew showimg(hPAF);
		frmView->Show();
	}
	private: System::Void decode_Load(System::Object^  sender, System::EventArgs^  e) {
	}
};
}