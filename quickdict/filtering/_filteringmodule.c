#define PY_SSIZE_T_CLEAN
#include <Python.h>



PyDoc_STRVAR(qd_filter_doc,
"Return a filtered dict with the predicate applied to the values.\n\
\n\
`p` might be\n\
\n\
- `None`: filtered by `bool(v)`,\n\
- otherwise: filtered by `p(v)`.\n\
\n\
C implementation.");

static PyObject*
qd_filter(PyObject* self, PyObject* const* args, Py_ssize_t nargs) {
    (void)self;
    if(nargs != 2) {
        PyErr_SetString(PyExc_TypeError, "expected two arguments");
        return NULL;
    }
    PyObject* p = args[0];
    PyObject* m = args[1];
    if(p!=Py_None && !PyCallable_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "p must be None or callable");
        return NULL;
    }
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mapping");
        return NULL;
    }
    
    PyObject* result = PyDict_New();
    if(!result) {
        return NULL;
    }
    
    if(p == Py_None) {
        //fast dict iteration
        if(PyDict_Check(m)) {
            Py_ssize_t pos = 0;
            PyObject* key;
            PyObject* value;
            while(PyDict_Next(m, &pos, &key, &value)) {
                int t = PyObject_IsTrue(value);
                //exception
                if(t < 0) {
                    Py_DECREF(result);
                    return NULL;
                }
                //false
                if(t == 0) {
                    continue;
                }
                //true
                if(PyDict_SetItem(result, key, value) < 0) {
                    Py_DECREF(result);
                    return NULL;
                }
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
            PyObject* item = PyList_GET_ITEM(items, i);
            PyObject* value = PyTuple_GET_ITEM(item, 1);
            int t = PyObject_IsTrue(value);
            //exception
            if(t < 0) {
                Py_DECREF(items);
                Py_DECREF(result);
                return NULL;
            }
            //false
            if(t == 0) {
                continue;
            }
            //true
            PyObject* key = PyTuple_GET_ITEM(item, 0);
            if(PyDict_SetItem(result, key, value) < 0) {
                Py_DECREF(items);
                Py_DECREF(result);
                return NULL;
            }
        }
        Py_DECREF(items);
        
        return result;
    }
    
    //p = callable
    //fast dict iteration
    if(PyDict_Check(m)) {
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* b = PyObject_CallFunctionObjArgs(p, value, NULL);
            if(!b) {
                Py_DECREF(result);
                return NULL;
            }
            int t = PyObject_IsTrue(b);
            Py_DECREF(b);
            //exception
            if(t < 0) {
                Py_DECREF(result);
                return NULL;
            }
            //false
            if(t == 0) {
                continue;
            }
            //true
            if(PyDict_SetItem(result, key, value) < 0) {
                Py_DECREF(result);
                return NULL;
            }
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
        PyObject* item = PyList_GET_ITEM(items, i);
        PyObject* value = PyTuple_GET_ITEM(item, 1);
        PyObject* b = PyObject_CallFunctionObjArgs(p, value, NULL);
        if(!b) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
        int t = PyObject_IsTrue(b);
        Py_DECREF(b);
        //exception
        if(t < 0) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
        //false
        if(t == 0) {
            continue;
        }
        //true
        PyObject* key = PyTuple_GET_ITEM(item, 0);
        if(PyDict_SetItem(result, key, value) < 0) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
    }
    Py_DECREF(items);
    return result;
}


PyDoc_STRVAR(qd_kfilter_doc,
"Return a filtered dict with the predicate applied to the keys.\n\
\n\
Filtered by `p(k)`.\n\
\n\
C implementation.");

static PyObject*
qd_kfilter(PyObject* self, PyObject* const* args, Py_ssize_t nargs) {
    (void)self;
    if(nargs != 2) {
        PyErr_SetString(PyExc_TypeError, "expected two arguments");
        return NULL;
    }
    PyObject* p = args[0];
    PyObject* m = args[1];
    if(!PyCallable_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "p must be callable");
        return NULL;
    }
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
            PyObject* b = PyObject_CallFunctionObjArgs(p, key, NULL);
            if(!b) {
                Py_DECREF(result);
                return NULL;
            }
            int t = PyObject_IsTrue(b);
            Py_DECREF(b);
            //exception
            if(t < 0) {
                Py_DECREF(result);
                return NULL;
            }
            //false
            if(t == 0) {
                continue;
            }
            //true
            if(PyDict_SetItem(result, key, value) < 0) {
                Py_DECREF(result);
                return NULL;
            }
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
        PyObject* item = PyList_GET_ITEM(items, i);
        PyObject* key = PyTuple_GET_ITEM(item, 0);
        PyObject* b = PyObject_CallFunctionObjArgs(p, key, NULL);
        if(!b) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
        int t = PyObject_IsTrue(b);
        Py_DECREF(b);
        //exception
        if(t < 0) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
        //false
        if(t == 0) {
            continue;
        }
        //true
        PyObject* value = PyTuple_GET_ITEM(item, 1);
        if(PyDict_SetItem(result, key, value) < 0) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
    }
    Py_DECREF(items);
    return result;
}


PyDoc_STRVAR(qd_kvfilter_doc,
"Return a filtered dict with the predicate applied to the items.\n\
\n\
Filtered by `p(k, v)`.\n\
\n\
C implementation.");

static PyObject*
qd_kvfilter(PyObject* self, PyObject* const* args, Py_ssize_t nargs) {
    (void)self;
    if(nargs != 2) {
        PyErr_SetString(PyExc_TypeError, "expected two arguments");
        return NULL;
    }
    PyObject* p = args[0];
    PyObject* m = args[1];
    if(!PyCallable_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "p must be callable");
        return NULL;
    }
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
            PyObject* b = PyObject_CallFunctionObjArgs(p, key, value, NULL);
            if(!b) {
                Py_DECREF(result);
                return NULL;
            }
            int t = PyObject_IsTrue(b);
            Py_DECREF(b);
            //exception
            if(t < 0) {
                Py_DECREF(result);
                return NULL;
            }
            //false
            if(t == 0) {
                continue;
            }
            //true
            if(PyDict_SetItem(result, key, value) < 0) {
                Py_DECREF(result);
                return NULL;
            }
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
        PyObject* item = PyList_GET_ITEM(items, i);
        PyObject* key = PyTuple_GET_ITEM(item, 0);
        PyObject* value = PyTuple_GET_ITEM(item, 1);
        PyObject* b = PyObject_CallFunctionObjArgs(p, key, value, NULL);
        if(!b) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
        int t = PyObject_IsTrue(b);
        Py_DECREF(b);
        //exception
        if(t < 0) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
        //false
        if(t == 0) {
            continue;
        }
        //true
        if(PyDict_SetItem(result, key, value) < 0) {
            Py_DECREF(items);
            Py_DECREF(result);
            return NULL;
        }
    }
    Py_DECREF(items);
    return result;
}


//in-place

PyDoc_STRVAR(qd_ifilter_doc,
"Filter with the predicate applied to the values.\n\
\n\
`p` might be\n\
\n\
- `None`: filtered by `bool(v)`,\n\
- otherwise: filtered by `p(v)`.\n\
\n\
C implementation.");

static PyObject*
qd_ifilter(PyObject* self, PyObject* const* args, Py_ssize_t nargs) {
    (void)self;
    if(nargs != 2) {
        PyErr_SetString(PyExc_TypeError, "expected two arguments");
        return NULL;
    }
    PyObject* p = args[0];
    PyObject* m = args[1];
    if(p!=Py_None && !PyCallable_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "p must be None or callable");
        return NULL;
    }
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mutable mapping");
        return NULL;
    }
    
    
    if(p == Py_None) {
        //fast dict iteration
        if(PyDict_Check(m)) {
            PyObject* to_delete = PyList_New(0);
            if(!to_delete) {
                return NULL;
            }
            
            Py_ssize_t pos = 0;
            PyObject* key;
            PyObject* value;
            while(PyDict_Next(m, &pos, &key, &value)) {
                int t = PyObject_IsTrue(value);
                //exception
                if(t < 0) {
                    Py_DECREF(to_delete);
                    return NULL;
                }
                //true
                if(t != 0) {
                    continue;
                }
                //false
                if(PyList_Append(to_delete, key) < 0) {
                    Py_DECREF(to_delete);
                    return NULL;
                }
            }
            
            Py_ssize_t len = PyList_GET_SIZE(to_delete);
            for(Py_ssize_t i=0; i<len; ++i) {
                if(PyDict_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
                    Py_DECREF(to_delete);
                    return NULL;
                }
            }
            Py_DECREF(to_delete);
            
            Py_INCREF(m);
            return m;
        }
        
        //general mapping
        PyObject* items = PyMapping_Items(m); //guaranteed [(k0, v0), (k1, v1), ...]: https://docs.python.org/3/c-api/mapping.html#c.PyMapping_Items
        if(!items) {
            return NULL;
        }
        
        PyObject* to_delete = PyList_New(0);
        if(!to_delete) {
            Py_DECREF(items);
            return NULL;
        }
        
        Py_ssize_t len = PyList_GET_SIZE(items);
        for(Py_ssize_t i=0; i<len; ++i) {
            PyObject* item  = PyList_GET_ITEM(items, i); //no null check, no tuple check, no length check
            PyObject* value = PyTuple_GET_ITEM(item, 1);
            int t = PyObject_IsTrue(value);
            //exception
            if(t < 0) {
                Py_DECREF(to_delete);
                Py_DECREF(items);
                return NULL;
            }
            //true
            if(t != 0) {
                continue;
            }
            //false
            PyObject* key = PyTuple_GET_ITEM(item, 0);
            if(PyList_Append(to_delete, key) < 0) {
                Py_DECREF(to_delete);
                Py_DECREF(items);
                return NULL;
            }
        }
        Py_DECREF(items);
        
        Py_ssize_t del_len = PyList_GET_SIZE(to_delete);
        for(Py_ssize_t i=0; i<del_len; ++i) {
            if(PyObject_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        Py_DECREF(to_delete);
        
        Py_INCREF(m);
        return m;
    }
    
    
    //p = callable
    //fast dict iteration
    if(PyDict_Check(m)) {
        PyObject* to_delete = PyList_New(0);
        if(!to_delete) {
            return NULL;
        }
        
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* b = PyObject_CallFunctionObjArgs(p, value, NULL);
            if(!b) {
                Py_DECREF(to_delete);
                return NULL;
            }
            int t = PyObject_IsTrue(b);
            Py_DECREF(b);
            //exception
            if(t < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
            //true
            if(t != 0) {
                continue;
            }
            //false
            if(PyList_Append(to_delete, key) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        
        Py_ssize_t len = PyList_GET_SIZE(to_delete);
        for(Py_ssize_t i=0; i<len; ++i) {
            if(PyDict_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        Py_DECREF(to_delete);
        
        Py_INCREF(m);
        return m;
    }
    
    //general mapping
    PyObject* items = PyMapping_Items(m); //guaranteed [(k0, v0), (k1, v1), ...]: https://docs.python.org/3/c-api/mapping.html#c.PyMapping_Items
    if(!items) {
        return NULL;
    }
    
    PyObject* to_delete = PyList_New(0);
    if(!to_delete) {
        Py_DECREF(items);
        return NULL;
    }
    
    Py_ssize_t len = PyList_GET_SIZE(items);
    for(Py_ssize_t i=0; i<len; ++i) {
        PyObject* item  = PyList_GET_ITEM(items, i); //no null check, no tuple check, no length check
        PyObject* value = PyTuple_GET_ITEM(item, 1);
        PyObject* b = PyObject_CallFunctionObjArgs(p, value, NULL);
        if(!b) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
        int t = PyObject_IsTrue(b);
        Py_DECREF(b);
        //exception
        if(t < 0) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
        //true
        if(t != 0) {
            continue;
        }
        //false
        PyObject* key = PyTuple_GET_ITEM(item, 0);
        if(PyList_Append(to_delete, key) < 0) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
    }
    Py_DECREF(items);
    
    Py_ssize_t del_len = PyList_GET_SIZE(to_delete);
    for(Py_ssize_t i=0; i<del_len; ++i) {
        if(PyObject_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
            Py_DECREF(to_delete);
            return NULL;
        }
    }
    Py_DECREF(to_delete);
    
    Py_INCREF(m);
    return m;
}


PyDoc_STRVAR(qd_ikfilter_doc,
"Filter a mapping with the predicate applied to the keys.\n\
\n\
Filtered by `p(k)`.\n\
\n\
C implementation.");

static PyObject*
qd_ikfilter(PyObject* self, PyObject* const* args, Py_ssize_t nargs) {
    (void)self;
    if(nargs != 2) {
        PyErr_SetString(PyExc_TypeError, "expected two arguments");
        return NULL;
    }
    PyObject* p = args[0];
    PyObject* m = args[1];
    if(!PyCallable_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "p must be callable");
        return NULL;
    }
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mutable mapping");
        return NULL;
    }

    //fast dict iteration
    if(PyDict_Check(m)) {
        PyObject* to_delete = PyList_New(0);
        if(!to_delete) {
            return NULL;
        }
        
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* b = PyObject_CallFunctionObjArgs(p, key, NULL);
            if(!b) {
                Py_DECREF(to_delete);
                return NULL;
            }
            int t = PyObject_IsTrue(b);
            Py_DECREF(b);
            //exception
            if(t < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
            //true
            if(t != 0) {
                continue;
            }
            //false
            if(PyList_Append(to_delete, key) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        
        Py_ssize_t len = PyList_GET_SIZE(to_delete);
        for(Py_ssize_t i=0; i<len; ++i) {
            if(PyDict_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        Py_DECREF(to_delete);
        
        Py_INCREF(m);
        return m;
    }
    
    //general mapping
    PyObject* items = PyMapping_Items(m); //guaranteed [(k0, v0), (k1, v1), ...]: https://docs.python.org/3/c-api/mapping.html#c.PyMapping_Items
    if(!items) {
        return NULL;
    }
    
    PyObject* to_delete = PyList_New(0);
    if(!to_delete) {
        Py_DECREF(items);
        return NULL;
    }
    
    Py_ssize_t len = PyList_GET_SIZE(items);
    for(Py_ssize_t i=0; i<len; ++i) {
        PyObject* item  = PyList_GET_ITEM(items, i); //no null check, no tuple check, no length check
        PyObject* key = PyTuple_GET_ITEM(item, 0);
        PyObject* b = PyObject_CallFunctionObjArgs(p, key, NULL);
        if(!b) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
        int t = PyObject_IsTrue(b);
        Py_DECREF(b);
        //exception
        if(t < 0) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
        //true
        if(t != 0) {
            continue;
        }
        //false
        if(PyList_Append(to_delete, key) < 0) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
    }
    Py_DECREF(items);
    
    Py_ssize_t del_len = PyList_GET_SIZE(to_delete);
    for(Py_ssize_t i=0; i<del_len; ++i) {
        if(PyObject_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
            Py_DECREF(to_delete);
            return NULL;
        }
    }
    Py_DECREF(to_delete);
    
    Py_INCREF(m);
    return m;
}


PyDoc_STRVAR(qd_ikvfilter_doc,
"Filter a mapping with the predicate applied to the items.\n\
\n\
Filtered by `p(k, v)`.\n\
\n\
C implementation.");

static PyObject*
qd_ikvfilter(PyObject* self, PyObject* const* args, Py_ssize_t nargs) {
    (void)self;
    if(nargs != 2) {
        PyErr_SetString(PyExc_TypeError, "expected two arguments");
        return NULL;
    }
    PyObject* p = args[0];
    PyObject* m = args[1];
    if(!PyCallable_Check(p)) {
        PyErr_SetString(PyExc_TypeError, "p must be callable");
        return NULL;
    }
    if(!PyMapping_Check(m)) {
        PyErr_SetString(PyExc_TypeError, "m must be a mutable mapping");
        return NULL;
    }
    
    //fast dict iteration
    if(PyDict_Check(m)) {
        PyObject* to_delete = PyList_New(0);
        if(!to_delete) {
            return NULL;
        }
        
        Py_ssize_t pos = 0;
        PyObject* key;
        PyObject* value;
        while(PyDict_Next(m, &pos, &key, &value)) {
            PyObject* b = PyObject_CallFunctionObjArgs(p, key, value, NULL);
            if(!b) {
                Py_DECREF(to_delete);
                return NULL;
            }
            int t = PyObject_IsTrue(b);
            Py_DECREF(b);
            //exception
            if(t < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
            //true
            if(t != 0) {
                continue;
            }
            //false
            if(PyList_Append(to_delete, key) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        
        Py_ssize_t len = PyList_GET_SIZE(to_delete);
        for(Py_ssize_t i=0; i<len; ++i) {
            if(PyDict_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
                Py_DECREF(to_delete);
                return NULL;
            }
        }
        Py_DECREF(to_delete);
        
        Py_INCREF(m);
        return m;
    }
    
    //general mapping
    PyObject* items = PyMapping_Items(m); //guaranteed [(k0, v0), (k1, v1), ...]: https://docs.python.org/3/c-api/mapping.html#c.PyMapping_Items
    if(!items) {
        return NULL;
    }
    
    PyObject* to_delete = PyList_New(0);
    if(!to_delete) {
        Py_DECREF(items);
        return NULL;
    }
    
    Py_ssize_t len = PyList_GET_SIZE(items);
    for(Py_ssize_t i=0; i<len; ++i) {
        PyObject* item  = PyList_GET_ITEM(items, i); //no null check, no tuple check, no length check
        PyObject* key = PyTuple_GET_ITEM(item, 0);
        PyObject* value = PyTuple_GET_ITEM(item, 1);
        PyObject* b = PyObject_CallFunctionObjArgs(p, key, value, NULL);
        if(!b) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
        int t = PyObject_IsTrue(b);
        Py_DECREF(b);
        //exception
        if(t < 0) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
        //true
        if(t != 0) {
            continue;
        }
        //false
        if(PyList_Append(to_delete, key) < 0) {
            Py_DECREF(to_delete);
            Py_DECREF(items);
            return NULL;
        }
    }
    Py_DECREF(items);
    
    Py_ssize_t del_len = PyList_GET_SIZE(to_delete);
    for(Py_ssize_t i=0; i<del_len; ++i) {
        if(PyObject_DelItem(m, PyList_GET_ITEM(to_delete, i)) < 0) {
            Py_DECREF(to_delete);
            return NULL;
        }
    }
    Py_DECREF(to_delete);
    
    Py_INCREF(m);
    return m;
}



PyDoc_STRVAR(doc,
"quickdict.filtering module C implementation.");

static PyMethodDef methods[] = {
    {"qd_filter",    qd_filter,    METH_FASTCALL, qd_filter_doc},
    {"qd_kfilter",   qd_kfilter,   METH_FASTCALL, qd_kfilter_doc},
    {"qd_kvfilter",  qd_kvfilter,  METH_FASTCALL, qd_kvfilter_doc},
    {"qd_ifilter",   qd_ifilter,   METH_FASTCALL, qd_ifilter_doc},
    {"qd_ikfilter",  qd_ikfilter,  METH_FASTCALL, qd_ikfilter_doc},
    {"qd_ikvfilter", qd_ikvfilter, METH_FASTCALL, qd_ikvfilter_doc},
    {NULL, NULL, 0, NULL} //sentinel
};

static PyModuleDef module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "quickdict.filtering._filtering",
    .m_doc  = doc,
    .m_size = 0,
    .m_methods = methods,
    .m_slots = NULL,
    .m_traverse = NULL,
    .m_clear = NULL,
    .m_free = NULL
};

PyMODINIT_FUNC
PyInit__filtering(void)
{
    return PyModuleDef_Init(&module);
}
