//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TConvert : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel2;
    TImage *Image1;
    TOpenPictureDialog *OpenPictureDialog1;
    TSaveDialog *SaveDialog1;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label7;
    TEdit *BoardLayer;
    TButton *SelectInput;
    TButton *SelectOutput;
    TUpDown *UpDown1;
    TProgressBar *ProgressBar1;
    TLabel *Label6;
    TLabel *Label8;
    TLabel *Label9;
    TBevel *Bevel1;
    TUpDown *UpDown2;
    TEdit *ScaleFactor;
    TLabel *Label10;
    TCheckBox *Negative;
    TCheckBox *MirrorX;
    TCheckBox *MirrorY;
    TStatusBar *StatusBar1;
    TLabel *Label11;
    TLabel *ImageSize;
    TBevel *Bevel2;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label12;
    TMemo *Memo1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall SelectInputClick(TObject *Sender);
    void __fastcall SelectOutputClick(TObject *Sender);
    
    void __fastcall ScaleFactorChange(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    TImage *saveBitmap;
public:		// User declarations
    __fastcall TConvert(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConvert *Convert;
//---------------------------------------------------------------------------
#endif
