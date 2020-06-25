#include "QT_Plugin.h"
#include "Form.h"

QWidget* QT_Plugin_Init()
{
    Form* form = new Form();
    return form;
}

const char* QT_Plugin_Name()
{
    return "Python Script";
}

const char* QT_Plugin_Contents()
{
    return "Script";
}
