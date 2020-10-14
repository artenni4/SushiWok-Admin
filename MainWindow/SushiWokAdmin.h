#pragma once

#include <Python.h>
#include <QtWidgets/QMainWindow>
#include "ui_SushiWokAdmin.h"

class SushiWokAdmin : public QMainWindow
{
    Q_OBJECT

public:
    SushiWokAdmin(QWidget *parent = Q_NULLPTR);
    ~SushiWokAdmin();

private slots:
    void AddActiveOrder();
    void test();

private:
    PyObject *pDefaultScriptsModule;
    Ui::SushiWokAdminClass* ui;
};
