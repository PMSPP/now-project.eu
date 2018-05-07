//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BMPtoPCB.res");
USEFORM("main.cpp", Convert);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TConvert), &Convert);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
