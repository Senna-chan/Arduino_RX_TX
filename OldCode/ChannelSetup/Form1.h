#pragma once

// uncomment to execute the rk1-utils:
//    #include "rk1_Utils_demo.h"  // shows how the rk1-utils can be used

#include "Header1.h"
#include "Header2.h"
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <cliext/map>

namespace CppCLRWinFormsProject {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace cliext;
  /// <summary>
  /// Summary for Form1
  /// </summary>
  public ref class Form1 : public System::Windows::Forms::Form
  {
  protected:
      map<int, System::Windows::Forms::TabPage^>^ channelPages = (gcnew map<int, System::Windows::Forms::TabPage^>);

  public:
    Form1(void)
    {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //

      // uncomment to execute the rk1-utils:
      //    N_rk1_Utils_demo::execute(); // shows how the rk1-utils can be used
      channelPages->insert(cliext::make_pair(1, tpCH1));
      channelPages->insert(cliext::make_pair(2, tpCH2));
      channelPages->insert(cliext::make_pair(3, tpCH3));
      channelPages->insert(cliext::make_pair(4, tpCH4));
      channelPages->insert(cliext::make_pair(5, tpCH5));
      channelPages->insert(cliext::make_pair(6, tpCH6));
      channelPages->insert(cliext::make_pair(7, tpCH7));
      channelPages->insert(cliext::make_pair(8, tpCH8));
      channelPages->insert(cliext::make_pair(9, tpCH9));
      channelPages->insert(cliext::make_pair(10, tpCH10));
      channelPages->insert(cliext::make_pair(11, tpCH11));
      channelPages->insert(cliext::make_pair(12, tpCH12));
      channelPages->insert(cliext::make_pair(13, tpCH13));
      channelPages->insert(cliext::make_pair(14, tpCH14));
      channelPages->insert(cliext::make_pair(15, tpCH15));
      channelPages->insert(cliext::make_pair(16, tpCH16));
      channelPages->insert(cliext::make_pair(17, tpCH17));
      channelPages->insert(cliext::make_pair(18, tpCH18));
      channelPages->insert(cliext::make_pair(19, tpCH19));
      channelPages->insert(cliext::make_pair(20, tpCH20));
      channelPages->insert(cliext::make_pair(21, tpCH21));
      channelPages->insert(cliext::make_pair(22, tpCH22));
      channelPages->insert(cliext::make_pair(23, tpCH23));
      channelPages->insert(cliext::make_pair(24, tpCH24));
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }
  private:
      int selectedChannel;

      System::Windows::Forms::TabControl^ tabControl1;
      System::Windows::Forms::TabPage^ tpCH1 ;
      System::Windows::Forms::TabPage^ tpCH2 ;
      System::Windows::Forms::TabPage^ tpCH3 ;
      System::Windows::Forms::TabPage^ tpCH4 ;
      System::Windows::Forms::TabPage^ tpCH5 ;
      System::Windows::Forms::TabPage^ tpCH6 ;
      System::Windows::Forms::TabPage^ tpCH7 ;
      System::Windows::Forms::TabPage^ tpCH8 ;
      System::Windows::Forms::TabPage^ tpCH9 ;
      System::Windows::Forms::TabPage^ tpCH10;
      System::Windows::Forms::TabPage^ tpCH11;
      System::Windows::Forms::TabPage^ tpCH12;
      System::Windows::Forms::TabPage^ tpCH13;
      System::Windows::Forms::TabPage^ tpCH14;
      System::Windows::Forms::TabPage^ tpCH15;
      System::Windows::Forms::TabPage^ tpCH16;
      System::Windows::Forms::TabPage^ tpCH17;
      System::Windows::Forms::TabPage^ tpCH18;
      System::Windows::Forms::TabPage^ tpCH19;
      System::Windows::Forms::TabPage^ tpCH20;
      System::Windows::Forms::TabPage^ tpCH21;
      System::Windows::Forms::TabPage^ tpCH22;
      System::Windows::Forms::TabPage^ tpCH23;
      System::Windows::Forms::TabPage^ tpCH24;


  protected:








  protected:

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
        this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
        this->tpCH1 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH2 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH3 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH4 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH5 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH6 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH7 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH8 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH9 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH10 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH11 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH12 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH13 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH14 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH15 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH16 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH17 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH18 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH19 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH20 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH21 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH22 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH23 = (gcnew System::Windows::Forms::TabPage());
        this->tpCH24 = (gcnew System::Windows::Forms::TabPage());
        this->tabControl1->SuspendLayout();
        this->SuspendLayout();
        // 
        // tabControl1
        // 
        this->tabControl1->Controls->Add(this->tpCH1);
        this->tabControl1->Controls->Add(this->tpCH2);
        this->tabControl1->Controls->Add(this->tpCH3);
        this->tabControl1->Controls->Add(this->tpCH4);
        this->tabControl1->Controls->Add(this->tpCH5);
        this->tabControl1->Controls->Add(this->tpCH6);
        this->tabControl1->Controls->Add(this->tpCH7);
        this->tabControl1->Controls->Add(this->tpCH8);
        this->tabControl1->Controls->Add(this->tpCH9);
        this->tabControl1->Controls->Add(this->tpCH10);
        this->tabControl1->Controls->Add(this->tpCH11);
        this->tabControl1->Controls->Add(this->tpCH12);
        this->tabControl1->Controls->Add(this->tpCH13);
        this->tabControl1->Controls->Add(this->tpCH14);
        this->tabControl1->Controls->Add(this->tpCH15);
        this->tabControl1->Controls->Add(this->tpCH16);
        this->tabControl1->Controls->Add(this->tpCH17);
        this->tabControl1->Controls->Add(this->tpCH18);
        this->tabControl1->Controls->Add(this->tpCH19);
        this->tabControl1->Controls->Add(this->tpCH20);
        this->tabControl1->Controls->Add(this->tpCH21);
        this->tabControl1->Controls->Add(this->tpCH22);
        this->tabControl1->Controls->Add(this->tpCH23);
        this->tabControl1->Controls->Add(this->tpCH24);
        this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
        this->tabControl1->Location = System::Drawing::Point(0, 0);
        this->tabControl1->Name = L"tabControl1";
        this->tabControl1->SelectedIndex = 0;
        this->tabControl1->Size = System::Drawing::Size(961, 401);
        this->tabControl1->TabIndex = 0;
        this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::tabControl1_SelectedIndexChanged);
        // 
        // tpCH1
        // 
        this->tpCH1->Location = System::Drawing::Point(4, 22);
        this->tpCH1->Name = L"tpCH1";
        this->tpCH1->Size = System::Drawing::Size(953, 375);
        this->tpCH1->TabIndex = 0;
        this->tpCH1->Text = L"CH1";
        this->tpCH1->UseVisualStyleBackColor = true;
        // 
        // tpCH2
        // 
        this->tpCH2->Location = System::Drawing::Point(4, 22);
        this->tpCH2->Name = L"tpCH2";
        this->tpCH2->Size = System::Drawing::Size(276, 235);
        this->tpCH2->TabIndex = 0;
        this->tpCH2->Text = L"CH2";
        this->tpCH2->UseVisualStyleBackColor = true;
        // 
        // tpCH3
        // 
        this->tpCH3->Location = System::Drawing::Point(4, 22);
        this->tpCH3->Name = L"tpCH3";
        this->tpCH3->Size = System::Drawing::Size(276, 235);
        this->tpCH3->TabIndex = 0;
        this->tpCH3->Text = L"CH3";
        this->tpCH3->UseVisualStyleBackColor = true;
        // 
        // tpCH4
        // 
        this->tpCH4->Location = System::Drawing::Point(4, 22);
        this->tpCH4->Name = L"tpCH4";
        this->tpCH4->Size = System::Drawing::Size(276, 235);
        this->tpCH4->TabIndex = 0;
        this->tpCH4->Text = L"CH4";
        this->tpCH4->UseVisualStyleBackColor = true;
        // 
        // tpCH5
        // 
        this->tpCH5->Location = System::Drawing::Point(4, 22);
        this->tpCH5->Name = L"tpCH5";
        this->tpCH5->Size = System::Drawing::Size(276, 235);
        this->tpCH5->TabIndex = 0;
        this->tpCH5->Text = L"CH5";
        this->tpCH5->UseVisualStyleBackColor = true;
        // 
        // tpCH6
        // 
        this->tpCH6->Location = System::Drawing::Point(4, 22);
        this->tpCH6->Name = L"tpCH6";
        this->tpCH6->Size = System::Drawing::Size(276, 235);
        this->tpCH6->TabIndex = 0;
        this->tpCH6->Text = L"CH6";
        this->tpCH6->UseVisualStyleBackColor = true;
        // 
        // tpCH7
        // 
        this->tpCH7->Location = System::Drawing::Point(4, 22);
        this->tpCH7->Name = L"tpCH7";
        this->tpCH7->Size = System::Drawing::Size(276, 235);
        this->tpCH7->TabIndex = 0;
        this->tpCH7->Text = L"CH7";
        this->tpCH7->UseVisualStyleBackColor = true;
        // 
        // tpCH8
        // 
        this->tpCH8->Location = System::Drawing::Point(4, 22);
        this->tpCH8->Name = L"tpCH8";
        this->tpCH8->Size = System::Drawing::Size(276, 235);
        this->tpCH8->TabIndex = 0;
        this->tpCH8->Text = L"CH8";
        this->tpCH8->UseVisualStyleBackColor = true;
        // 
        // tpCH9
        // 
        this->tpCH9->Location = System::Drawing::Point(4, 22);
        this->tpCH9->Name = L"tpCH9";
        this->tpCH9->Size = System::Drawing::Size(276, 235);
        this->tpCH9->TabIndex = 0;
        this->tpCH9->Text = L"CH9";
        this->tpCH9->UseVisualStyleBackColor = true;
        // 
        // tpCH10
        // 
        this->tpCH10->Location = System::Drawing::Point(4, 22);
        this->tpCH10->Name = L"tpCH10";
        this->tpCH10->Size = System::Drawing::Size(276, 235);
        this->tpCH10->TabIndex = 1;
        this->tpCH10->Text = L"CH10";
        // 
        // tpCH11
        // 
        this->tpCH11->Location = System::Drawing::Point(4, 22);
        this->tpCH11->Name = L"tpCH11";
        this->tpCH11->Size = System::Drawing::Size(276, 235);
        this->tpCH11->TabIndex = 2;
        this->tpCH11->Text = L"CH11";
        // 
        // tpCH12
        // 
        this->tpCH12->Location = System::Drawing::Point(4, 22);
        this->tpCH12->Name = L"tpCH12";
        this->tpCH12->Size = System::Drawing::Size(276, 235);
        this->tpCH12->TabIndex = 3;
        this->tpCH12->Text = L"CH12";
        // 
        // tpCH13
        // 
        this->tpCH13->Location = System::Drawing::Point(4, 22);
        this->tpCH13->Name = L"tpCH13";
        this->tpCH13->Size = System::Drawing::Size(276, 235);
        this->tpCH13->TabIndex = 4;
        this->tpCH13->Text = L"CH13";
        // 
        // tpCH14
        // 
        this->tpCH14->Location = System::Drawing::Point(4, 22);
        this->tpCH14->Name = L"tpCH14";
        this->tpCH14->Size = System::Drawing::Size(276, 235);
        this->tpCH14->TabIndex = 5;
        this->tpCH14->Text = L"CH14";
        // 
        // tpCH15
        // 
        this->tpCH15->Location = System::Drawing::Point(4, 22);
        this->tpCH15->Name = L"tpCH15";
        this->tpCH15->Size = System::Drawing::Size(276, 235);
        this->tpCH15->TabIndex = 6;
        this->tpCH15->Text = L"CH15";
        // 
        // tpCH16
        // 
        this->tpCH16->Location = System::Drawing::Point(4, 22);
        this->tpCH16->Name = L"tpCH16";
        this->tpCH16->Size = System::Drawing::Size(276, 235);
        this->tpCH16->TabIndex = 7;
        this->tpCH16->Text = L"CH16";
        // 
        // tpCH17
        // 
        this->tpCH17->Location = System::Drawing::Point(4, 22);
        this->tpCH17->Name = L"tpCH17";
        this->tpCH17->Size = System::Drawing::Size(276, 235);
        this->tpCH17->TabIndex = 8;
        this->tpCH17->Text = L"CH17";
        // 
        // tpCH18
        // 
        this->tpCH18->Location = System::Drawing::Point(4, 22);
        this->tpCH18->Name = L"tpCH18";
        this->tpCH18->Size = System::Drawing::Size(276, 235);
        this->tpCH18->TabIndex = 9;
        this->tpCH18->Text = L"CH18";
        // 
        // tpCH19
        // 
        this->tpCH19->Location = System::Drawing::Point(4, 22);
        this->tpCH19->Name = L"tpCH19";
        this->tpCH19->Size = System::Drawing::Size(276, 235);
        this->tpCH19->TabIndex = 10;
        this->tpCH19->Text = L"CH19";
        // 
        // tpCH20
        // 
        this->tpCH20->Location = System::Drawing::Point(4, 22);
        this->tpCH20->Name = L"tpCH20";
        this->tpCH20->Size = System::Drawing::Size(276, 235);
        this->tpCH20->TabIndex = 11;
        this->tpCH20->Text = L"CH20";
        // 
        // tpCH21
        // 
        this->tpCH21->Location = System::Drawing::Point(4, 22);
        this->tpCH21->Name = L"tpCH21";
        this->tpCH21->Size = System::Drawing::Size(276, 235);
        this->tpCH21->TabIndex = 12;
        this->tpCH21->Text = L"CH21";
        // 
        // tpCH22
        // 
        this->tpCH22->Location = System::Drawing::Point(4, 22);
        this->tpCH22->Name = L"tpCH22";
        this->tpCH22->Size = System::Drawing::Size(276, 235);
        this->tpCH22->TabIndex = 13;
        this->tpCH22->Text = L"CH22";
        // 
        // tpCH23
        // 
        this->tpCH23->Location = System::Drawing::Point(4, 22);
        this->tpCH23->Name = L"tpCH23";
        this->tpCH23->Size = System::Drawing::Size(276, 235);
        this->tpCH23->TabIndex = 14;
        this->tpCH23->Text = L"CH23";
        // 
        // tpCH24
        // 
        this->tpCH24->Location = System::Drawing::Point(4, 22);
        this->tpCH24->Name = L"tpCH24";
        this->tpCH24->Size = System::Drawing::Size(276, 235);
        this->tpCH24->TabIndex = 15;
        this->tpCH24->Text = L"CH24";
        // 
        // Form1
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(961, 401);
        this->Controls->Add(this->tabControl1);
        this->Name = L"Form1";
        this->Text = L"Form1";
        this->tabControl1->ResumeLayout(false);
        this->ResumeLayout(false);

    }
#pragma endregion

   // You can call the functions at a button click. If you prefer, 
    // you can call them by clicking a menu item.

  private: System::Void tabControl1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
      selectedChannel = this->tabControl1->SelectedIndex + 1;
      std::cout << "Selected Channel is " << selectedChannel;
  }
}; // end of class Form1
} // end of namespace CppCLRWinFormsProject

