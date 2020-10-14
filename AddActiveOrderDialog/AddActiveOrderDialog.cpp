#include <Python.h>
#include "AddActiveOrderDialog.h"
#include "ui_AddActiveOrderDialog.h"

AddActiveOrderDialog::AddActiveOrderDialog(PyObject* pAddOrderFunction, QWidget *parent)
	: QDialog(parent), pFunction(pAddOrderFunction)
{
	ui = new Ui::AddActiveOrderDialog();
	ui->setupUi(this);
}

AddActiveOrderDialog::~AddActiveOrderDialog()
{
	delete ui;
}
