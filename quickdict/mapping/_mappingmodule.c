#define PY_SSIZE_T_CLEAN
#include <Python.h>



/**
 * Call directly with C function pointer and METH_O argument.
 */
static PyObject*
_qd_unary(PyObject* (*op)(PyObject*), PyObject* m)
{
    //no guard against m==NULL
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mapping");
        return NULL;
    }
    
    PyObject* result = PyDict_New();
    if(!result) {
        return NULL;
    }
    
    //fast dict iteration
    if(PyDict_Check(m)) {
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* updated = (*op)(value);
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
    }
    
    //general mapping
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
        PyObject* updated = (*op)(value);
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
    
    return result;
}

/**
 * Call directly with C function pointer and METH_O argument.
 */
static PyObject*
_qd_iunary(PyObject* (*op)(PyObject*), PyObject* m)
{
    //no guard against m==NULL
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mutable mapping");
        return NULL;
    }
    
    //fast dict iteration
    if(PyDict_Check(m)) {
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* updated = (*op)(value);
            if(!updated) {
                return NULL;
            }
            if(PyDict_SetItem(m, key, updated) < 0) {
                Py_DECREF(updated);
                return NULL;
            }
            Py_DECREF(updated);
        }
        Py_INCREF(m);
        return m;
    }
    
    //general mapping
    PyObject* items = PyMapping_Items(m); //guaranteed [(k0, v0), (k1, v1), ...]: https://docs.python.org/3/c-api/mapping.html#c.PyMapping_Items
    if(!items) {
        return NULL;
    }
    Py_ssize_t len = PyList_GET_SIZE(items);
    for(Py_ssize_t i=0; i<len; ++i) {
        PyObject* pair = PyList_GET_ITEM(items, i); //no null check, no tuple check, no length check
        
        PyObject* key = PyTuple_GET_ITEM(pair, 0);
        PyObject* value = PyTuple_GET_ITEM(pair, 1);
        PyObject* updated = (*op)(value);
        if(!updated) {
            Py_DECREF(items);
            return NULL;
        }
        if(PyObject_SetItem(m, key, updated) < 0) {
            Py_DECREF(updated);
            Py_DECREF(items);
            return NULL;
        }
        Py_DECREF(updated);
    }
    Py_DECREF(items);
    
    Py_INCREF(m);
    return m;
}


PyDoc_STRVAR(qd_pos_doc,
"Return a dict with the unary plus operator applied to the values.\n\
\n\
C implementation.");

static PyObject*
qd_pos(PyObject* self, PyObject* m)
{
    (void)self;
    return _qd_unary(&PyNumber_Positive, m);
}

PyDoc_STRVAR(qd_ipos_doc,
"Apply the unary plus operator to the values.\n\
\n\
C implementation.");

static PyObject*
qd_ipos(PyObject* self, PyObject* m)
{
    (void)self;
    return _qd_iunary(&PyNumber_Positive, m);
}


PyDoc_STRVAR(qd_neg_doc,
"Return a dict with negated values.\n\
\n\
C implementation.");

static PyObject*
qd_neg(PyObject* self, PyObject* m)
{
    (void)self;
    return _qd_unary(&PyNumber_Negative, m);
}

PyDoc_STRVAR(qd_ineg_doc,
"Negate the values.\n\
\n\
C implementation.");

static PyObject*
qd_ineg(PyObject* self, PyObject* m)
{
    (void)self;
    return _qd_iunary(&PyNumber_Negative, m);
}



PyDoc_STRVAR(doc,
"quickdict.mapping module C implementation.");

static PyMethodDef methods[] = {
    {"qd_pos",  qd_pos,  METH_O, qd_pos_doc},
    {"qd_ipos", qd_ipos, METH_O, qd_ipos_doc},
    {"qd_neg",  qd_neg,  METH_O, qd_neg_doc},
    {"qd_ineg", qd_ineg, METH_O, qd_ineg_doc},
    {NULL, NULL, 0, NULL} //sentinel
};

static PyModuleDef module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "quickdict.mapping._mapping",
    .m_doc  = doc,
    .m_size = 0,
    .m_methods = methods,
    .m_slots = NULL,
    .m_traverse = NULL,
    .m_clear = NULL,
    .m_free = NULL
};

PyMODINIT_FUNC
PyInit__mapping(void)
{
    return PyModuleDef_Init(&module);
}
