#define PY_SSIZE_T_CLEAN
#include <Python.h>



PyDoc_STRVAR(qd_neg_doc,
"Return a dict with negated values.\n\
\n\
C implementation.");

static PyObject*
qd_neg(PyObject* self, PyObject* m)
{
    (void)self;
    //no guard against d==NULL
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mapping");
        return NULL;
    }
    
    PyObject* result = PyDict_New();
    if(!result) {
        return NULL;
    }
    
    if(PyDict_Check(m)) { //fast dict iteration
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* updated = PyNumber_Negative(value);
            if(!updated) {
                Py_DECREF(result);
                return NULL;
            }
            if(PyDict_SetItem(result, key, updated) < 0) {
                Py_DECREF(updated);
                Py_DECREF(result);
                return NULL;
            }
            Py_DECREF(updated);
        }
        return result;
    
    } else { //general mapping
        PyObject* items = PyMapping_Items(m); //guaranteed [(k0, v0), (k1, v1), ...]: https://docs.python.org/3/c-api/mapping.html#c.PyMapping_Items
        if(!items) {
            Py_DECREF(result);
            return NULL;
        }
        Py_ssize_t len = PyList_GET_SIZE(items);
        for(Py_ssize_t i=0; i<len; ++i) {
            PyObject* pair = PyList_GET_ITEM(items, i); //no null check, no tuple check, no length check
            
            PyObject* key = PyTuple_GET_ITEM(pair, 0);
            PyObject* value = PyTuple_GET_ITEM(pair, 1);
            PyObject* updated = PyNumber_Negative(value);
            if(!updated) {
                Py_DECREF(items);
                Py_DECREF(result);
                return NULL;
            }
            if(PyDict_SetItem(result, key, updated) < 0) {
                Py_DECREF(updated);
                Py_DECREF(items);
                Py_DECREF(result);
                return NULL;
            }
            Py_DECREF(updated);
        }
        Py_DECREF(items);
    }
    
    return result;
}



PyDoc_STRVAR(quickdict_doc,
"quickdict module C implementation.");

static PyMethodDef quickdict_methods[] = {
    {"qd_neg", qd_neg, METH_O, qd_neg_doc},
    {NULL, NULL, 0, NULL} //sentinel
};

static PyModuleDef quickdictmodule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "quickdict._quickdict",
    .m_doc  = quickdict_doc,
    .m_size = 0,
    .m_methods = quickdict_methods,
    .m_slots = NULL,
    .m_traverse = NULL,
    .m_clear = NULL,
    .m_free = NULL
};

PyMODINIT_FUNC
PyInit__quickdict(void)
{
    return PyModuleDef_Init(&quickdictmodule);
}
