﻿#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QString>
#include <functional>

#pragma execution_character_set("utf-8")
Form::Form(InterFaceStruct* pInterFaceStruct,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_pInterFaceStruct(pInterFaceStruct)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}


