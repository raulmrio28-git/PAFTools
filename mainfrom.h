#pragma once
#include "decode.h"
namespace PAFTools {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:
		mainform(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  choice;
	private: System::Windows::Forms::Button^  decodeButton;
	private: System::Windows::Forms::Button^  encodeButton;
	protected:

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
			this->choice = (gcnew System::Windows::Forms::Label());
			this->decodeButton = (gcnew System::Windows::Forms::Button());
			this->encodeButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// choice
			// 
			this->choice->AutoSize = true;
			this->choice->Location = System::Drawing::Point(12, 9);
			this->choice->Name = L"choice";
			this->choice->Size = System::Drawing::Size(278, 17);
			this->choice->TabIndex = 0;
			this->choice->Text = L"What type of WICA operation do you want\?";
			// 
			// decodeButton
			// 
			this->decodeButton->Location = System::Drawing::Point(15, 40);
			this->decodeButton->Name = L"decodeButton";
			this->decodeButton->Size = System::Drawing::Size(177, 38);
			this->decodeButton->TabIndex = 1;
			this->decodeButton->Text = L"Decode";
			this->decodeButton->UseVisualStyleBackColor = true;
			this->decodeButton->Click += gcnew System::EventHandler(this, &mainform::decodeButton_Click);
			// 
			// encodeButton
			// 
			this->encodeButton->Location = System::Drawing::Point(232, 40);
			this->encodeButton->Name = L"encodeButton";
			this->encodeButton->Size = System::Drawing::Size(177, 38);
			this->encodeButton->TabIndex = 2;
			this->encodeButton->Text = L"Encode";
			this->encodeButton->UseVisualStyleBackColor = true;
			this->encodeButton->Click += gcnew System::EventHandler(this, &mainform::encodeButton_Click);
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(421, 90);
			this->Controls->Add(this->encodeButton);
			this->Controls->Add(this->decodeButton);
			this->Controls->Add(this->choice);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"mainform";
			this->ShowIcon = false;
			this->Text = L"WICA Tools v1.0";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void decodeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		decode^ frmDecode = gcnew decode();
		frmDecode->Show();
		this->Hide();
	}
	private: System::Void encodeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show("Not implemented yet!", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	};
}
