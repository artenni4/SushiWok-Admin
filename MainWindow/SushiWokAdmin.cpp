#include <Python.h>
#include <iostream>
#include "SushiWokAdmin.h"
#include "../AddActiveOrderDialog/AddActiveOrderDialog.h"
#include <qmessagebox.h>


SushiWokAdmin::SushiWokAdmin(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SushiWokAdminClass)
{
    std::cout << "Starting Python interpreter" << std::endl;
    Py_SetProgramName((const wchar_t*)"Firebase_Connector");
    Py_Initialize();

    PyObject *pFunction, *pRes;

    pDefaultScriptsModule = PyImport_Import(PyUnicode_FromString("scripts"));
    if (pDefaultScriptsModule)
    {
        pFunction = PyObject_GetAttrString(pDefaultScriptsModule, "init_scripts");
        if (pFunction && PyCallable_Check(pFunction))
        {
            pRes = PyObject_CallObject(pFunction, NULL);
            Py_DECREF(pFunction);
            if (PyLong_AsLong(pRes) != 0)
            {
                std::cerr << "Some error occured during initialization";
                QMessageBox::warning(this, "Error", "Some error occured during initialization");
            }
            Py_DECREF(pRes);
        }
        else
        {
            std::cerr << "Initialization function 'init_scripts' not found";
            QMessageBox::critical(this, "Error", "Initialization function 'init_scripts' not found. None of Firebase interactions will work");
        }
        //pFunction = PyObject_GetAttrString(pDefaultScriptsModule, "setup_listener");
        //pRes = PyObject_CallObject(pFunction, NULL);
    }
    else
    {
        std::cerr << "Scripts modules not found";
        QMessageBox::critical(this, "Error", "Python module scripts.py not found. None of Firebase interactions will work");
    }


    ui->setupUi(this);

    connect(ui->couriers_shift_button, &QPushButton::clicked, this, &SushiWokAdmin::test);
    connect(ui->active_orders_add_button, &QPushButton::clicked, this, &SushiWokAdmin::AddActiveOrder);

    //ui->active_orders_table->setColumnCount(4);
    //ui->active_orders_table->setRowCount(12);
    //ui->active_orders_table->setItem(1, 1, new QTableWidgetItem(tr("hi")));
}

SushiWokAdmin::~SushiWokAdmin()
{
    delete ui;
    PyObject *pFunction = PyObject_GetAttrString(pDefaultScriptsModule, "close_scripts");
    if (pFunction && PyCallable_Check(pFunction))
    {
        PyObject_CallObject(pFunction, NULL);
    }
    Py_DECREF(pDefaultScriptsModule);
    Py_Finalize();
}

void SushiWokAdmin::AddActiveOrder()
{
    PyObject* pFunction = PyObject_GetAttrString(pDefaultScriptsModule, "add_active_order");
    AddActiveOrderDialog dialog(pFunction);
    dialog.setModal(true);
    dialog.exec();
}

void SushiWokAdmin::test()
{
    PyObject* pFunction,* pRes;

    if (pDefaultScriptsModule)
    {
        pFunction = PyObject_GetAttrString(pDefaultScriptsModule, "test_add");
        if (pFunction && PyCallable_Check(pFunction))
        {
            pRes = PyObject_CallObject(pFunction, NULL);
            Py_DECREF(pFunction);
            if (PyLong_AsLong(pRes) != 0)
            {
                QMessageBox::warning(this, "Warning", "Functoin test_add ended badly");
            }
            Py_DECREF(pRes);
        }
    }
}
