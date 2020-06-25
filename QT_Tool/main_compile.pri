OUT_DIR = $$PWD/../Bin

CONFIG(debug, debug|release){   #设置debug配置下编译生成文件的路径
    #TARGET = $$join(TARGET,,,d)   #为debug版本生成的文件增加d的后缀
    contains(TEMPLATE, "lib"){
        DESTDIR = $$OUT_DIR/Debug/lib        #将库放在lib文件夹下
        DLLDESTDIR = $$OUT_DIR/Debug/bin     #将动态库自动拷贝至bin目录下
    }else{
        DESTDIR = $$OUT_DIR/Debug/bin        #将应用程序放在bin目录下
    }
    OBJECTS_DIR = $$OUT_DIR/Debug/obj/$$TARGET     #将生成的对象文件放在专门的obj文件夹下
    MOC_DIR = $$OUT_DIR/Debug/moc/$$TARGET         #将QT自动生成的对象放在moc文件夹下
}else{   #设置release配置下编译生成文件的路径
    contains(TEMPLATE, "lib"){
        DESTDIR = $$OUT_DIR/Release/lib        #将库放在lib文件夹下
        DLLDESTDIR = $$OUT_DIR/Release/bin     #将动态库自动拷贝至bin目录下
    }else{
        DESTDIR = $$OUT_DIR/Release/bin        #将应用程序放在bin目录下
    }
    OBJECTS_DIR = $$OUT_DIR/Release/obj/$$TARGET   #将生成的对象文件放在专门的obj文件夹下
    MOC_DIR = $$OUT_DIR/Release/moc/$$TARGET       #将QT自动生成的对象放在moc文件夹下
}

message($$OUT_DIR)
message($$DESTDIR)
