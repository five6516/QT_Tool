#include "QT_Plugin.h"
#include "Form.h"
#pragma execution_character_set("utf-8")
QWidget* QT_Plugin_Init(InterFaceStruct* pInterFaceStruct)
{
    Form* form = new Form(pInterFaceStruct);
    return form;
}

const char* QT_Plugin_Name()
{
    return "Json格式化";
}

const char* QT_Plugin_Contents()
{
    return "Json";
}
