# QT Tool

QT制作的小工具集合，插件模式




# 简介（Overview）

QT制作的小工具集合，采用插件模式

# 编译（build）

### windwos

1. QT 5.12 和 VS2015

# 插件 （Plugin）

1. 插件目录在Plugin文件夹
2. 每个插件都是一个单独的库

目前插件列表

| 功能          | 简介                     |
| ------------- | ------------------------ |
| Python Script | 可调用自定义的Python脚本 |
| Server        | 空                       |



# python脚本插件 （Script）

1. 放置在 /Plugin/Script 文件夹中

2. 脚本调用内置包 `qt_app`，使用 `dir`查看函数 

3. 集成的Python版本为3.7.3

4. 目前包含脚本
   - hello
   - md5
   - 多个pdf合成一个.py
   - 多个pdf合成一个-缩放.py

5. QT 和python3中 slots会有冲突，需要做一些处理

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
