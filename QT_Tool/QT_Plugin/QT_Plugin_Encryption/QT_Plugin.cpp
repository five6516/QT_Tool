#include "QT_Plugin.h"
#include "Form.h"

QWidget* QT_Plugin_Init(InterFaceStruct* pInterFaceStruct)
{
    Form* form = new Form(pInterFaceStruct);
    return form;
}

const char* QT_Plugin_Name()
{
    return "Encryption";
}

const char* QT_Plugin_Contents()
{
    return "Encryption";
}
