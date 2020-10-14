#include <Python.h>
#include "AddActiveOrderDialog.h"
#include "ui_AddActiveOrderDialog.h"
#include <qmessagebox.h>

AddActiveOrderDialog::AddActiveOrderDialog(PyObject* pAddOrderFunction, QWidget *parent)
	: QDialog(parent), pFunction(pAddOrderFunction)
{
	ui = new Ui::AddActiveOrderDialog();
	ui->setupUi(this);

	connect(ui->add_order_button, &QPushButton::clicked, this, &AddActiveOrderDialog::AddOrder);
}

AddActiveOrderDialog::~AddActiveOrderDialog()
{
	delete ui;
	Py_DECREF(pFunction);
}

void AddActiveOrderDialog::AddOrder()
{
	PyObject* pArgTuple, *pArgs, * pRes;

	pArgTuple = PyTuple_New(1);
	pArgs = PyTuple_New(7);
	if (pArgTuple && pArgs)
	{
		std::string ID = ui->order_id->text().toStdString();
		std::string ShopAddress = ui->shop_address->text().toStdString();
		std::string DestinationAddress = ui->destination_address->text().toStdString();
		std::string Phone = ui->phone->text().toStdString();
		std::string ReadyTime = ui->ready_time->text().toStdString();
		std::string TakeTime = ui->take_time->text().toStdString();
		std::string Description = ui->description->text().toStdString();

		PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(ID.c_str()));
		PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(ShopAddress.c_str()));
		PyTuple_SetItem(pArgs, 2, PyUnicode_FromString(DestinationAddress.c_str()));
		PyTuple_SetItem(pArgs, 3, PyUnicode_FromString(Phone.c_str()));
		PyTuple_SetItem(pArgs, 4, PyUnicode_FromString(ReadyTime.c_str()));
		PyTuple_SetItem(pArgs, 5, PyUnicode_FromString(TakeTime.c_str()));
		PyTuple_SetItem(pArgs, 6, PyUnicode_FromString(Description.c_str()));

		PyTuple_SetItem(pArgTuple, 0, pArgs);

		pRes = PyObject_CallObject(pFunction, pArgTuple);
		if (PyLong_AsLong(pRes) != 0)
		{
			QMessageBox::warning(this, "Warning", "Function add_active_order ended badly");
		}
		else
		{
			Py_DECREF(pRes);
		}
		Py_DECREF(pArgs);
	}

	AddActiveOrderDialog::close();
}

