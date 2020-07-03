#  Python Script (QT_Plugin_Python)



## 简介

支持python脚本功能



## 功能

- Python脚本放置在 /Plugin/Script 文件夹中
- 脚本调用内置包 `qt_app`，使用 `dir`查看函数 

- 集成的Python版本为3.7.3

- 目前包含脚本
  - hello
  - md5
  - 多个pdf合成一个.py
  - 多个pdf合成一个-缩放.py



## 注意点

QT 和python3中 slots会有冲突，需要做一些处理

```
#undef slots //这里添加
typedef struct{
    const char* name;
    int basicsize;
    int itemsize;
    unsigned int flags;
    PyType_Slot *slots; /* terminated by slot==0. */
} PyType_Spec;
#define slots Q_SLOTS //这里添加
```



## 依赖

- [QT](http://qt-project.org)(L-GPL v3)
- [Python3](https://www.python.org/)(GPL)

