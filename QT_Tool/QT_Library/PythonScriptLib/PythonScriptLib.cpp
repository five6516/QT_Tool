#include "PythonScriptLib.h"
#include "PythonScriptLib_global.h"
#include <Python.h>
#include <string>

Python_Param param;
bool showLog(QString data, int R,int G,int B,int Size)
{
    return param.pShowLog("Py:" + data,R,G,B,Size);
}

///**********************注册函数************************/
static PyObject *SpamError;

static PyObject *
addstring(PyObject *self, PyObject *args)
{
    const char *command;
    int R=0;
    int G=0;
    int B=0;
    int Size=0;
    if (!PyArg_ParseTuple(args, "siiii", &command,&R,&G,&B,&Size))
        return NULL;

    showLog(QString().asprintf("%s",command),R,G,B,Size);

    return Py_None;
}

static PyObject *
get_appdirpath(PyObject *self, PyObject *args)
{
    return PyUnicode_FromUnicode((const Py_UNICODE*)param.strAppPath.toStdWString().c_str(), param.strAppPath.toStdWString().size());;
}

static PyMethodDef AppMethods[] = {

    {"addstring",  addstring, METH_VARARGS,
     "addstring"},
    {"get_appdirpath",  get_appdirpath, METH_VARARGS,
     "get_appdirpath"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef appmodule = {
    PyModuleDef_HEAD_INIT,
    "qt_app",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    AppMethods
};

//PyMODINIT_FUNC
static PyObject*
PyInit_spam(void)
{
    return PyModule_Create(&appmodule);
}

int PythonScript_Run(Python_Param* Python_Param,QString moduleName,QString functionName,QString strInput1,QString strInput2,QString& strOutput)
{
    param.strAppPath = Python_Param->strAppPath;
    param.pShowLog = Python_Param->pShowLog;


    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("qt_app", PyInit_spam);
    Py_Initialize();//初始化
    if(!Py_IsInitialized())
    {
        showLog("Python init fail",255,0,0,0);
        return -1;
    }
    //设置加载路径
    std::string path = "Plugin\\Script";
    std::string chdir_cmd = std::string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
    pName = PyUnicode_DecodeFSDefault(moduleName.toStdString().c_str()); //py脚本路径
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule,functionName.toStdString().c_str());//加载函数

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);//设置参数个数
            pValue = PyUnicode_FromUnicode((const Py_UNICODE*)strInput1.toStdWString().c_str(), strInput1.toStdWString().size());
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                showLog("Cannot convert argument",255,0,0,0);
                return 1;
            }
            PyTuple_SetItem(pArgs, 0, pValue);//设置参数
            pValue = PyUnicode_FromUnicode((const Py_UNICODE*)strInput2.toStdWString().c_str(), strInput2.toStdWString().size());
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                showLog("Cannot convert argument",255,0,0,0);
                return 1;
            }
            PyTuple_SetItem(pArgs, 1, pValue);//设置参数

            pValue = PyObject_CallObject(pFunc, pArgs);//调用函数
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                char* t;
                int error = PyArg_Parse(pValue, "s", &t);
                strOutput = QString().asprintf("%s",t);
                Py_DECREF(pValue);
                if(!error)
                {
                    showLog("PyArg_Parse failed",255,0,0,0);
                    return 1;
                }
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                showLog("Call failed",255,0,0,0);
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            showLog("Cannot find function",255,0,0,0);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        showLog("Failed to load",255,0,0,0);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {//释放
        return 120;
    }
    return 0;
}
