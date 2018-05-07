//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <dir.h>
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConvert *Convert;

//---------------------------------------------------------------------------

__fastcall TConvert::TConvert(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TConvert::SelectInputClick(TObject *Sender)
{
    if(OpenPictureDialog1->Execute()) {
        Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
        SelectOutput->Enabled = true;
        ImageSize->Caption = AnsiString(Image1->Picture->Width) + " x " +
                             AnsiString(Image1->Picture->Height) + " mils";
    }
}
//---------------------------------------------------------------------------

void __fastcall TConvert::SelectOutputClick(TObject *Sender)
{
    FILE *out;
    int x, y, x1=0, flipy, flipx;
    TColor pix;
    bool start;

    if (SaveDialog1->Execute()) {

        Screen->Cursor = crHourGlass;
        out = fopen(SaveDialog1->FileName.c_str(), "w");
        fprintf(out, "PCB FILE %d\n", 4);

        ProgressBar1->Max = Image1->Picture->Height;

        for( y = 0; y < Image1->Picture->Height; y++) {

            if(MirrorY->Checked)
                flipy = y;
            else
                flipy = abs(y - Image1->Picture->Height);

            flipy *= ScaleFactor->Text.ToInt();

            start = false;

            for( x =0; x < Image1->Picture->Width; x++) {
                pix = Image1->Canvas->Pixels[x][y];

                if(MirrorX->Checked)
                    flipx = abs(x - Image1->Picture->Height);
                else
                    flipx  = x;

                flipx *= ScaleFactor->Text.ToInt();

                if(Negative->Checked) {
                    switch (pix & 0x00ffffff) {

                        case clWhite:
                            if(!start) {
                                x1= flipx;
                                start = true;
                            }
                            break;

                        case clBlack:
                            if(start)
                                fprintf(out, "FT\n%d %d %d %d %s %s %d\n",
                                    x1, flipy, flipx, flipy,
                                    ScaleFactor->Text.c_str(),
                                    BoardLayer->Text.c_str(), 0);
                            start = false;
                            break;
                    }
                } else {
                    switch (pix & 0x00ffffff) {

                        case clBlack:
                            if(!start) {
                                x1= flipx;
                                start = true;
                            }
                            break;

                        case clWhite:
                            if(start)
                                fprintf(out, "FT\n%d %d %d %d %s %s %d\n",
                                    x1, flipy, flipx, flipy,
                                    ScaleFactor->Text.c_str(),
                                    BoardLayer->Text.c_str(), 0);
                            start = false;
                            break;
                    }
                }
            }
            if(start)
                fprintf(out, "FT\n%d %d %d %d %s %s %d\n",
                    x1, flipy, flipx, flipy,
                    ScaleFactor->Text.c_str(),
                    BoardLayer->Text.c_str(), 0);

            ProgressBar1->Position = y;
        }
        fprintf(out, "ENDPCB\n");
        fclose(out);
        Screen->Cursor = crArrow;
        ProgressBar1->Position = 0;
        SelectOutput->Enabled = false;
        StatusBar1->SimpleText = "DONE...";
        Image1->Picture= saveBitmap->Picture;
    }
}
//---------------------------------------------------------------------------


void __fastcall TConvert::ScaleFactorChange(TObject *Sender)
{
    ImageSize->Caption = AnsiString(Image1->Picture->Width *
                                    ScaleFactor->Text.ToInt())
                         + " x " +
                         AnsiString(Image1->Picture->Height *
                                    ScaleFactor->Text.ToInt())
                         + " mils";

}
//---------------------------------------------------------------------------

void __fastcall TConvert::Button1Click(TObject *Sender)
{
    Button1->Visible=false;
    Memo1->Visible=false;
    SelectOutput->Enabled = true;
    SelectInput->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TConvert::Button2Click(TObject *Sender)
{
    Button1->Visible=true;
    Memo1->Visible=true;
    SelectOutput->Enabled=false;
    SelectInput->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TConvert::FormShow(TObject *Sender)
{
    saveBitmap = new TImage(this);
    saveBitmap->Picture = Image1->Picture;
}
//---------------------------------------------------------------------------

void __fastcall TConvert::FormClose(TObject *Sender, TCloseAction &Action)
{
    delete saveBitmap;
}
//---------------------------------------------------------------------------

