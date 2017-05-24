// py_ext_t.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Python.h"

//
//编译说明：Release，x64
//

#define PY_OK  0
#define PY_ERROR  -1


INT __api_init(VOID)
{
	printf("api_init().\n");

	return PY_OK;
}

//零参数
static PyObject* fun_param_0(PyObject *self, PyObject *args)
{
	PyObject *ref_obj = NULL;

	if (PyArg_ParseTuple(args, "")) //no arguments
	{
		if (0 == __api_init())
		{
			ref_obj = Py_BuildValue("is", PY_OK, "success.");
		}
		else
		{
			ref_obj = Py_BuildValue("is", PY_ERROR, "failed.");
		}
	}

	return ref_obj;
}


INT __positive_num(INT n)
{
	INT ret = (n > 0) ? 0 : 1;

	return ret;
}

//1参数
static PyObject* fun_param_1(PyObject *self, PyObject *args)
{
	UINT n;
	PyObject *ref_obj = NULL;

	if (PyArg_ParseTuple(args, "i", &n)) //1 argument
	{
		if (PY_OK == __positive_num(n))
		{
			ref_obj = Py_BuildValue("is", PY_OK, "great than 0");
		}
		else
		{
			ref_obj = Py_BuildValue("is", PY_ERROR, "less or equal to 0");
		}
	}

	return ref_obj;
}


//2参数，包含1个变长数组
static PyObject* fun_param_2(PyObject *self, PyObject *args)
{
	INT i, n;
	PyObject *ref_obj = NULL;
	Py_buffer tmp;

	if (PyArg_ParseTuple(args, "iy*", &n, &tmp)) //2 argument
	{
		printf("fun_param_2():n = %d\n", n);

		for (i = 0; i < tmp.len; ++i)
		{
			printf("0x%04x ", *((CHAR *)(tmp.buf))+i);
			if (!((i+1) % 8))
			{
				printf("\n");
			}
		}
		printf("\n");

		ref_obj = Py_BuildValue("is", PY_OK, "success.");
	}

	return ref_obj;
}

//字符串参数
static PyObject* fun_param_str(PyObject *self, PyObject *args)
{
	INT n;
	PyObject *ref_obj = NULL;
	Py_buffer tmp;

	if (PyArg_ParseTuple(args, "is", &n, &tmp)) //2 argument
	{
		printf("fun_param_str():n = %d, %s\n", n, (char *)tmp.buf);

		ref_obj = Py_BuildValue("iy", PY_OK, "success."); //成功
	}
	else
	{
		ref_obj = Py_BuildValue("iy", PY_ERROR, "failed.");
	}

	return ref_obj;
}

static PyMethodDef py_ext_t_method[] = {
	{ "fun_param_0", fun_param_0, METH_VARARGS, "fun_param_0" },
	{ "fun_param_1", fun_param_1, METH_VARARGS, "fun_param_1" },
	{ "fun_param_2", fun_param_2, METH_VARARGS, "fun_param_2" },
	{ "fun_param_str", fun_param_str, METH_VARARGS, "fun_param_str" },
	{ NULL, NULL, 0, NULL } //end of table marker
};

static struct PyModuleDef py_ext_tmodule = {
	PyModuleDef_HEAD_INIT,
	"py_ext_t", //module name
	"python extending samples", //module documents
	-1, //size of per_interpreter module state
	    // -1 = in global vars
	py_ext_t_method
};

PyMODINIT_FUNC
PyInit_py_ext_t()
{
	return PyModule_Create(&py_ext_tmodule);
}





