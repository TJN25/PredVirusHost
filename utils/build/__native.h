#ifndef MYPYC_NATIVE_H
#define MYPYC_NATIVE_H
#include <Python.h>
#include <CPy.h>
#ifndef MYPYC_DECLARED_tuple_T3IOO
#define MYPYC_DECLARED_tuple_T3IOO
typedef struct tuple_T3IOO {
    CPyTagged f0;
    PyObject *f1;
    PyObject *f2;
} tuple_T3IOO;
#endif

#ifndef MYPYC_DECLARED_tuple_T3OOO
#define MYPYC_DECLARED_tuple_T3OOO
typedef struct tuple_T3OOO {
    PyObject *f0;
    PyObject *f1;
    PyObject *f2;
} tuple_T3OOO;
#endif

#ifndef MYPYC_DECLARED_tuple_T2OO
#define MYPYC_DECLARED_tuple_T2OO
typedef struct tuple_T2OO {
    PyObject *f0;
    PyObject *f1;
} tuple_T2OO;
#endif

#ifndef MYPYC_DECLARED_tuple_T5OIIIO
#define MYPYC_DECLARED_tuple_T5OIIIO
typedef struct tuple_T5OIIIO {
    PyObject *f0;
    CPyTagged f1;
    CPyTagged f2;
    CPyTagged f3;
    PyObject *f4;
} tuple_T5OIIIO;
#endif

#endif
