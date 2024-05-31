#include "init.c"
#include "getargs.c"
#include "getargsfast.c"
#include "int_ops.c"
#include "float_ops.c"
#include "str_ops.c"
#include "bytes_ops.c"
#include "list_ops.c"
#include "dict_ops.c"
#include "set_ops.c"
#include "tuple_ops.c"
#include "exc_ops.c"
#include "misc_ops.c"
#include "generic_ops.c"
#include "__native.h"
#include "__native_internal.h"
static PyMethodDef module_methods[] = {
    {"process_line", (PyCFunction)CPyPy_process_line, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"align_offset", (PyCFunction)CPyPy_align_offset, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"process_chunk", (PyCFunction)CPyPy_process_chunk, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"process_line_no_write", (PyCFunction)CPyPy_process_line_no_write, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"process_whole_file", (PyCFunction)CPyPy_process_whole_file, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"process_genome", (PyCFunction)CPyPy_process_genome, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"read_file_in_chunks", (PyCFunction)CPyPy_read_file_in_chunks, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {"process_fasta_file", (PyCFunction)CPyPy_process_fasta_file, METH_FASTCALL | METH_KEYWORDS, NULL /* docstring */},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "process_fasta_input",
    NULL, /* docstring */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    module_methods
};

PyMODINIT_FUNC PyInit_process_fasta_input(void)
{
    PyObject* modname = NULL;
    if (CPyModule_process_fasta_input_internal) {
        Py_INCREF(CPyModule_process_fasta_input_internal);
        return CPyModule_process_fasta_input_internal;
    }
    CPyModule_process_fasta_input_internal = PyModule_Create(&module);
    if (unlikely(CPyModule_process_fasta_input_internal == NULL))
        goto fail;
    modname = PyObject_GetAttrString((PyObject *)CPyModule_process_fasta_input_internal, "__name__");
    CPyStatic_globals = PyModule_GetDict(CPyModule_process_fasta_input_internal);
    if (unlikely(CPyStatic_globals == NULL))
        goto fail;
    if (CPyGlobalsInit() < 0)
        goto fail;
    char result = CPyDef___top_level__();
    if (result == 2)
        goto fail;
    Py_DECREF(modname);
    return CPyModule_process_fasta_input_internal;
    fail:
    Py_CLEAR(CPyModule_process_fasta_input_internal);
    Py_CLEAR(modname);
    return NULL;
}

tuple_T3IOO CPyDef_process_line(PyObject *cpy_r_line, PyObject *cpy_r_ff, PyObject *cpy_r_fh) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    int32_t cpy_r_r2;
    char cpy_r_r3;
    char cpy_r_r4;
    PyObject *cpy_r_r5;
    PyObject *cpy_r_r6;
    int32_t cpy_r_r7;
    char cpy_r_r8;
    char cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_r11;
    tuple_T3IOO cpy_r_r12;
    PyObject *cpy_r_r13;
    PyObject *cpy_r_r14;
    int32_t cpy_r_r15;
    char cpy_r_r16;
    char cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject **cpy_r_r22;
    PyObject *cpy_r_r23;
    PyObject *cpy_r_r24;
    PyObject *cpy_r_r25;
    PyObject *cpy_r_r26;
    tuple_T3IOO cpy_r_r27;
    PyObject *cpy_r_r28;
    PyObject **cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    PyObject *cpy_r_r34;
    PyObject *cpy_r_r35;
    PyObject **cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    PyObject *cpy_r_r40;
    PyObject *cpy_r_r41;
    PyObject *cpy_r_r42;
    PyObject **cpy_r_r44;
    PyObject *cpy_r_r45;
    PyObject *cpy_r_protein;
    PyObject *cpy_r_r46;
    PyObject *cpy_r_r47;
    PyObject **cpy_r_r49;
    PyObject *cpy_r_r50;
    PyObject *cpy_r_r51;
    PyObject *cpy_r_r52;
    PyObject *cpy_r_r53;
    PyObject *cpy_r_r54;
    PyObject *cpy_r_r55;
    PyObject *cpy_r_r56;
    PyObject *cpy_r_r57;
    PyObject *cpy_r_r58;
    PyObject *cpy_r_r59;
    PyObject *cpy_r_r60;
    PyObject *cpy_r_r61;
    PyObject *cpy_r_r62;
    PyObject *cpy_r_r63;
    PyObject **cpy_r_r65;
    PyObject *cpy_r_r66;
    PyObject *cpy_r_r67;
    PyObject *cpy_r_r68;
    PyObject *cpy_r_r69;
    PyObject *cpy_r_r70;
    tuple_T3IOO cpy_r_r71;
    tuple_T3IOO cpy_r_r72;
    cpy_r_r0 = CPyBytes_GetSlice(cpy_r_line, 0, 2);
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 12, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r1 = CPyStatics[58]; /* b'\n' */
    cpy_r_r2 = CPyBytes_Compare(cpy_r_r0, cpy_r_r1);
    CPy_DECREF(cpy_r_r0);
    cpy_r_r3 = cpy_r_r2 >= 0;
    if (unlikely(!cpy_r_r3)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 12, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r4 = cpy_r_r2 == 1;
    if (cpy_r_r4) goto CPyL6;
    cpy_r_r5 = CPyBytes_GetSlice(cpy_r_line, 0, 2);
    if (unlikely(cpy_r_r5 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 12, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r6 = CPyStatics[59]; /* b'\r' */
    cpy_r_r7 = CPyBytes_Compare(cpy_r_r5, cpy_r_r6);
    CPy_DECREF(cpy_r_r5);
    cpy_r_r8 = cpy_r_r7 >= 0;
    if (unlikely(!cpy_r_r8)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 12, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r9 = cpy_r_r7 == 1;
    if (!cpy_r_r9) goto CPyL7;
CPyL6: ;
    cpy_r_r10 = CPyStatics[3]; /* '\n' */
    cpy_r_r11 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_r10);
    CPy_INCREF(cpy_r_r11);
    cpy_r_r12.f0 = 0;
    cpy_r_r12.f1 = cpy_r_r10;
    cpy_r_r12.f2 = cpy_r_r11;
    return cpy_r_r12;
CPyL7: ;
    cpy_r_r13 = CPyBytes_GetSlice(cpy_r_line, 0, 2);
    if (unlikely(cpy_r_r13 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 14, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r14 = CPyStatics[60]; /* b'>' */
    cpy_r_r15 = CPyBytes_Compare(cpy_r_r13, cpy_r_r14);
    CPy_DECREF(cpy_r_r13);
    cpy_r_r16 = cpy_r_r15 >= 0;
    if (unlikely(!cpy_r_r16)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 14, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r17 = cpy_r_r15 != 1;
    if (!cpy_r_r17) goto CPyL14;
    cpy_r_r18 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r19 = CPy_Decode(cpy_r_line, cpy_r_r18, NULL);
    if (unlikely(cpy_r_r19 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 15, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r20 = CPyStatics[6]; /* 'write' */
    PyObject *cpy_r_r21[2] = {cpy_r_ff, cpy_r_r19};
    cpy_r_r22 = (PyObject **)&cpy_r_r21;
    cpy_r_r23 = PyObject_VectorcallMethod(cpy_r_r20, cpy_r_r22, 9223372036854775810ULL, 0);
    if (unlikely(cpy_r_r23 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 15, CPyStatic_globals);
        goto CPyL33;
    } else
        goto CPyL34;
CPyL12: ;
    CPy_DECREF(cpy_r_r19);
    cpy_r_r24 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r25 = CPy_Decode(cpy_r_line, cpy_r_r24, NULL);
    if (unlikely(cpy_r_r25 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 16, CPyStatic_globals);
        goto CPyL32;
    }
    cpy_r_r26 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_r26);
    cpy_r_r27.f0 = 2;
    cpy_r_r27.f1 = cpy_r_r25;
    cpy_r_r27.f2 = cpy_r_r26;
    return cpy_r_r27;
CPyL14: ;
    cpy_r_r28 = CPyStatics[7]; /* 'rstrip' */
    PyObject *cpy_r_r29[1] = {cpy_r_line};
    cpy_r_r30 = (PyObject **)&cpy_r_r29;
    cpy_r_r31 = PyObject_VectorcallMethod(cpy_r_r28, cpy_r_r30, 9223372036854775809ULL, 0);
    if (unlikely(cpy_r_r31 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 17, CPyStatic_globals);
        goto CPyL32;
    }
    if (likely(PyBytes_Check(cpy_r_r31) || PyByteArray_Check(cpy_r_r31)))
        cpy_r_r32 = cpy_r_r31;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_line", 17, CPyStatic_globals, "bytes", cpy_r_r31);
        goto CPyL32;
    }
    cpy_r_r33 = CPyStatics[61]; /* b' ' */
    cpy_r_r34 = CPyStatics[62]; /* b'*' */
    cpy_r_r35 = CPyStatics[8]; /* 'replace' */
    PyObject *cpy_r_r36[3] = {cpy_r_r32, cpy_r_r33, cpy_r_r34};
    cpy_r_r37 = (PyObject **)&cpy_r_r36;
    cpy_r_r38 = PyObject_VectorcallMethod(cpy_r_r35, cpy_r_r37, 9223372036854775811ULL, 0);
    if (unlikely(cpy_r_r38 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 17, CPyStatic_globals);
        goto CPyL35;
    }
    CPy_DECREF(cpy_r_r32);
    if (likely(PyBytes_Check(cpy_r_r38) || PyByteArray_Check(cpy_r_r38)))
        cpy_r_r39 = cpy_r_r38;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_line", 17, CPyStatic_globals, "bytes", cpy_r_r38);
        goto CPyL32;
    }
    cpy_r_line = cpy_r_r39;
    cpy_r_r40 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r41 = CPy_Decode(cpy_r_line, cpy_r_r40, NULL);
    if (unlikely(cpy_r_r41 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 18, CPyStatic_globals);
        goto CPyL36;
    }
    cpy_r_r42 = CPyStatics[6]; /* 'write' */
    PyObject *cpy_r_r43[2] = {cpy_r_ff, cpy_r_r41};
    cpy_r_r44 = (PyObject **)&cpy_r_r43;
    cpy_r_r45 = PyObject_VectorcallMethod(cpy_r_r42, cpy_r_r44, 9223372036854775810ULL, 0);
    if (unlikely(cpy_r_r45 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 18, CPyStatic_globals);
        goto CPyL37;
    } else
        goto CPyL38;
CPyL20: ;
    CPy_DECREF(cpy_r_r41);
    CPy_INCREF(cpy_r_line);
    cpy_r_protein = cpy_r_line;
    cpy_r_r46 = CPyStatics[63]; /* b'[' */
    cpy_r_r47 = CPyStatics[9]; /* 'split' */
    PyObject *cpy_r_r48[2] = {cpy_r_line, cpy_r_r46};
    cpy_r_r49 = (PyObject **)&cpy_r_r48;
    cpy_r_r50 = PyObject_VectorcallMethod(cpy_r_r47, cpy_r_r49, 9223372036854775810ULL, 0);
    if (unlikely(cpy_r_r50 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 21, CPyStatic_globals);
        goto CPyL39;
    }
    CPy_DECREF(cpy_r_line);
    if (likely(PyList_Check(cpy_r_r50)))
        cpy_r_r51 = cpy_r_r50;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_line", 21, CPyStatic_globals, "list", cpy_r_r50);
        goto CPyL40;
    }
    cpy_r_r52 = CPyList_GetSlice(cpy_r_r51, 2, 9223372036854775806LL);
    CPy_DECREF(cpy_r_r51);
    if (unlikely(cpy_r_r52 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 22, CPyStatic_globals);
        goto CPyL40;
    }
    if (likely(PyList_Check(cpy_r_r52)))
        cpy_r_r53 = cpy_r_r52;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_line", 22, CPyStatic_globals, "list", cpy_r_r52);
        goto CPyL40;
    }
    cpy_r_r54 = CPyStatics[64]; /* b'' */
    cpy_r_r55 = CPyBytes_Join(cpy_r_r54, cpy_r_r53);
    CPy_DECREF(cpy_r_r53);
    if (unlikely(cpy_r_r55 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 24, CPyStatic_globals);
        goto CPyL40;
    }
    cpy_r_r56 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r57 = CPy_Decode(cpy_r_r55, cpy_r_r56, NULL);
    if (unlikely(cpy_r_r57 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 25, CPyStatic_globals);
        goto CPyL41;
    }
    cpy_r_r58 = CPyStatics[10]; /* ' ' */
    cpy_r_r59 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r60 = CPy_Decode(cpy_r_protein, cpy_r_r59, NULL);
    if (unlikely(cpy_r_r60 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 25, CPyStatic_globals);
        goto CPyL42;
    }
    cpy_r_r61 = CPyStatics[3]; /* '\n' */
    cpy_r_r62 = CPyStr_Build(4, cpy_r_r57, cpy_r_r58, cpy_r_r60, cpy_r_r61);
    CPy_DECREF(cpy_r_r57);
    CPy_DECREF(cpy_r_r60);
    if (unlikely(cpy_r_r62 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 25, CPyStatic_globals);
        goto CPyL41;
    }
    cpy_r_r63 = CPyStatics[6]; /* 'write' */
    PyObject *cpy_r_r64[2] = {cpy_r_fh, cpy_r_r62};
    cpy_r_r65 = (PyObject **)&cpy_r_r64;
    cpy_r_r66 = PyObject_VectorcallMethod(cpy_r_r63, cpy_r_r65, 9223372036854775810ULL, 0);
    if (unlikely(cpy_r_r66 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 25, CPyStatic_globals);
        goto CPyL43;
    } else
        goto CPyL44;
CPyL29: ;
    CPy_DECREF(cpy_r_r62);
    cpy_r_r67 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r68 = CPy_Decode(cpy_r_protein, cpy_r_r67, NULL);
    CPy_DECREF(cpy_r_protein);
    if (unlikely(cpy_r_r68 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 26, CPyStatic_globals);
        goto CPyL45;
    }
    cpy_r_r69 = CPyStatics[5]; /* 'UTF-8' */
    cpy_r_r70 = CPy_Decode(cpy_r_r55, cpy_r_r69, NULL);
    CPy_DECREF(cpy_r_r55);
    if (unlikely(cpy_r_r70 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line", 26, CPyStatic_globals);
        goto CPyL46;
    }
    cpy_r_r71.f0 = 4;
    cpy_r_r71.f1 = cpy_r_r68;
    cpy_r_r71.f2 = cpy_r_r70;
    return cpy_r_r71;
CPyL32: ;
    tuple_T3IOO __tmp1 = { CPY_INT_TAG, NULL, NULL };
    cpy_r_r72 = __tmp1;
    return cpy_r_r72;
CPyL33: ;
    CPy_DecRef(cpy_r_r19);
    goto CPyL32;
CPyL34: ;
    CPy_DECREF(cpy_r_r23);
    goto CPyL12;
CPyL35: ;
    CPy_DecRef(cpy_r_r32);
    goto CPyL32;
CPyL36: ;
    CPy_DecRef(cpy_r_line);
    goto CPyL32;
CPyL37: ;
    CPy_DecRef(cpy_r_line);
    CPy_DecRef(cpy_r_r41);
    goto CPyL32;
CPyL38: ;
    CPy_DECREF(cpy_r_r45);
    goto CPyL20;
CPyL39: ;
    CPy_DecRef(cpy_r_line);
    CPy_DecRef(cpy_r_protein);
    goto CPyL32;
CPyL40: ;
    CPy_DecRef(cpy_r_protein);
    goto CPyL32;
CPyL41: ;
    CPy_DecRef(cpy_r_protein);
    CPy_DecRef(cpy_r_r55);
    goto CPyL32;
CPyL42: ;
    CPy_DecRef(cpy_r_protein);
    CPy_DecRef(cpy_r_r55);
    CPy_DecRef(cpy_r_r57);
    goto CPyL32;
CPyL43: ;
    CPy_DecRef(cpy_r_protein);
    CPy_DecRef(cpy_r_r55);
    CPy_DecRef(cpy_r_r62);
    goto CPyL32;
CPyL44: ;
    CPy_DECREF(cpy_r_r66);
    goto CPyL29;
CPyL45: ;
    CPy_DecRef(cpy_r_r55);
    goto CPyL32;
CPyL46: ;
    CPy_DecRef(cpy_r_r68);
    goto CPyL32;
}

PyObject *CPyPy_process_line(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"line", "ff", "fh", 0};
    static CPyArg_Parser parser = {"OOO:process_line", kwlist, 0};
    PyObject *obj_line;
    PyObject *obj_ff;
    PyObject *obj_fh;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_line, &obj_ff, &obj_fh)) {
        return NULL;
    }
    PyObject *arg_line;
    if (likely(PyBytes_Check(obj_line) || PyByteArray_Check(obj_line)))
        arg_line = obj_line;
    else {
        CPy_TypeError("bytes", obj_line); 
        goto fail;
    }
    PyObject *arg_ff = obj_ff;
    PyObject *arg_fh = obj_fh;
    tuple_T3IOO retval = CPyDef_process_line(arg_line, arg_ff, arg_fh);
    if (retval.f0 == CPY_INT_TAG) {
        return NULL;
    }
    PyObject *retbox = PyTuple_New(3);
    if (unlikely(retbox == NULL))
        CPyError_OutOfMemory();
    PyObject *__tmp2 = CPyTagged_StealAsObject(retval.f0);
    PyTuple_SET_ITEM(retbox, 0, __tmp2);
    PyObject *__tmp3 = retval.f1;
    PyTuple_SET_ITEM(retbox, 1, __tmp3);
    PyObject *__tmp4 = retval.f2;
    PyTuple_SET_ITEM(retbox, 2, __tmp4);
    return retbox;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "process_line", 11, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_align_offset(PyObject *cpy_r_offset, PyObject *cpy_r_page_size) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    PyObject *cpy_r_r2;
    cpy_r_r0 = PyNumber_FloorDivide(cpy_r_offset, cpy_r_page_size);
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "align_offset", 29, CPyStatic_globals);
        goto CPyL3;
    }
    cpy_r_r1 = PyNumber_Multiply(cpy_r_r0, cpy_r_page_size);
    CPy_DECREF(cpy_r_r0);
    if (unlikely(cpy_r_r1 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "align_offset", 29, CPyStatic_globals);
        goto CPyL3;
    }
    return cpy_r_r1;
CPyL3: ;
    cpy_r_r2 = NULL;
    return cpy_r_r2;
}

PyObject *CPyPy_align_offset(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"offset", "page_size", 0};
    static CPyArg_Parser parser = {"OO:align_offset", kwlist, 0};
    PyObject *obj_offset;
    PyObject *obj_page_size;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_offset, &obj_page_size)) {
        return NULL;
    }
    PyObject *arg_offset = obj_offset;
    PyObject *arg_page_size = obj_page_size;
    PyObject *retval = CPyDef_align_offset(arg_offset, arg_page_size);
    return retval;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "align_offset", 28, CPyStatic_globals);
    return NULL;
}

char CPyDef_process_chunk(PyObject *cpy_r_file_path, PyObject *cpy_r_start_byte, PyObject *cpy_r_end_byte, CPyTagged cpy_r_file_counter, PyObject *cpy_r_output) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    PyObject *cpy_r_r2;
    CPyTagged cpy_r_r3;
    PyObject *cpy_r_r4;
    PyObject *cpy_r_r5;
    PyObject *cpy_r_r6;
    PyObject *cpy_r_r7;
    PyObject *cpy_r_r8;
    PyObject *cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_r11;
    PyObject *cpy_r_r12;
    PyObject *cpy_r_r13;
    PyObject *cpy_r_r14;
    PyObject **cpy_r_r16;
    PyObject *cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject *cpy_r_r21;
    PyObject **cpy_r_r23;
    PyObject *cpy_r_r24;
    tuple_T3OOO cpy_r_r25;
    PyObject *cpy_r_r26;
    PyObject *cpy_r_r27;
    PyObject *cpy_r_r28;
    char cpy_r_r29;
    char cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    PyObject *cpy_r_r34;
    PyObject *cpy_r_r35;
    PyObject *cpy_r_r36;
    PyObject *cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    PyObject **cpy_r_r41;
    PyObject *cpy_r_r42;
    PyObject *cpy_r_r43;
    PyObject *cpy_r_r44;
    PyObject *cpy_r_r45;
    PyObject *cpy_r_r46;
    PyObject **cpy_r_r48;
    PyObject *cpy_r_r49;
    tuple_T3OOO cpy_r_r50;
    PyObject *cpy_r_r51;
    PyObject *cpy_r_r52;
    PyObject *cpy_r_r53;
    char cpy_r_r54;
    char cpy_r_r55;
    PyObject *cpy_r_r56;
    PyObject *cpy_r_r57;
    PyObject *cpy_r_r58;
    PyObject *cpy_r_r59;
    PyObject *cpy_r_r60;
    PyObject *cpy_r_r61;
    PyObject *cpy_r_r62;
    PyObject *cpy_r_r63;
    PyObject *cpy_r_r64;
    PyObject **cpy_r_r66;
    PyObject *cpy_r_r67;
    PyObject *cpy_r_r68;
    PyObject *cpy_r_r69;
    PyObject *cpy_r_r70;
    PyObject *cpy_r_r71;
    PyObject *cpy_r_r72;
    PyObject **cpy_r_r74;
    PyObject *cpy_r_r75;
    PyObject *cpy_r_r76;
    PyObject *cpy_r_r77;
    PyObject *cpy_r_r78;
    PyObject *cpy_r_r79;
    PyObject *cpy_r_r80;
    PyObject *cpy_r_r81;
    PyObject *cpy_r_r82;
    PyObject *cpy_r_r83;
    PyObject *cpy_r_r84;
    PyObject **cpy_r_r86;
    PyObject *cpy_r_r87;
    PyObject *cpy_r_r88;
    PyObject *cpy_r_r89;
    PyObject *cpy_r_r90;
    PyObject *cpy_r_r91;
    PyObject *cpy_r_r92;
    PyObject **cpy_r_r94;
    PyObject *cpy_r_r95;
    PyObject *cpy_r_r96;
    PyObject *cpy_r_d;
    PyObject *cpy_r_r97;
    PyObject *cpy_r_r98;
    PyObject *cpy_r_r99;
    PyObject *cpy_r_r100;
    PyObject **cpy_r_r102;
    PyObject *cpy_r_r103;
    PyObject *cpy_r_r104;
    PyObject *cpy_r_r105;
    PyObject *cpy_r_r106;
    PyObject *cpy_r_r107;
    PyObject *cpy_r_r108;
    PyObject **cpy_r_r110;
    PyObject *cpy_r_r111;
    char cpy_r_r112;
    PyObject *cpy_r_r113;
    PyObject *cpy_r_r114;
    PyObject **cpy_r_r116;
    PyObject *cpy_r_r117;
    CPyTagged cpy_r_r118;
    PyObject *cpy_r_r119;
    PyObject *cpy_r_r120;
    PyObject *cpy_r_r121;
    CPyTagged cpy_r_r122;
    PyObject *cpy_r_r123;
    PyObject *cpy_r_r124;
    PyObject *cpy_r_r125;
    PyObject *cpy_r_r126;
    PyObject *cpy_r_r127;
    PyObject **cpy_r_r129;
    PyObject *cpy_r_r130;
    PyObject *cpy_r_r131;
    PyObject *cpy_r_r132;
    PyObject *cpy_r_r133;
    PyObject *cpy_r_r134;
    PyObject *cpy_r_r135;
    PyObject *cpy_r_r136;
    PyObject **cpy_r_r138;
    PyObject *cpy_r_r139;
    char cpy_r_r140;
    PyObject *cpy_r_r141;
    PyObject *cpy_r_r142;
    PyObject **cpy_r_r144;
    PyObject *cpy_r_r145;
    PyObject *cpy_r_r146;
    PyObject *cpy_r_current_seq;
    PyObject *cpy_r_r147;
    PyObject *cpy_r_r148;
    PyObject *cpy_r_r149;
    PyObject *cpy_r_r150;
    PyObject *cpy_r_r151;
    PyObject *cpy_r_r152;
    PyObject **cpy_r_r154;
    PyObject *cpy_r_r155;
    PyObject *cpy_r_r156;
    PyObject *cpy_r_r157;
    PyObject *cpy_r_r158;
    tuple_T3IOO cpy_r_r159;
    tuple_T2OO cpy_r_r160;
    PyObject *cpy_r_r161;
    PyObject *cpy_r_r162;
    PyObject *cpy_r_r163;
    PyObject *cpy_r_r164;
    char cpy_r_r165;
    tuple_T3OOO cpy_r_r166;
    tuple_T3OOO cpy_r_r167;
    PyObject *cpy_r_r168;
    PyObject *cpy_r_r169;
    PyObject *cpy_r_r170;
    PyObject **cpy_r_r172;
    PyObject *cpy_r_r173;
    int32_t cpy_r_r174;
    char cpy_r_r175;
    char cpy_r_r176;
    char cpy_r_r177;
    tuple_T3OOO cpy_r_r178;
    tuple_T3OOO cpy_r_r179;
    tuple_T3OOO cpy_r_r180;
    PyObject *cpy_r_r181;
    PyObject **cpy_r_r183;
    PyObject *cpy_r_r184;
    char cpy_r_r185;
    tuple_T3OOO cpy_r_r186;
    tuple_T3OOO cpy_r_r187;
    PyObject *cpy_r_r188;
    PyObject *cpy_r_r189;
    PyObject *cpy_r_r190;
    PyObject **cpy_r_r192;
    PyObject *cpy_r_r193;
    int32_t cpy_r_r194;
    char cpy_r_r195;
    char cpy_r_r196;
    char cpy_r_r197;
    tuple_T3OOO cpy_r_r198;
    tuple_T3OOO cpy_r_r199;
    tuple_T3OOO cpy_r_r200;
    PyObject *cpy_r_r201;
    PyObject **cpy_r_r203;
    PyObject *cpy_r_r204;
    char cpy_r_r205;
    char cpy_r_r206;
    cpy_r_r0 = CPyStatic_globals;
    cpy_r_r1 = CPyStatics[11]; /* 'MMAP_PAGE_SIZE' */
    cpy_r_r2 = CPyDict_GetItem(cpy_r_r0, cpy_r_r1);
    if (unlikely(cpy_r_r2 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 33, CPyStatic_globals);
        goto CPyL123;
    }
    if (likely(PyLong_Check(cpy_r_r2)))
        cpy_r_r3 = CPyTagged_FromObject(cpy_r_r2);
    else {
        CPy_TypeError("int", cpy_r_r2); cpy_r_r3 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r2);
    if (unlikely(cpy_r_r3 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 33, CPyStatic_globals);
        goto CPyL123;
    }
    cpy_r_r4 = CPyTagged_StealAsObject(cpy_r_r3);
    cpy_r_r5 = CPyDef_align_offset(cpy_r_start_byte, cpy_r_r4);
    CPy_DECREF(cpy_r_r4);
    if (unlikely(cpy_r_r5 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 33, CPyStatic_globals);
        goto CPyL123;
    }
    cpy_r_r6 = CPyStatics[12]; /* 'fastafile_' */
    cpy_r_r7 = CPyTagged_Str(cpy_r_file_counter);
    if (unlikely(cpy_r_r7 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL13;
    }
    cpy_r_r8 = CPyStatics[13]; /* '.faa' */
    cpy_r_r9 = CPyStr_Build(3, cpy_r_r6, cpy_r_r7, cpy_r_r8);
    CPy_DECREF(cpy_r_r7);
    if (unlikely(cpy_r_r9 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL13;
    }
    cpy_r_r10 = CPyModule_os;
    cpy_r_r11 = CPyStatics[14]; /* 'path' */
    cpy_r_r12 = CPyObject_GetAttr(cpy_r_r10, cpy_r_r11);
    if (unlikely(cpy_r_r12 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL124;
    }
    cpy_r_r13 = CPyStatics[15]; /* 'join' */
    cpy_r_r14 = CPyObject_GetAttr(cpy_r_r12, cpy_r_r13);
    CPy_DECREF(cpy_r_r12);
    if (unlikely(cpy_r_r14 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL124;
    }
    PyObject *cpy_r_r15[2] = {cpy_r_output, cpy_r_r9};
    cpy_r_r16 = (PyObject **)&cpy_r_r15;
    cpy_r_r17 = _PyObject_Vectorcall(cpy_r_r14, cpy_r_r16, 2, 0);
    CPy_DECREF(cpy_r_r14);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL124;
    }
    CPy_DECREF(cpy_r_r9);
    if (likely(PyUnicode_Check(cpy_r_r17)))
        cpy_r_r18 = cpy_r_r17;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals, "str", cpy_r_r17);
        goto CPyL13;
    }
    cpy_r_r19 = CPyModule_os;
    cpy_r_r20 = CPyStatics[16]; /* 'remove' */
    cpy_r_r21 = CPyObject_GetAttr(cpy_r_r19, cpy_r_r20);
    if (unlikely(cpy_r_r21 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL125;
    }
    PyObject *cpy_r_r22[1] = {cpy_r_r18};
    cpy_r_r23 = (PyObject **)&cpy_r_r22;
    cpy_r_r24 = _PyObject_Vectorcall(cpy_r_r21, cpy_r_r23, 1, 0);
    CPy_DECREF(cpy_r_r21);
    if (unlikely(cpy_r_r24 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 35, CPyStatic_globals);
        goto CPyL125;
    } else
        goto CPyL126;
CPyL12: ;
    CPy_DECREF(cpy_r_r18);
    goto CPyL20;
CPyL13: ;
    cpy_r_r25 = CPy_CatchError();
    cpy_r_r26 = CPyModule_builtins;
    cpy_r_r27 = CPyStatics[17]; /* 'OSError' */
    cpy_r_r28 = CPyObject_GetAttr(cpy_r_r26, cpy_r_r27);
    if (unlikely(cpy_r_r28 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 36, CPyStatic_globals);
        goto CPyL127;
    }
    cpy_r_r29 = CPy_ExceptionMatches(cpy_r_r28);
    CPy_DecRef(cpy_r_r28);
    if (cpy_r_r29) {
        goto CPyL17;
    } else
        goto CPyL128;
CPyL15: ;
    CPy_Reraise();
    if (!0) {
        goto CPyL18;
    } else
        goto CPyL129;
CPyL16: ;
    CPy_Unreachable();
CPyL17: ;
    CPy_RestoreExcInfo(cpy_r_r25);
    CPy_DecRef(cpy_r_r25.f0);
    CPy_DecRef(cpy_r_r25.f1);
    CPy_DecRef(cpy_r_r25.f2);
    goto CPyL20;
CPyL18: ;
    CPy_RestoreExcInfo(cpy_r_r25);
    CPy_DecRef(cpy_r_r25.f0);
    CPy_DecRef(cpy_r_r25.f1);
    CPy_DecRef(cpy_r_r25.f2);
    cpy_r_r30 = CPy_KeepPropagating();
    if (!cpy_r_r30) goto CPyL123;
    CPy_Unreachable();
CPyL20: ;
    cpy_r_r31 = CPyStatics[18]; /* 'fasta-headers_' */
    cpy_r_r32 = CPyTagged_Str(cpy_r_file_counter);
    if (unlikely(cpy_r_r32 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL29;
    }
    cpy_r_r33 = CPyStatics[19]; /* '.txt' */
    cpy_r_r34 = CPyStr_Build(3, cpy_r_r31, cpy_r_r32, cpy_r_r33);
    CPy_DECREF(cpy_r_r32);
    if (unlikely(cpy_r_r34 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL29;
    }
    cpy_r_r35 = CPyModule_os;
    cpy_r_r36 = CPyStatics[14]; /* 'path' */
    cpy_r_r37 = CPyObject_GetAttr(cpy_r_r35, cpy_r_r36);
    if (unlikely(cpy_r_r37 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL130;
    }
    cpy_r_r38 = CPyStatics[15]; /* 'join' */
    cpy_r_r39 = CPyObject_GetAttr(cpy_r_r37, cpy_r_r38);
    CPy_DECREF(cpy_r_r37);
    if (unlikely(cpy_r_r39 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL130;
    }
    PyObject *cpy_r_r40[2] = {cpy_r_output, cpy_r_r34};
    cpy_r_r41 = (PyObject **)&cpy_r_r40;
    cpy_r_r42 = _PyObject_Vectorcall(cpy_r_r39, cpy_r_r41, 2, 0);
    CPy_DECREF(cpy_r_r39);
    if (unlikely(cpy_r_r42 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL130;
    }
    CPy_DECREF(cpy_r_r34);
    if (likely(PyUnicode_Check(cpy_r_r42)))
        cpy_r_r43 = cpy_r_r42;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals, "str", cpy_r_r42);
        goto CPyL29;
    }
    cpy_r_r44 = CPyModule_os;
    cpy_r_r45 = CPyStatics[16]; /* 'remove' */
    cpy_r_r46 = CPyObject_GetAttr(cpy_r_r44, cpy_r_r45);
    if (unlikely(cpy_r_r46 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL131;
    }
    PyObject *cpy_r_r47[1] = {cpy_r_r43};
    cpy_r_r48 = (PyObject **)&cpy_r_r47;
    cpy_r_r49 = _PyObject_Vectorcall(cpy_r_r46, cpy_r_r48, 1, 0);
    CPy_DECREF(cpy_r_r46);
    if (unlikely(cpy_r_r49 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 39, CPyStatic_globals);
        goto CPyL131;
    } else
        goto CPyL132;
CPyL28: ;
    CPy_DECREF(cpy_r_r43);
    goto CPyL36;
CPyL29: ;
    cpy_r_r50 = CPy_CatchError();
    cpy_r_r51 = CPyModule_builtins;
    cpy_r_r52 = CPyStatics[17]; /* 'OSError' */
    cpy_r_r53 = CPyObject_GetAttr(cpy_r_r51, cpy_r_r52);
    if (unlikely(cpy_r_r53 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 40, CPyStatic_globals);
        goto CPyL133;
    }
    cpy_r_r54 = CPy_ExceptionMatches(cpy_r_r53);
    CPy_DecRef(cpy_r_r53);
    if (cpy_r_r54) {
        goto CPyL33;
    } else
        goto CPyL134;
CPyL31: ;
    CPy_Reraise();
    if (!0) {
        goto CPyL34;
    } else
        goto CPyL135;
CPyL32: ;
    CPy_Unreachable();
CPyL33: ;
    CPy_RestoreExcInfo(cpy_r_r50);
    CPy_DecRef(cpy_r_r50.f0);
    CPy_DecRef(cpy_r_r50.f1);
    CPy_DecRef(cpy_r_r50.f2);
    goto CPyL36;
CPyL34: ;
    CPy_RestoreExcInfo(cpy_r_r50);
    CPy_DecRef(cpy_r_r50.f0);
    CPy_DecRef(cpy_r_r50.f1);
    CPy_DecRef(cpy_r_r50.f2);
    cpy_r_r55 = CPy_KeepPropagating();
    if (!cpy_r_r55) goto CPyL123;
    CPy_Unreachable();
CPyL36: ;
    cpy_r_r56 = CPyStatics[12]; /* 'fastafile_' */
    cpy_r_r57 = CPyTagged_Str(cpy_r_file_counter);
    if (unlikely(cpy_r_r57 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL136;
    }
    cpy_r_r58 = CPyStatics[13]; /* '.faa' */
    cpy_r_r59 = CPyStr_Build(3, cpy_r_r56, cpy_r_r57, cpy_r_r58);
    CPy_DECREF(cpy_r_r57);
    if (unlikely(cpy_r_r59 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL136;
    }
    cpy_r_r60 = CPyModule_os;
    cpy_r_r61 = CPyStatics[14]; /* 'path' */
    cpy_r_r62 = CPyObject_GetAttr(cpy_r_r60, cpy_r_r61);
    if (unlikely(cpy_r_r62 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL137;
    }
    cpy_r_r63 = CPyStatics[15]; /* 'join' */
    cpy_r_r64 = CPyObject_GetAttr(cpy_r_r62, cpy_r_r63);
    CPy_DECREF(cpy_r_r62);
    if (unlikely(cpy_r_r64 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL137;
    }
    PyObject *cpy_r_r65[2] = {cpy_r_output, cpy_r_r59};
    cpy_r_r66 = (PyObject **)&cpy_r_r65;
    cpy_r_r67 = _PyObject_Vectorcall(cpy_r_r64, cpy_r_r66, 2, 0);
    CPy_DECREF(cpy_r_r64);
    if (unlikely(cpy_r_r67 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL137;
    }
    CPy_DECREF(cpy_r_r59);
    if (likely(PyUnicode_Check(cpy_r_r67)))
        cpy_r_r68 = cpy_r_r67;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals, "str", cpy_r_r67);
        goto CPyL136;
    }
    cpy_r_r69 = CPyStatics[20]; /* 'a' */
    cpy_r_r70 = CPyModule_builtins;
    cpy_r_r71 = CPyStatics[21]; /* 'open' */
    cpy_r_r72 = CPyObject_GetAttr(cpy_r_r70, cpy_r_r71);
    if (unlikely(cpy_r_r72 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL138;
    }
    PyObject *cpy_r_r73[2] = {cpy_r_r68, cpy_r_r69};
    cpy_r_r74 = (PyObject **)&cpy_r_r73;
    cpy_r_r75 = _PyObject_Vectorcall(cpy_r_r72, cpy_r_r74, 2, 0);
    CPy_DECREF(cpy_r_r72);
    if (unlikely(cpy_r_r75 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 42, CPyStatic_globals);
        goto CPyL138;
    }
    CPy_DECREF(cpy_r_r68);
    cpy_r_r76 = CPyStatics[18]; /* 'fasta-headers_' */
    cpy_r_r77 = CPyTagged_Str(cpy_r_file_counter);
    if (unlikely(cpy_r_r77 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL139;
    }
    cpy_r_r78 = CPyStatics[19]; /* '.txt' */
    cpy_r_r79 = CPyStr_Build(3, cpy_r_r76, cpy_r_r77, cpy_r_r78);
    CPy_DECREF(cpy_r_r77);
    if (unlikely(cpy_r_r79 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL139;
    }
    cpy_r_r80 = CPyModule_os;
    cpy_r_r81 = CPyStatics[14]; /* 'path' */
    cpy_r_r82 = CPyObject_GetAttr(cpy_r_r80, cpy_r_r81);
    if (unlikely(cpy_r_r82 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL140;
    }
    cpy_r_r83 = CPyStatics[15]; /* 'join' */
    cpy_r_r84 = CPyObject_GetAttr(cpy_r_r82, cpy_r_r83);
    CPy_DECREF(cpy_r_r82);
    if (unlikely(cpy_r_r84 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL140;
    }
    PyObject *cpy_r_r85[2] = {cpy_r_output, cpy_r_r79};
    cpy_r_r86 = (PyObject **)&cpy_r_r85;
    cpy_r_r87 = _PyObject_Vectorcall(cpy_r_r84, cpy_r_r86, 2, 0);
    CPy_DECREF(cpy_r_r84);
    if (unlikely(cpy_r_r87 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL140;
    }
    CPy_DECREF(cpy_r_r79);
    if (likely(PyUnicode_Check(cpy_r_r87)))
        cpy_r_r88 = cpy_r_r87;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals, "str", cpy_r_r87);
        goto CPyL139;
    }
    cpy_r_r89 = CPyStatics[20]; /* 'a' */
    cpy_r_r90 = CPyModule_builtins;
    cpy_r_r91 = CPyStatics[21]; /* 'open' */
    cpy_r_r92 = CPyObject_GetAttr(cpy_r_r90, cpy_r_r91);
    if (unlikely(cpy_r_r92 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL141;
    }
    PyObject *cpy_r_r93[2] = {cpy_r_r88, cpy_r_r89};
    cpy_r_r94 = (PyObject **)&cpy_r_r93;
    cpy_r_r95 = _PyObject_Vectorcall(cpy_r_r92, cpy_r_r94, 2, 0);
    CPy_DECREF(cpy_r_r92);
    if (unlikely(cpy_r_r95 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 43, CPyStatic_globals);
        goto CPyL141;
    }
    CPy_DECREF(cpy_r_r88);
    cpy_r_r96 = PyDict_New();
    if (unlikely(cpy_r_r96 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 44, CPyStatic_globals);
        goto CPyL142;
    }
    cpy_r_d = cpy_r_r96;
    cpy_r_r97 = CPyStatics[22]; /* 'r+b' */
    cpy_r_r98 = CPyModule_builtins;
    cpy_r_r99 = CPyStatics[21]; /* 'open' */
    cpy_r_r100 = CPyObject_GetAttr(cpy_r_r98, cpy_r_r99);
    if (unlikely(cpy_r_r100 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL143;
    }
    PyObject *cpy_r_r101[2] = {cpy_r_file_path, cpy_r_r97};
    cpy_r_r102 = (PyObject **)&cpy_r_r101;
    cpy_r_r103 = _PyObject_Vectorcall(cpy_r_r100, cpy_r_r102, 2, 0);
    CPy_DECREF(cpy_r_r100);
    if (unlikely(cpy_r_r103 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL143;
    }
    cpy_r_r104 = PyObject_Type(cpy_r_r103);
    cpy_r_r105 = CPyStatics[23]; /* '__exit__' */
    cpy_r_r106 = CPyObject_GetAttr(cpy_r_r104, cpy_r_r105);
    if (unlikely(cpy_r_r106 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL144;
    }
    cpy_r_r107 = CPyStatics[24]; /* '__enter__' */
    cpy_r_r108 = CPyObject_GetAttr(cpy_r_r104, cpy_r_r107);
    CPy_DECREF(cpy_r_r104);
    if (unlikely(cpy_r_r108 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL145;
    }
    PyObject *cpy_r_r109[1] = {cpy_r_r103};
    cpy_r_r110 = (PyObject **)&cpy_r_r109;
    cpy_r_r111 = _PyObject_Vectorcall(cpy_r_r108, cpy_r_r110, 1, 0);
    CPy_DECREF(cpy_r_r108);
    if (unlikely(cpy_r_r111 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL145;
    }
    cpy_r_r112 = 1;
    cpy_r_r113 = PyNumber_Subtract(cpy_r_end_byte, cpy_r_r5);
    if (unlikely(cpy_r_r113 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 47, CPyStatic_globals);
        goto CPyL146;
    }
    cpy_r_r114 = CPyStatics[25]; /* 'fileno' */
    PyObject *cpy_r_r115[1] = {cpy_r_r111};
    cpy_r_r116 = (PyObject **)&cpy_r_r115;
    cpy_r_r117 = PyObject_VectorcallMethod(cpy_r_r114, cpy_r_r116, 9223372036854775809ULL, 0);
    if (unlikely(cpy_r_r117 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 49, CPyStatic_globals);
        goto CPyL147;
    }
    CPy_DECREF(cpy_r_r111);
    if (likely(PyLong_Check(cpy_r_r117)))
        cpy_r_r118 = CPyTagged_FromObject(cpy_r_r117);
    else {
        CPy_TypeError("int", cpy_r_r117); cpy_r_r118 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r117);
    if (unlikely(cpy_r_r118 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 49, CPyStatic_globals);
        goto CPyL148;
    }
    cpy_r_r119 = CPyModule_mmap;
    cpy_r_r120 = CPyStatics[26]; /* 'ACCESS_READ' */
    cpy_r_r121 = CPyObject_GetAttr(cpy_r_r119, cpy_r_r120);
    if (unlikely(cpy_r_r121 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 49, CPyStatic_globals);
        goto CPyL149;
    }
    if (likely(PyLong_Check(cpy_r_r121)))
        cpy_r_r122 = CPyTagged_FromObject(cpy_r_r121);
    else {
        CPy_TypeError("int", cpy_r_r121); cpy_r_r122 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r121);
    if (unlikely(cpy_r_r122 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 49, CPyStatic_globals);
        goto CPyL149;
    }
    cpy_r_r123 = CPyModule_mmap;
    cpy_r_r124 = CPyStatics[27]; /* 'mmap' */
    cpy_r_r125 = CPyObject_GetAttr(cpy_r_r123, cpy_r_r124);
    if (unlikely(cpy_r_r125 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL150;
    }
    cpy_r_r126 = CPyTagged_StealAsObject(cpy_r_r118);
    cpy_r_r127 = CPyTagged_StealAsObject(cpy_r_r122);
    PyObject *cpy_r_r128[4] = {cpy_r_r126, cpy_r_r113, cpy_r_r127, cpy_r_r5};
    cpy_r_r129 = (PyObject **)&cpy_r_r128;
    cpy_r_r130 = CPyStatics[66]; /* ('access', 'offset') */
    cpy_r_r131 = _PyObject_Vectorcall(cpy_r_r125, cpy_r_r129, 2, cpy_r_r130);
    CPy_DECREF(cpy_r_r125);
    if (unlikely(cpy_r_r131 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL151;
    }
    CPy_DECREF(cpy_r_r126);
    CPy_DECREF(cpy_r_r113);
    CPy_DECREF(cpy_r_r127);
    cpy_r_r132 = PyObject_Type(cpy_r_r131);
    cpy_r_r133 = CPyStatics[23]; /* '__exit__' */
    cpy_r_r134 = CPyObject_GetAttr(cpy_r_r132, cpy_r_r133);
    if (unlikely(cpy_r_r134 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL152;
    }
    cpy_r_r135 = CPyStatics[24]; /* '__enter__' */
    cpy_r_r136 = CPyObject_GetAttr(cpy_r_r132, cpy_r_r135);
    CPy_DECREF(cpy_r_r132);
    if (unlikely(cpy_r_r136 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL153;
    }
    PyObject *cpy_r_r137[1] = {cpy_r_r131};
    cpy_r_r138 = (PyObject **)&cpy_r_r137;
    cpy_r_r139 = _PyObject_Vectorcall(cpy_r_r136, cpy_r_r138, 1, 0);
    CPy_DECREF(cpy_r_r136);
    if (unlikely(cpy_r_r139 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL153;
    }
    cpy_r_r140 = 1;
    cpy_r_r141 = PyNumber_Subtract(cpy_r_start_byte, cpy_r_r5);
    CPy_DECREF(cpy_r_r5);
    if (unlikely(cpy_r_r141 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 51, CPyStatic_globals);
        goto CPyL154;
    }
    cpy_r_r142 = CPyStatics[30]; /* 'seek' */
    PyObject *cpy_r_r143[2] = {cpy_r_r139, cpy_r_r141};
    cpy_r_r144 = (PyObject **)&cpy_r_r143;
    cpy_r_r145 = PyObject_VectorcallMethod(cpy_r_r142, cpy_r_r144, 9223372036854775810ULL, 0);
    if (unlikely(cpy_r_r145 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 51, CPyStatic_globals);
        goto CPyL155;
    } else
        goto CPyL156;
CPyL72: ;
    CPy_DECREF(cpy_r_r141);
    cpy_r_r146 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_r146);
    cpy_r_current_seq = cpy_r_r146;
    cpy_r_r147 = CPyStatics[31]; /* 'readline' */
    cpy_r_r148 = CPyObject_GetAttr(cpy_r_r139, cpy_r_r147);
    CPy_DECREF(cpy_r_r139);
    if (unlikely(cpy_r_r148 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 53, CPyStatic_globals);
        goto CPyL157;
    }
    cpy_r_r149 = CPyStatics[64]; /* b'' */
    cpy_r_r150 = CPyModule_builtins;
    cpy_r_r151 = CPyStatics[32]; /* 'iter' */
    cpy_r_r152 = CPyObject_GetAttr(cpy_r_r150, cpy_r_r151);
    if (unlikely(cpy_r_r152 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 53, CPyStatic_globals);
        goto CPyL158;
    }
    PyObject *cpy_r_r153[2] = {cpy_r_r148, cpy_r_r149};
    cpy_r_r154 = (PyObject **)&cpy_r_r153;
    cpy_r_r155 = _PyObject_Vectorcall(cpy_r_r152, cpy_r_r154, 2, 0);
    CPy_DECREF(cpy_r_r152);
    if (unlikely(cpy_r_r155 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 53, CPyStatic_globals);
        goto CPyL158;
    }
    CPy_DECREF(cpy_r_r148);
    cpy_r_r156 = PyObject_GetIter(cpy_r_r155);
    CPy_DECREF(cpy_r_r155);
    if (unlikely(cpy_r_r156 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 53, CPyStatic_globals);
        goto CPyL157;
    }
CPyL76: ;
    cpy_r_r157 = PyIter_Next(cpy_r_r156);
    if (cpy_r_r157 == NULL) goto CPyL159;
    if (likely(PyBytes_Check(cpy_r_r157) || PyByteArray_Check(cpy_r_r157)))
        cpy_r_r158 = cpy_r_r157;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_chunk", 53, CPyStatic_globals, "bytes", cpy_r_r157);
        goto CPyL160;
    }
    cpy_r_r159 = CPyDef_process_line(cpy_r_r158, cpy_r_r75, cpy_r_r95);
    CPy_DECREF(cpy_r_r158);
    if (unlikely(cpy_r_r159.f0 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 54, CPyStatic_globals);
        goto CPyL160;
    }
    cpy_r_r160 = CPyDef_process_genome(cpy_r_d, cpy_r_current_seq, cpy_r_r159);
    CPy_DECREF(cpy_r_d);
    CPy_DECREF(cpy_r_current_seq);
    CPyTagged_DECREF(cpy_r_r159.f0);
    CPy_DECREF(cpy_r_r159.f1);
    CPy_DECREF(cpy_r_r159.f2);
    if (unlikely(cpy_r_r160.f0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 55, CPyStatic_globals);
        goto CPyL161;
    }
    cpy_r_r161 = cpy_r_r160.f0;
    cpy_r_r162 = cpy_r_r161;
    cpy_r_d = cpy_r_r162;
    cpy_r_r163 = cpy_r_r160.f1;
    cpy_r_r164 = cpy_r_r163;
    cpy_r_current_seq = cpy_r_r164;
    goto CPyL76;
CPyL81: ;
    cpy_r_r165 = CPy_NoErrOccured();
    if (unlikely(!cpy_r_r165)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 53, CPyStatic_globals);
    } else
        goto CPyL90;
CPyL82: ;
    cpy_r_r166 = CPy_CatchError();
    cpy_r_r140 = 0;
    cpy_r_r167 = CPy_GetExcInfo();
    cpy_r_r168 = cpy_r_r167.f0;
    CPy_INCREF(cpy_r_r168);
    cpy_r_r169 = cpy_r_r167.f1;
    CPy_INCREF(cpy_r_r169);
    cpy_r_r170 = cpy_r_r167.f2;
    CPy_INCREF(cpy_r_r170);
    CPy_DecRef(cpy_r_r167.f0);
    CPy_DecRef(cpy_r_r167.f1);
    CPy_DecRef(cpy_r_r167.f2);
    PyObject *cpy_r_r171[4] = {cpy_r_r131, cpy_r_r168, cpy_r_r169, cpy_r_r170};
    cpy_r_r172 = (PyObject **)&cpy_r_r171;
    cpy_r_r173 = _PyObject_Vectorcall(cpy_r_r134, cpy_r_r172, 4, 0);
    if (unlikely(cpy_r_r173 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL162;
    }
    CPy_DecRef(cpy_r_r168);
    CPy_DecRef(cpy_r_r169);
    CPy_DecRef(cpy_r_r170);
    cpy_r_r174 = PyObject_IsTrue(cpy_r_r173);
    CPy_DecRef(cpy_r_r173);
    cpy_r_r175 = cpy_r_r174 >= 0;
    if (unlikely(!cpy_r_r175)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL88;
    }
    cpy_r_r176 = cpy_r_r174;
    if (cpy_r_r176) goto CPyL87;
    CPy_Reraise();
    if (!0) {
        goto CPyL88;
    } else
        goto CPyL163;
CPyL86: ;
    CPy_Unreachable();
CPyL87: ;
    CPy_RestoreExcInfo(cpy_r_r166);
    CPy_DecRef(cpy_r_r166.f0);
    CPy_DecRef(cpy_r_r166.f1);
    CPy_DecRef(cpy_r_r166.f2);
    goto CPyL90;
CPyL88: ;
    CPy_RestoreExcInfo(cpy_r_r166);
    CPy_DecRef(cpy_r_r166.f0);
    CPy_DecRef(cpy_r_r166.f1);
    CPy_DecRef(cpy_r_r166.f2);
    cpy_r_r177 = CPy_KeepPropagating();
    if (!cpy_r_r177) {
        goto CPyL91;
    } else
        goto CPyL164;
CPyL89: ;
    CPy_Unreachable();
CPyL90: ;
    tuple_T3OOO __tmp5 = { NULL, NULL, NULL };
    cpy_r_r178 = __tmp5;
    cpy_r_r179 = cpy_r_r178;
    goto CPyL92;
CPyL91: ;
    cpy_r_r180 = CPy_CatchError();
    cpy_r_r179 = cpy_r_r180;
CPyL92: ;
    if (!cpy_r_r140) goto CPyL165;
    cpy_r_r181 = (PyObject *)&_Py_NoneStruct;
    PyObject *cpy_r_r182[4] = {cpy_r_r131, cpy_r_r181, cpy_r_r181, cpy_r_r181};
    cpy_r_r183 = (PyObject **)&cpy_r_r182;
    cpy_r_r184 = _PyObject_Vectorcall(cpy_r_r134, cpy_r_r183, 4, 0);
    CPy_DECREF(cpy_r_r134);
    if (unlikely(cpy_r_r184 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 48, CPyStatic_globals);
        goto CPyL166;
    } else
        goto CPyL167;
CPyL94: ;
    CPy_DECREF(cpy_r_r131);
CPyL95: ;
    if (cpy_r_r179.f0 == NULL) goto CPyL110;
    CPy_Reraise();
    if (!0) {
        goto CPyL98;
    } else
        goto CPyL168;
CPyL97: ;
    CPy_Unreachable();
CPyL98: ;
    if (cpy_r_r179.f0 == NULL) goto CPyL100;
    CPy_RestoreExcInfo(cpy_r_r179);
    CPy_XDECREF(cpy_r_r179.f0);
    CPy_XDECREF(cpy_r_r179.f1);
    CPy_XDECREF(cpy_r_r179.f2);
CPyL100: ;
    cpy_r_r185 = CPy_KeepPropagating();
    if (!cpy_r_r185) {
        goto CPyL102;
    } else
        goto CPyL169;
CPyL101: ;
    CPy_Unreachable();
CPyL102: ;
    cpy_r_r186 = CPy_CatchError();
    cpy_r_r112 = 0;
    cpy_r_r187 = CPy_GetExcInfo();
    cpy_r_r188 = cpy_r_r187.f0;
    CPy_INCREF(cpy_r_r188);
    cpy_r_r189 = cpy_r_r187.f1;
    CPy_INCREF(cpy_r_r189);
    cpy_r_r190 = cpy_r_r187.f2;
    CPy_INCREF(cpy_r_r190);
    CPy_DECREF(cpy_r_r187.f0);
    CPy_DECREF(cpy_r_r187.f1);
    CPy_DECREF(cpy_r_r187.f2);
    PyObject *cpy_r_r191[4] = {cpy_r_r103, cpy_r_r188, cpy_r_r189, cpy_r_r190};
    cpy_r_r192 = (PyObject **)&cpy_r_r191;
    cpy_r_r193 = _PyObject_Vectorcall(cpy_r_r106, cpy_r_r192, 4, 0);
    if (unlikely(cpy_r_r193 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL170;
    }
    CPy_DECREF(cpy_r_r188);
    CPy_DECREF(cpy_r_r189);
    CPy_DECREF(cpy_r_r190);
    cpy_r_r194 = PyObject_IsTrue(cpy_r_r193);
    CPy_DECREF(cpy_r_r193);
    cpy_r_r195 = cpy_r_r194 >= 0;
    if (unlikely(!cpy_r_r195)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL108;
    }
    cpy_r_r196 = cpy_r_r194;
    if (cpy_r_r196) goto CPyL107;
    CPy_Reraise();
    if (!0) {
        goto CPyL108;
    } else
        goto CPyL171;
CPyL106: ;
    CPy_Unreachable();
CPyL107: ;
    CPy_RestoreExcInfo(cpy_r_r186);
    CPy_DECREF(cpy_r_r186.f0);
    CPy_DECREF(cpy_r_r186.f1);
    CPy_DECREF(cpy_r_r186.f2);
    goto CPyL110;
CPyL108: ;
    CPy_RestoreExcInfo(cpy_r_r186);
    CPy_DECREF(cpy_r_r186.f0);
    CPy_DECREF(cpy_r_r186.f1);
    CPy_DECREF(cpy_r_r186.f2);
    cpy_r_r197 = CPy_KeepPropagating();
    if (!cpy_r_r197) {
        goto CPyL111;
    } else
        goto CPyL172;
CPyL109: ;
    CPy_Unreachable();
CPyL110: ;
    tuple_T3OOO __tmp6 = { NULL, NULL, NULL };
    cpy_r_r198 = __tmp6;
    cpy_r_r199 = cpy_r_r198;
    goto CPyL112;
CPyL111: ;
    cpy_r_r200 = CPy_CatchError();
    cpy_r_r199 = cpy_r_r200;
CPyL112: ;
    if (!cpy_r_r112) goto CPyL173;
    cpy_r_r201 = (PyObject *)&_Py_NoneStruct;
    PyObject *cpy_r_r202[4] = {cpy_r_r103, cpy_r_r201, cpy_r_r201, cpy_r_r201};
    cpy_r_r203 = (PyObject **)&cpy_r_r202;
    cpy_r_r204 = _PyObject_Vectorcall(cpy_r_r106, cpy_r_r203, 4, 0);
    CPy_DECREF(cpy_r_r106);
    if (unlikely(cpy_r_r204 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_chunk", 46, CPyStatic_globals);
        goto CPyL174;
    } else
        goto CPyL175;
CPyL114: ;
    CPy_DECREF(cpy_r_r103);
CPyL115: ;
    if (cpy_r_r199.f0 == NULL) goto CPyL122;
    CPy_Reraise();
    if (!0) {
        goto CPyL118;
    } else
        goto CPyL176;
CPyL117: ;
    CPy_Unreachable();
CPyL118: ;
    if (cpy_r_r199.f0 == NULL) goto CPyL120;
    CPy_RestoreExcInfo(cpy_r_r199);
    CPy_XDECREF(cpy_r_r199.f0);
    CPy_XDECREF(cpy_r_r199.f1);
    CPy_XDECREF(cpy_r_r199.f2);
CPyL120: ;
    cpy_r_r205 = CPy_KeepPropagating();
    if (!cpy_r_r205) goto CPyL123;
    CPy_Unreachable();
CPyL122: ;
    return 1;
CPyL123: ;
    cpy_r_r206 = 2;
    return cpy_r_r206;
CPyL124: ;
    CPy_DecRef(cpy_r_r9);
    goto CPyL13;
CPyL125: ;
    CPy_DecRef(cpy_r_r18);
    goto CPyL13;
CPyL126: ;
    CPy_DECREF(cpy_r_r24);
    goto CPyL12;
CPyL127: ;
    CPy_DecRef(cpy_r_r5);
    goto CPyL18;
CPyL128: ;
    CPy_DecRef(cpy_r_r5);
    goto CPyL15;
CPyL129: ;
    CPy_DecRef(cpy_r_r25.f0);
    CPy_DecRef(cpy_r_r25.f1);
    CPy_DecRef(cpy_r_r25.f2);
    goto CPyL16;
CPyL130: ;
    CPy_DecRef(cpy_r_r34);
    goto CPyL29;
CPyL131: ;
    CPy_DecRef(cpy_r_r43);
    goto CPyL29;
CPyL132: ;
    CPy_DECREF(cpy_r_r49);
    goto CPyL28;
CPyL133: ;
    CPy_DecRef(cpy_r_r5);
    goto CPyL34;
CPyL134: ;
    CPy_DecRef(cpy_r_r5);
    goto CPyL31;
CPyL135: ;
    CPy_DecRef(cpy_r_r50.f0);
    CPy_DecRef(cpy_r_r50.f1);
    CPy_DecRef(cpy_r_r50.f2);
    goto CPyL32;
CPyL136: ;
    CPy_DecRef(cpy_r_r5);
    goto CPyL123;
CPyL137: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r59);
    goto CPyL123;
CPyL138: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r68);
    goto CPyL123;
CPyL139: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    goto CPyL123;
CPyL140: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r79);
    goto CPyL123;
CPyL141: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r88);
    goto CPyL123;
CPyL142: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    goto CPyL123;
CPyL143: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    goto CPyL123;
CPyL144: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r103);
    CPy_DecRef(cpy_r_r104);
    goto CPyL123;
CPyL145: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r103);
    CPy_DecRef(cpy_r_r106);
    goto CPyL123;
CPyL146: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r111);
    goto CPyL102;
CPyL147: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r111);
    CPy_DecRef(cpy_r_r113);
    goto CPyL102;
CPyL148: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r113);
    goto CPyL102;
CPyL149: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r113);
    CPyTagged_DecRef(cpy_r_r118);
    goto CPyL102;
CPyL150: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r113);
    CPyTagged_DecRef(cpy_r_r118);
    CPyTagged_DecRef(cpy_r_r122);
    goto CPyL102;
CPyL151: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r113);
    CPy_DecRef(cpy_r_r126);
    CPy_DecRef(cpy_r_r127);
    goto CPyL102;
CPyL152: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r131);
    CPy_DecRef(cpy_r_r132);
    goto CPyL102;
CPyL153: ;
    CPy_DecRef(cpy_r_r5);
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r131);
    CPy_DecRef(cpy_r_r134);
    goto CPyL102;
CPyL154: ;
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r139);
    goto CPyL82;
CPyL155: ;
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r139);
    CPy_DecRef(cpy_r_r141);
    goto CPyL82;
CPyL156: ;
    CPy_DECREF(cpy_r_r145);
    goto CPyL72;
CPyL157: ;
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_current_seq);
    goto CPyL82;
CPyL158: ;
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_current_seq);
    CPy_DecRef(cpy_r_r148);
    goto CPyL82;
CPyL159: ;
    CPy_DECREF(cpy_r_r75);
    CPy_DECREF(cpy_r_r95);
    CPy_DECREF(cpy_r_d);
    CPy_DECREF(cpy_r_current_seq);
    CPy_DECREF(cpy_r_r156);
    goto CPyL81;
CPyL160: ;
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_current_seq);
    CPy_DecRef(cpy_r_r156);
    goto CPyL82;
CPyL161: ;
    CPy_DecRef(cpy_r_r75);
    CPy_DecRef(cpy_r_r95);
    CPy_DecRef(cpy_r_r156);
    goto CPyL82;
CPyL162: ;
    CPy_DecRef(cpy_r_r168);
    CPy_DecRef(cpy_r_r169);
    CPy_DecRef(cpy_r_r170);
    goto CPyL88;
CPyL163: ;
    CPy_DecRef(cpy_r_r103);
    CPy_DecRef(cpy_r_r106);
    CPy_DecRef(cpy_r_r131);
    CPy_DecRef(cpy_r_r134);
    CPy_DecRef(cpy_r_r166.f0);
    CPy_DecRef(cpy_r_r166.f1);
    CPy_DecRef(cpy_r_r166.f2);
    goto CPyL86;
CPyL164: ;
    CPy_DecRef(cpy_r_r103);
    CPy_DecRef(cpy_r_r106);
    CPy_DecRef(cpy_r_r131);
    CPy_DecRef(cpy_r_r134);
    goto CPyL89;
CPyL165: ;
    CPy_DECREF(cpy_r_r131);
    CPy_DECREF(cpy_r_r134);
    goto CPyL95;
CPyL166: ;
    CPy_DecRef(cpy_r_r131);
    goto CPyL98;
CPyL167: ;
    CPy_DECREF(cpy_r_r184);
    goto CPyL94;
CPyL168: ;
    CPy_DECREF(cpy_r_r103);
    CPy_DECREF(cpy_r_r106);
    CPy_XDECREF(cpy_r_r179.f0);
    CPy_XDECREF(cpy_r_r179.f1);
    CPy_XDECREF(cpy_r_r179.f2);
    goto CPyL97;
CPyL169: ;
    CPy_DECREF(cpy_r_r103);
    CPy_DECREF(cpy_r_r106);
    goto CPyL101;
CPyL170: ;
    CPy_DecRef(cpy_r_r188);
    CPy_DecRef(cpy_r_r189);
    CPy_DecRef(cpy_r_r190);
    goto CPyL108;
CPyL171: ;
    CPy_DECREF(cpy_r_r103);
    CPy_DECREF(cpy_r_r106);
    CPy_DECREF(cpy_r_r186.f0);
    CPy_DECREF(cpy_r_r186.f1);
    CPy_DECREF(cpy_r_r186.f2);
    goto CPyL106;
CPyL172: ;
    CPy_DECREF(cpy_r_r103);
    CPy_DECREF(cpy_r_r106);
    goto CPyL109;
CPyL173: ;
    CPy_DECREF(cpy_r_r103);
    CPy_DECREF(cpy_r_r106);
    goto CPyL115;
CPyL174: ;
    CPy_DecRef(cpy_r_r103);
    goto CPyL118;
CPyL175: ;
    CPy_DECREF(cpy_r_r204);
    goto CPyL114;
CPyL176: ;
    CPy_XDECREF(cpy_r_r199.f0);
    CPy_XDECREF(cpy_r_r199.f1);
    CPy_XDECREF(cpy_r_r199.f2);
    goto CPyL117;
}

PyObject *CPyPy_process_chunk(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"file_path", "start_byte", "end_byte", "file_counter", "output", 0};
    static CPyArg_Parser parser = {"OOOOO:process_chunk", kwlist, 0};
    PyObject *obj_file_path;
    PyObject *obj_start_byte;
    PyObject *obj_end_byte;
    PyObject *obj_file_counter;
    PyObject *obj_output;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_file_path, &obj_start_byte, &obj_end_byte, &obj_file_counter, &obj_output)) {
        return NULL;
    }
    PyObject *arg_file_path;
    if (likely(PyUnicode_Check(obj_file_path)))
        arg_file_path = obj_file_path;
    else {
        CPy_TypeError("str", obj_file_path); 
        goto fail;
    }
    PyObject *arg_start_byte = obj_start_byte;
    PyObject *arg_end_byte = obj_end_byte;
    CPyTagged arg_file_counter;
    if (likely(PyLong_Check(obj_file_counter)))
        arg_file_counter = CPyTagged_BorrowFromObject(obj_file_counter);
    else {
        CPy_TypeError("int", obj_file_counter); goto fail;
    }
    PyObject *arg_output;
    if (likely(PyUnicode_Check(obj_output)))
        arg_output = obj_output;
    else {
        CPy_TypeError("str", obj_output); 
        goto fail;
    }
    char retval = CPyDef_process_chunk(arg_file_path, arg_start_byte, arg_end_byte, arg_file_counter, arg_output);
    if (retval == 2) {
        return NULL;
    }
    PyObject *retbox = Py_None;
    CPy_INCREF(retbox);
    return retbox;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "process_chunk", 31, CPyStatic_globals);
    return NULL;
}

tuple_T3IOO CPyDef_process_line_no_write(PyObject *cpy_r_line) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    int32_t cpy_r_r2;
    char cpy_r_r3;
    PyObject *cpy_r_r4;
    char cpy_r_r5;
    char cpy_r_r6;
    char cpy_r_r7;
    PyObject *cpy_r_r8;
    PyObject *cpy_r_r9;
    int32_t cpy_r_r10;
    char cpy_r_r11;
    PyObject *cpy_r_r12;
    char cpy_r_r13;
    char cpy_r_r14;
    char cpy_r_r15;
    PyObject *cpy_r_r16;
    PyObject *cpy_r_r17;
    tuple_T3IOO cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    int32_t cpy_r_r21;
    char cpy_r_r22;
    PyObject *cpy_r_r23;
    char cpy_r_r24;
    char cpy_r_r25;
    char cpy_r_r26;
    PyObject *cpy_r_r27;
    tuple_T3IOO cpy_r_r28;
    PyObject *cpy_r_r29;
    PyObject **cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    PyObject *cpy_r_r34;
    PyObject *cpy_r_r35;
    PyObject *cpy_r_r36;
    PyObject *cpy_r_protein;
    PyObject *cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    PyObject *cpy_r_r40;
    PyObject *cpy_r_r41;
    PyObject *cpy_r_r42;
    tuple_T3IOO cpy_r_r43;
    tuple_T3IOO cpy_r_r44;
    cpy_r_r0 = CPyStr_GetItem(cpy_r_line, 0);
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 58, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r1 = CPyStatics[3]; /* '\n' */
    cpy_r_r2 = PyUnicode_Compare(cpy_r_r0, cpy_r_r1);
    CPy_DECREF(cpy_r_r0);
    cpy_r_r3 = cpy_r_r2 == -1;
    if (!cpy_r_r3) goto CPyL4;
    cpy_r_r4 = PyErr_Occurred();
    cpy_r_r5 = cpy_r_r4 != NULL;
    if (!cpy_r_r5) goto CPyL4;
    cpy_r_r6 = CPy_KeepPropagating();
    if (unlikely(!cpy_r_r6)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 58, CPyStatic_globals);
        goto CPyL25;
    }
CPyL4: ;
    cpy_r_r7 = cpy_r_r2 == 0;
    if (cpy_r_r7) goto CPyL10;
    cpy_r_r8 = CPyStr_GetItem(cpy_r_line, 0);
    if (unlikely(cpy_r_r8 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 58, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r9 = CPyStatics[33]; /* '\r' */
    cpy_r_r10 = PyUnicode_Compare(cpy_r_r8, cpy_r_r9);
    CPy_DECREF(cpy_r_r8);
    cpy_r_r11 = cpy_r_r10 == -1;
    if (!cpy_r_r11) goto CPyL9;
    cpy_r_r12 = PyErr_Occurred();
    cpy_r_r13 = cpy_r_r12 != NULL;
    if (!cpy_r_r13) goto CPyL9;
    cpy_r_r14 = CPy_KeepPropagating();
    if (unlikely(!cpy_r_r14)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 58, CPyStatic_globals);
        goto CPyL25;
    }
CPyL9: ;
    cpy_r_r15 = cpy_r_r10 == 0;
    if (!cpy_r_r15) goto CPyL11;
CPyL10: ;
    cpy_r_r16 = CPyStatics[3]; /* '\n' */
    cpy_r_r17 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_r16);
    CPy_INCREF(cpy_r_r17);
    cpy_r_r18.f0 = 0;
    cpy_r_r18.f1 = cpy_r_r16;
    cpy_r_r18.f2 = cpy_r_r17;
    return cpy_r_r18;
CPyL11: ;
    cpy_r_r19 = CPyStr_GetItem(cpy_r_line, 0);
    if (unlikely(cpy_r_r19 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 60, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r20 = CPyStatics[34]; /* '>' */
    cpy_r_r21 = PyUnicode_Compare(cpy_r_r19, cpy_r_r20);
    CPy_DECREF(cpy_r_r19);
    cpy_r_r22 = cpy_r_r21 == -1;
    if (!cpy_r_r22) goto CPyL15;
    cpy_r_r23 = PyErr_Occurred();
    cpy_r_r24 = cpy_r_r23 != NULL;
    if (!cpy_r_r24) goto CPyL15;
    cpy_r_r25 = CPy_KeepPropagating();
    if (unlikely(!cpy_r_r25)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 60, CPyStatic_globals);
        goto CPyL25;
    }
CPyL15: ;
    cpy_r_r26 = cpy_r_r21 != 0;
    if (!cpy_r_r26) goto CPyL17;
    cpy_r_r27 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_line);
    CPy_INCREF(cpy_r_r27);
    cpy_r_r28.f0 = 2;
    cpy_r_r28.f1 = cpy_r_line;
    cpy_r_r28.f2 = cpy_r_r27;
    return cpy_r_r28;
CPyL17: ;
    cpy_r_r29 = CPyStatics[7]; /* 'rstrip' */
    PyObject *cpy_r_r30[1] = {cpy_r_line};
    cpy_r_r31 = (PyObject **)&cpy_r_r30;
    cpy_r_r32 = PyObject_VectorcallMethod(cpy_r_r29, cpy_r_r31, 9223372036854775809ULL, 0);
    if (unlikely(cpy_r_r32 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 62, CPyStatic_globals);
        goto CPyL25;
    }
    if (likely(PyUnicode_Check(cpy_r_r32)))
        cpy_r_r33 = cpy_r_r32;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_line_no_write", 62, CPyStatic_globals, "str", cpy_r_r32);
        goto CPyL25;
    }
    cpy_r_r34 = CPyStatics[10]; /* ' ' */
    cpy_r_r35 = CPyStatics[35]; /* '*' */
    cpy_r_r36 = PyUnicode_Replace(cpy_r_r33, cpy_r_r34, cpy_r_r35, -1);
    CPy_DECREF(cpy_r_r33);
    if (unlikely(cpy_r_r36 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 62, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_line = cpy_r_r36;
    CPy_INCREF(cpy_r_line);
    cpy_r_protein = cpy_r_line;
    cpy_r_r37 = CPyStatics[36]; /* '[' */
    cpy_r_r38 = PyUnicode_Split(cpy_r_line, cpy_r_r37, -1);
    CPy_DECREF(cpy_r_line);
    if (unlikely(cpy_r_r38 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 65, CPyStatic_globals);
        goto CPyL26;
    }
    cpy_r_r39 = CPyList_GetSlice(cpy_r_r38, 2, 9223372036854775806LL);
    CPy_DECREF(cpy_r_r38);
    if (unlikely(cpy_r_r39 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 66, CPyStatic_globals);
        goto CPyL26;
    }
    if (likely(PyList_Check(cpy_r_r39)))
        cpy_r_r40 = cpy_r_r39;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_line_no_write", 66, CPyStatic_globals, "list", cpy_r_r39);
        goto CPyL26;
    }
    cpy_r_r41 = CPyStatics[4]; /* '' */
    cpy_r_r42 = PyUnicode_Join(cpy_r_r41, cpy_r_r40);
    CPy_DECREF(cpy_r_r40);
    if (unlikely(cpy_r_r42 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 68, CPyStatic_globals);
        goto CPyL26;
    }
    cpy_r_r43.f0 = 4;
    cpy_r_r43.f1 = cpy_r_protein;
    cpy_r_r43.f2 = cpy_r_r42;
    return cpy_r_r43;
CPyL25: ;
    tuple_T3IOO __tmp7 = { CPY_INT_TAG, NULL, NULL };
    cpy_r_r44 = __tmp7;
    return cpy_r_r44;
CPyL26: ;
    CPy_DecRef(cpy_r_protein);
    goto CPyL25;
}

PyObject *CPyPy_process_line_no_write(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"line", 0};
    static CPyArg_Parser parser = {"O:process_line_no_write", kwlist, 0};
    PyObject *obj_line;
    if (!CPyArg_ParseStackAndKeywordsOneArg(args, nargs, kwnames, &parser, &obj_line)) {
        return NULL;
    }
    PyObject *arg_line;
    if (likely(PyUnicode_Check(obj_line)))
        arg_line = obj_line;
    else {
        CPy_TypeError("str", obj_line); 
        goto fail;
    }
    tuple_T3IOO retval = CPyDef_process_line_no_write(arg_line);
    if (retval.f0 == CPY_INT_TAG) {
        return NULL;
    }
    PyObject *retbox = PyTuple_New(3);
    if (unlikely(retbox == NULL))
        CPyError_OutOfMemory();
    PyObject *__tmp8 = CPyTagged_StealAsObject(retval.f0);
    PyTuple_SET_ITEM(retbox, 0, __tmp8);
    PyObject *__tmp9 = retval.f1;
    PyTuple_SET_ITEM(retbox, 1, __tmp9);
    PyObject *__tmp10 = retval.f2;
    PyTuple_SET_ITEM(retbox, 2, __tmp10);
    return retbox;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "process_line_no_write", 57, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_process_whole_file(PyObject *cpy_r_file_path) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_d;
    PyObject *cpy_r_r1;
    PyObject *cpy_r_current_seq;
    PyObject *cpy_r_r2;
    PyObject *cpy_r_r3;
    PyObject *cpy_r_r4;
    PyObject *cpy_r_r5;
    PyObject **cpy_r_r7;
    PyObject *cpy_r_r8;
    PyObject *cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_r11;
    PyObject *cpy_r_r12;
    PyObject *cpy_r_r13;
    PyObject **cpy_r_r15;
    PyObject *cpy_r_r16;
    char cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    tuple_T3IOO cpy_r_r21;
    tuple_T2OO cpy_r_r22;
    PyObject *cpy_r_r23;
    PyObject *cpy_r_r24;
    PyObject *cpy_r_r25;
    PyObject *cpy_r_r26;
    char cpy_r_r27;
    tuple_T3OOO cpy_r_r28;
    tuple_T3OOO cpy_r_r29;
    PyObject *cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject **cpy_r_r34;
    PyObject *cpy_r_r35;
    int32_t cpy_r_r36;
    char cpy_r_r37;
    char cpy_r_r38;
    char cpy_r_r39;
    tuple_T3OOO cpy_r_r40;
    tuple_T3OOO cpy_r_r41;
    tuple_T3OOO cpy_r_r42;
    PyObject *cpy_r_r43;
    PyObject **cpy_r_r45;
    PyObject *cpy_r_r46;
    char cpy_r_r47;
    PyObject *cpy_r_r48;
    cpy_r_r0 = PyDict_New();
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 72, CPyStatic_globals);
        goto CPyL35;
    }
    cpy_r_d = cpy_r_r0;
    cpy_r_r1 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_r1);
    cpy_r_current_seq = cpy_r_r1;
    cpy_r_r2 = CPyStatics[37]; /* 'r' */
    cpy_r_r3 = CPyModule_builtins;
    cpy_r_r4 = CPyStatics[21]; /* 'open' */
    cpy_r_r5 = CPyObject_GetAttr(cpy_r_r3, cpy_r_r4);
    if (unlikely(cpy_r_r5 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL36;
    }
    PyObject *cpy_r_r6[2] = {cpy_r_file_path, cpy_r_r2};
    cpy_r_r7 = (PyObject **)&cpy_r_r6;
    cpy_r_r8 = _PyObject_Vectorcall(cpy_r_r5, cpy_r_r7, 2, 0);
    CPy_DECREF(cpy_r_r5);
    if (unlikely(cpy_r_r8 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL36;
    }
    cpy_r_r9 = PyObject_Type(cpy_r_r8);
    cpy_r_r10 = CPyStatics[23]; /* '__exit__' */
    cpy_r_r11 = CPyObject_GetAttr(cpy_r_r9, cpy_r_r10);
    if (unlikely(cpy_r_r11 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL37;
    }
    cpy_r_r12 = CPyStatics[24]; /* '__enter__' */
    cpy_r_r13 = CPyObject_GetAttr(cpy_r_r9, cpy_r_r12);
    CPy_DECREF(cpy_r_r9);
    if (unlikely(cpy_r_r13 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL38;
    }
    PyObject *cpy_r_r14[1] = {cpy_r_r8};
    cpy_r_r15 = (PyObject **)&cpy_r_r14;
    cpy_r_r16 = _PyObject_Vectorcall(cpy_r_r13, cpy_r_r15, 1, 0);
    CPy_DECREF(cpy_r_r13);
    if (unlikely(cpy_r_r16 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL38;
    }
    cpy_r_r17 = 1;
    cpy_r_r18 = PyObject_GetIter(cpy_r_r16);
    CPy_DECREF(cpy_r_r16);
    if (unlikely(cpy_r_r18 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 75, CPyStatic_globals);
        goto CPyL39;
    }
CPyL8: ;
    cpy_r_r19 = PyIter_Next(cpy_r_r18);
    if (cpy_r_r19 == NULL) goto CPyL40;
    if (likely(PyUnicode_Check(cpy_r_r19)))
        cpy_r_r20 = cpy_r_r19;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_whole_file", 75, CPyStatic_globals, "str", cpy_r_r19);
        goto CPyL41;
    }
    cpy_r_r21 = CPyDef_process_line_no_write(cpy_r_r20);
    CPy_DECREF(cpy_r_r20);
    if (unlikely(cpy_r_r21.f0 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 76, CPyStatic_globals);
        goto CPyL41;
    }
    cpy_r_r22 = CPyDef_process_genome(cpy_r_d, cpy_r_current_seq, cpy_r_r21);
    CPy_DECREF(cpy_r_current_seq);
    CPyTagged_DECREF(cpy_r_r21.f0);
    CPy_DECREF(cpy_r_r21.f1);
    CPy_DECREF(cpy_r_r21.f2);
    if (unlikely(cpy_r_r22.f0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 77, CPyStatic_globals);
        goto CPyL42;
    } else
        goto CPyL43;
CPyL12: ;
    cpy_r_r23 = cpy_r_r22.f0;
    cpy_r_r24 = cpy_r_r23;
    cpy_r_d = cpy_r_r24;
    cpy_r_r25 = cpy_r_r22.f1;
    cpy_r_r26 = cpy_r_r25;
    cpy_r_current_seq = cpy_r_r26;
    goto CPyL8;
CPyL13: ;
    cpy_r_r27 = CPy_NoErrOccured();
    if (unlikely(!cpy_r_r27)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 75, CPyStatic_globals);
    } else
        goto CPyL22;
CPyL14: ;
    cpy_r_r28 = CPy_CatchError();
    cpy_r_r17 = 0;
    cpy_r_r29 = CPy_GetExcInfo();
    cpy_r_r30 = cpy_r_r29.f0;
    CPy_INCREF(cpy_r_r30);
    cpy_r_r31 = cpy_r_r29.f1;
    CPy_INCREF(cpy_r_r31);
    cpy_r_r32 = cpy_r_r29.f2;
    CPy_INCREF(cpy_r_r32);
    CPy_DecRef(cpy_r_r29.f0);
    CPy_DecRef(cpy_r_r29.f1);
    CPy_DecRef(cpy_r_r29.f2);
    PyObject *cpy_r_r33[4] = {cpy_r_r8, cpy_r_r30, cpy_r_r31, cpy_r_r32};
    cpy_r_r34 = (PyObject **)&cpy_r_r33;
    cpy_r_r35 = _PyObject_Vectorcall(cpy_r_r11, cpy_r_r34, 4, 0);
    if (unlikely(cpy_r_r35 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL44;
    }
    CPy_DecRef(cpy_r_r30);
    CPy_DecRef(cpy_r_r31);
    CPy_DecRef(cpy_r_r32);
    cpy_r_r36 = PyObject_IsTrue(cpy_r_r35);
    CPy_DecRef(cpy_r_r35);
    cpy_r_r37 = cpy_r_r36 >= 0;
    if (unlikely(!cpy_r_r37)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL20;
    }
    cpy_r_r38 = cpy_r_r36;
    if (cpy_r_r38) goto CPyL19;
    CPy_Reraise();
    if (!0) {
        goto CPyL20;
    } else
        goto CPyL45;
CPyL18: ;
    CPy_Unreachable();
CPyL19: ;
    CPy_RestoreExcInfo(cpy_r_r28);
    CPy_DecRef(cpy_r_r28.f0);
    CPy_DecRef(cpy_r_r28.f1);
    CPy_DecRef(cpy_r_r28.f2);
    goto CPyL22;
CPyL20: ;
    CPy_RestoreExcInfo(cpy_r_r28);
    CPy_DecRef(cpy_r_r28.f0);
    CPy_DecRef(cpy_r_r28.f1);
    CPy_DecRef(cpy_r_r28.f2);
    cpy_r_r39 = CPy_KeepPropagating();
    if (!cpy_r_r39) {
        goto CPyL23;
    } else
        goto CPyL46;
CPyL21: ;
    CPy_Unreachable();
CPyL22: ;
    tuple_T3OOO __tmp11 = { NULL, NULL, NULL };
    cpy_r_r40 = __tmp11;
    cpy_r_r41 = cpy_r_r40;
    goto CPyL24;
CPyL23: ;
    cpy_r_r42 = CPy_CatchError();
    cpy_r_r41 = cpy_r_r42;
CPyL24: ;
    if (!cpy_r_r17) goto CPyL47;
    cpy_r_r43 = (PyObject *)&_Py_NoneStruct;
    PyObject *cpy_r_r44[4] = {cpy_r_r8, cpy_r_r43, cpy_r_r43, cpy_r_r43};
    cpy_r_r45 = (PyObject **)&cpy_r_r44;
    cpy_r_r46 = _PyObject_Vectorcall(cpy_r_r11, cpy_r_r45, 4, 0);
    CPy_DECREF(cpy_r_r11);
    if (unlikely(cpy_r_r46 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 74, CPyStatic_globals);
        goto CPyL48;
    } else
        goto CPyL49;
CPyL26: ;
    CPy_DECREF(cpy_r_r8);
CPyL27: ;
    if (cpy_r_r41.f0 == NULL) {
        goto CPyL34;
    } else
        goto CPyL50;
CPyL28: ;
    CPy_Reraise();
    if (!0) {
        goto CPyL30;
    } else
        goto CPyL51;
CPyL29: ;
    CPy_Unreachable();
CPyL30: ;
    if (cpy_r_r41.f0 == NULL) goto CPyL32;
    CPy_RestoreExcInfo(cpy_r_r41);
    CPy_XDECREF(cpy_r_r41.f0);
    CPy_XDECREF(cpy_r_r41.f1);
    CPy_XDECREF(cpy_r_r41.f2);
CPyL32: ;
    cpy_r_r47 = CPy_KeepPropagating();
    if (!cpy_r_r47) goto CPyL35;
    CPy_Unreachable();
CPyL34: ;
    return cpy_r_d;
CPyL35: ;
    cpy_r_r48 = NULL;
    return cpy_r_r48;
CPyL36: ;
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_current_seq);
    goto CPyL35;
CPyL37: ;
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_current_seq);
    CPy_DecRef(cpy_r_r8);
    CPy_DecRef(cpy_r_r9);
    goto CPyL35;
CPyL38: ;
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_current_seq);
    CPy_DecRef(cpy_r_r8);
    CPy_DecRef(cpy_r_r11);
    goto CPyL35;
CPyL39: ;
    CPy_DecRef(cpy_r_current_seq);
    goto CPyL14;
CPyL40: ;
    CPy_DECREF(cpy_r_current_seq);
    CPy_DECREF(cpy_r_r18);
    goto CPyL13;
CPyL41: ;
    CPy_DecRef(cpy_r_current_seq);
    CPy_DecRef(cpy_r_r18);
    goto CPyL14;
CPyL42: ;
    CPy_DecRef(cpy_r_r18);
    goto CPyL14;
CPyL43: ;
    CPy_DECREF(cpy_r_d);
    goto CPyL12;
CPyL44: ;
    CPy_DecRef(cpy_r_r30);
    CPy_DecRef(cpy_r_r31);
    CPy_DecRef(cpy_r_r32);
    goto CPyL20;
CPyL45: ;
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r8);
    CPy_DecRef(cpy_r_r11);
    CPy_DecRef(cpy_r_r28.f0);
    CPy_DecRef(cpy_r_r28.f1);
    CPy_DecRef(cpy_r_r28.f2);
    goto CPyL18;
CPyL46: ;
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r8);
    CPy_DecRef(cpy_r_r11);
    goto CPyL21;
CPyL47: ;
    CPy_DECREF(cpy_r_r8);
    CPy_DECREF(cpy_r_r11);
    goto CPyL27;
CPyL48: ;
    CPy_DecRef(cpy_r_d);
    CPy_DecRef(cpy_r_r8);
    goto CPyL30;
CPyL49: ;
    CPy_DECREF(cpy_r_r46);
    goto CPyL26;
CPyL50: ;
    CPy_DECREF(cpy_r_d);
    goto CPyL28;
CPyL51: ;
    CPy_XDECREF(cpy_r_r41.f0);
    CPy_XDECREF(cpy_r_r41.f1);
    CPy_XDECREF(cpy_r_r41.f2);
    goto CPyL29;
}

PyObject *CPyPy_process_whole_file(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"file_path", 0};
    static CPyArg_Parser parser = {"O:process_whole_file", kwlist, 0};
    PyObject *obj_file_path;
    if (!CPyArg_ParseStackAndKeywordsOneArg(args, nargs, kwnames, &parser, &obj_file_path)) {
        return NULL;
    }
    PyObject *arg_file_path;
    if (likely(PyUnicode_Check(obj_file_path)))
        arg_file_path = obj_file_path;
    else {
        CPy_TypeError("str", obj_file_path); 
        goto fail;
    }
    PyObject *retval = CPyDef_process_whole_file(arg_file_path);
    return retval;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "process_whole_file", 71, CPyStatic_globals);
    return NULL;
}

tuple_T2OO CPyDef_process_genome(PyObject *cpy_r_d, PyObject *cpy_r_seq, tuple_T3IOO cpy_r_line) {
    CPyTagged cpy_r_r0;
    char cpy_r_r1;
    tuple_T2OO cpy_r_r2;
    CPyTagged cpy_r_r3;
    char cpy_r_r4;
    PyObject *cpy_r_r5;
    PyObject *cpy_r_r6;
    PyObject *cpy_r_r7;
    PyObject *cpy_r_r8;
    tuple_T2OO cpy_r_r9;
    CPyTagged cpy_r_r10;
    char cpy_r_r11;
    PyObject *cpy_r_r12;
    int32_t cpy_r_r13;
    char cpy_r_r14;
    char cpy_r_r15;
    PyObject *cpy_r_r16;
    PyObject *cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject *cpy_r_r21;
    int32_t cpy_r_r22;
    char cpy_r_r23;
    PyObject *cpy_r_r24;
    PyObject *cpy_r_r25;
    PyObject *cpy_r_r26;
    PyObject *cpy_r_r27;
    PyObject *cpy_r_r28;
    int32_t cpy_r_r29;
    char cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    CPyPtr cpy_r_r33;
    CPyPtr cpy_r_r34;
    PyObject *cpy_r_r35;
    PyObject *cpy_r_r36;
    CPyPtr cpy_r_r37;
    CPyPtr cpy_r_r38;
    CPyPtr cpy_r_r39;
    PyObject *cpy_r_r40;
    int32_t cpy_r_r41;
    char cpy_r_r42;
    PyObject *cpy_r_r43;
    tuple_T2OO cpy_r_r44;
    tuple_T2OO cpy_r_r45;
    cpy_r_r0 = cpy_r_line.f0;
    CPyTagged_INCREF(cpy_r_r0);
    cpy_r_r1 = cpy_r_r0 == 0;
    CPyTagged_DECREF(cpy_r_r0);
    if (!cpy_r_r1) goto CPyL2;
    CPy_INCREF(cpy_r_d);
    CPy_INCREF(cpy_r_seq);
    cpy_r_r2.f0 = cpy_r_d;
    cpy_r_r2.f1 = cpy_r_seq;
    return cpy_r_r2;
CPyL2: ;
    cpy_r_r3 = cpy_r_line.f0;
    CPyTagged_INCREF(cpy_r_r3);
    cpy_r_r4 = cpy_r_r3 == 2;
    CPyTagged_DECREF(cpy_r_r3);
    if (!cpy_r_r4) goto CPyL6;
    cpy_r_r5 = cpy_r_line.f1;
    CPy_INCREF(cpy_r_r5);
    cpy_r_r6 = CPyStatics[3]; /* '\n' */
    cpy_r_r7 = CPyStr_Build(2, cpy_r_r5, cpy_r_r6);
    CPy_DECREF(cpy_r_r5);
    if (unlikely(cpy_r_r7 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 84, CPyStatic_globals);
        goto CPyL25;
    }
    CPy_INCREF(cpy_r_seq);
    cpy_r_r8 = CPyStr_Append(cpy_r_seq, cpy_r_r7);
    CPy_DECREF(cpy_r_r7);
    if (unlikely(cpy_r_r8 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 84, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_seq = cpy_r_r8;
    CPy_INCREF(cpy_r_d);
    cpy_r_r9.f0 = cpy_r_d;
    cpy_r_r9.f1 = cpy_r_seq;
    return cpy_r_r9;
CPyL6: ;
    cpy_r_r10 = cpy_r_line.f0;
    CPyTagged_INCREF(cpy_r_r10);
    cpy_r_r11 = cpy_r_r10 == 4;
    CPyTagged_DECREF(cpy_r_r10);
    if (!cpy_r_r11) goto CPyL26;
    cpy_r_r12 = cpy_r_line.f2;
    CPy_INCREF(cpy_r_r12);
    cpy_r_r13 = PyDict_Contains(cpy_r_d, cpy_r_r12);
    CPy_DECREF(cpy_r_r12);
    cpy_r_r14 = cpy_r_r13 >= 0;
    if (unlikely(!cpy_r_r14)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 87, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r15 = cpy_r_r13;
    if (!cpy_r_r15) goto CPyL19;
    cpy_r_r16 = cpy_r_line.f2;
    CPy_INCREF(cpy_r_r16);
    cpy_r_r17 = CPyDict_GetItem(cpy_r_d, cpy_r_r16);
    CPy_DECREF(cpy_r_r16);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 88, CPyStatic_globals);
        goto CPyL25;
    }
    if (likely(PyList_Check(cpy_r_r17)))
        cpy_r_r18 = cpy_r_r17;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_genome", 88, CPyStatic_globals, "list", cpy_r_r17);
        goto CPyL25;
    }
    cpy_r_r19 = CPyList_GetItemShort(cpy_r_r18, 0);
    CPy_DECREF(cpy_r_r18);
    if (unlikely(cpy_r_r19 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 88, CPyStatic_globals);
        goto CPyL25;
    }
    if (likely(PyList_Check(cpy_r_r19)))
        cpy_r_r20 = cpy_r_r19;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_genome", 88, CPyStatic_globals, "list", cpy_r_r19);
        goto CPyL25;
    }
    cpy_r_r21 = cpy_r_line.f1;
    CPy_INCREF(cpy_r_r21);
    cpy_r_r22 = PyList_Append(cpy_r_r20, cpy_r_r21);
    CPy_DECREF(cpy_r_r20);
    CPy_DECREF(cpy_r_r21);
    cpy_r_r23 = cpy_r_r22 >= 0;
    if (unlikely(!cpy_r_r23)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 88, CPyStatic_globals);
        goto CPyL25;
    }
    cpy_r_r24 = cpy_r_line.f2;
    CPy_INCREF(cpy_r_r24);
    cpy_r_r25 = CPyDict_GetItem(cpy_r_d, cpy_r_r24);
    CPy_DECREF(cpy_r_r24);
    if (unlikely(cpy_r_r25 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 89, CPyStatic_globals);
        goto CPyL25;
    }
    if (likely(PyList_Check(cpy_r_r25)))
        cpy_r_r26 = cpy_r_r25;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_genome", 89, CPyStatic_globals, "list", cpy_r_r25);
        goto CPyL25;
    }
    cpy_r_r27 = CPyList_GetItemShort(cpy_r_r26, 2);
    CPy_DECREF(cpy_r_r26);
    if (unlikely(cpy_r_r27 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 89, CPyStatic_globals);
        goto CPyL25;
    }
    if (likely(PyList_Check(cpy_r_r27)))
        cpy_r_r28 = cpy_r_r27;
    else {
        CPy_TypeErrorTraceback("process_fasta_input.py", "process_genome", 89, CPyStatic_globals, "list", cpy_r_r27);
        goto CPyL25;
    }
    cpy_r_r29 = PyList_Append(cpy_r_r28, cpy_r_seq);
    CPy_DECREF(cpy_r_r28);
    cpy_r_r30 = cpy_r_r29 >= 0;
    if (unlikely(!cpy_r_r30)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 89, CPyStatic_globals);
        goto CPyL25;
    } else
        goto CPyL23;
CPyL19: ;
    cpy_r_r31 = cpy_r_line.f1;
    CPy_INCREF(cpy_r_r31);
    cpy_r_r32 = PyList_New(1);
    if (unlikely(cpy_r_r32 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 92, CPyStatic_globals);
        goto CPyL27;
    }
    cpy_r_r33 = (CPyPtr)&((PyListObject *)cpy_r_r32)->ob_item;
    cpy_r_r34 = *(CPyPtr *)cpy_r_r33;
    *(PyObject * *)cpy_r_r34 = cpy_r_r31;
    cpy_r_r35 = PyList_New(0);
    if (unlikely(cpy_r_r35 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 92, CPyStatic_globals);
        goto CPyL28;
    }
    cpy_r_r36 = PyList_New(2);
    if (unlikely(cpy_r_r36 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 92, CPyStatic_globals);
        goto CPyL29;
    }
    cpy_r_r37 = (CPyPtr)&((PyListObject *)cpy_r_r36)->ob_item;
    cpy_r_r38 = *(CPyPtr *)cpy_r_r37;
    *(PyObject * *)cpy_r_r38 = cpy_r_r32;
    cpy_r_r39 = cpy_r_r38 + 8;
    *(PyObject * *)cpy_r_r39 = cpy_r_r35;
    cpy_r_r40 = cpy_r_line.f2;
    CPy_INCREF(cpy_r_r40);
    cpy_r_r41 = CPyDict_SetItem(cpy_r_d, cpy_r_r40, cpy_r_r36);
    CPy_DECREF(cpy_r_r40);
    CPy_DECREF(cpy_r_r36);
    cpy_r_r42 = cpy_r_r41 >= 0;
    if (unlikely(!cpy_r_r42)) {
        CPy_AddTraceback("process_fasta_input.py", "process_genome", 92, CPyStatic_globals);
        goto CPyL25;
    }
CPyL23: ;
    cpy_r_r43 = CPyStatics[4]; /* '' */
    CPy_INCREF(cpy_r_r43);
    cpy_r_seq = cpy_r_r43;
CPyL24: ;
    CPy_INCREF(cpy_r_d);
    cpy_r_r44.f0 = cpy_r_d;
    cpy_r_r44.f1 = cpy_r_seq;
    return cpy_r_r44;
CPyL25: ;
    tuple_T2OO __tmp12 = { NULL, NULL };
    cpy_r_r45 = __tmp12;
    return cpy_r_r45;
CPyL26: ;
    CPy_INCREF(cpy_r_seq);
    goto CPyL24;
CPyL27: ;
    CPy_DecRef(cpy_r_r31);
    goto CPyL25;
CPyL28: ;
    CPy_DecRef(cpy_r_r32);
    goto CPyL25;
CPyL29: ;
    CPy_DecRef(cpy_r_r32);
    CPy_DecRef(cpy_r_r35);
    goto CPyL25;
}

PyObject *CPyPy_process_genome(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"d", "seq", "line", 0};
    static CPyArg_Parser parser = {"OOO:process_genome", kwlist, 0};
    PyObject *obj_d;
    PyObject *obj_seq;
    PyObject *obj_line;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_d, &obj_seq, &obj_line)) {
        return NULL;
    }
    PyObject *arg_d;
    if (likely(PyDict_Check(obj_d)))
        arg_d = obj_d;
    else {
        CPy_TypeError("dict", obj_d); 
        goto fail;
    }
    PyObject *arg_seq;
    if (likely(PyUnicode_Check(obj_seq)))
        arg_seq = obj_seq;
    else {
        CPy_TypeError("str", obj_seq); 
        goto fail;
    }
    tuple_T3IOO arg_line;
    PyObject *__tmp13;
    if (unlikely(!(PyTuple_Check(obj_line) && PyTuple_GET_SIZE(obj_line) == 3))) {
        __tmp13 = NULL;
        goto __LL14;
    }
    if (likely(PyLong_Check(PyTuple_GET_ITEM(obj_line, 0))))
        __tmp13 = PyTuple_GET_ITEM(obj_line, 0);
    else {
        __tmp13 = NULL;
    }
    if (__tmp13 == NULL) goto __LL14;
    if (likely(PyUnicode_Check(PyTuple_GET_ITEM(obj_line, 1))))
        __tmp13 = PyTuple_GET_ITEM(obj_line, 1);
    else {
        __tmp13 = NULL;
    }
    if (__tmp13 == NULL) goto __LL14;
    if (likely(PyUnicode_Check(PyTuple_GET_ITEM(obj_line, 2))))
        __tmp13 = PyTuple_GET_ITEM(obj_line, 2);
    else {
        __tmp13 = NULL;
    }
    if (__tmp13 == NULL) goto __LL14;
    __tmp13 = obj_line;
__LL14: ;
    if (unlikely(__tmp13 == NULL)) {
        CPy_TypeError("tuple[int, str, str]", obj_line); goto fail;
    } else {
        PyObject *__tmp15 = PyTuple_GET_ITEM(obj_line, 0);
        CPyTagged __tmp16;
        if (likely(PyLong_Check(__tmp15)))
            __tmp16 = CPyTagged_BorrowFromObject(__tmp15);
        else {
            CPy_TypeError("int", __tmp15); goto fail;
        }
        arg_line.f0 = __tmp16;
        PyObject *__tmp17 = PyTuple_GET_ITEM(obj_line, 1);
        PyObject *__tmp18;
        if (likely(PyUnicode_Check(__tmp17)))
            __tmp18 = __tmp17;
        else {
            CPy_TypeError("str", __tmp17); 
            __tmp18 = NULL;
        }
        arg_line.f1 = __tmp18;
        PyObject *__tmp19 = PyTuple_GET_ITEM(obj_line, 2);
        PyObject *__tmp20;
        if (likely(PyUnicode_Check(__tmp19)))
            __tmp20 = __tmp19;
        else {
            CPy_TypeError("str", __tmp19); 
            __tmp20 = NULL;
        }
        arg_line.f2 = __tmp20;
    }
    tuple_T2OO retval = CPyDef_process_genome(arg_d, arg_seq, arg_line);
    if (retval.f0 == NULL) {
        return NULL;
    }
    PyObject *retbox = PyTuple_New(2);
    if (unlikely(retbox == NULL))
        CPyError_OutOfMemory();
    PyObject *__tmp21 = retval.f0;
    PyTuple_SET_ITEM(retbox, 0, __tmp21);
    PyObject *__tmp22 = retval.f1;
    PyTuple_SET_ITEM(retbox, 1, __tmp22);
    return retbox;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "process_genome", 80, CPyStatic_globals);
    return NULL;
}

PyObject *CPyDef_read_file_in_chunks(PyObject *cpy_r_file_path, PyObject *cpy_r_output, CPyTagged cpy_r_n_cpus) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    PyObject *cpy_r_r2;
    PyObject *cpy_r_r3;
    PyObject *cpy_r_r4;
    PyObject **cpy_r_r6;
    PyObject *cpy_r_r7;
    CPyTagged cpy_r_r8;
    CPyTagged cpy_r_r9;
    PyObject *cpy_r_r10;
    PyObject *cpy_r_r11;
    PyObject *cpy_r_r12;
    PyObject *cpy_r_r13;
    PyObject *cpy_r_r14;
    PyObject **cpy_r_r16;
    PyObject *cpy_r_r17;
    PyObject *cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject *cpy_r_r21;
    PyObject *cpy_r_r22;
    PyObject **cpy_r_r24;
    PyObject *cpy_r_r25;
    char cpy_r_r26;
    PyObject *cpy_r_r27;
    PyObject **cpy_r_r29;
    PyObject *cpy_r_r30;
    CPyTagged cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    PyObject *cpy_r_r34;
    CPyTagged cpy_r_r35;
    PyObject *cpy_r_r36;
    PyObject *cpy_r_r37;
    PyObject *cpy_r_r38;
    PyObject *cpy_r_r39;
    PyObject *cpy_r_r40;
    PyObject *cpy_r_r41;
    PyObject **cpy_r_r43;
    PyObject *cpy_r_r44;
    PyObject *cpy_r_r45;
    PyObject *cpy_r_r46;
    PyObject *cpy_r_r47;
    PyObject *cpy_r_r48;
    PyObject *cpy_r_r49;
    PyObject *cpy_r_r50;
    PyObject **cpy_r_r52;
    PyObject *cpy_r_r53;
    char cpy_r_r54;
    CPyTagged cpy_r_start_byte;
    CPyTagged cpy_r_file_counter;
    CPyTagged cpy_r_r55;
    PyObject *cpy_r_r56;
    PyObject *cpy_r__;
    int64_t cpy_r_r57;
    char cpy_r_r58;
    int64_t cpy_r_r59;
    char cpy_r_r60;
    char cpy_r_r61;
    char cpy_r_r62;
    CPyTagged cpy_r_r63;
    CPyTagged cpy_r_r64;
    int64_t cpy_r_r65;
    char cpy_r_r66;
    int64_t cpy_r_r67;
    char cpy_r_r68;
    char cpy_r_r69;
    char cpy_r_r70;
    CPyTagged cpy_r_r71;
    CPyTagged cpy_r_end_byte;
    PyObject *cpy_r_r72;
    PyObject *cpy_r_r73;
    PyObject *cpy_r_r74;
    PyObject **cpy_r_r76;
    PyObject *cpy_r_r77;
    CPyTagged cpy_r_r78;
    char cpy_r_r79;
    CPyTagged cpy_r_r80;
    tuple_T5OIIIO cpy_r_r81;
    PyObject *cpy_r_r82;
    int32_t cpy_r_r83;
    char cpy_r_r84;
    CPyTagged cpy_r_r85;
    PyObject *cpy_r_r86;
    tuple_T3OOO cpy_r_r87;
    tuple_T3OOO cpy_r_r88;
    PyObject *cpy_r_r89;
    PyObject *cpy_r_r90;
    PyObject *cpy_r_r91;
    PyObject **cpy_r_r93;
    PyObject *cpy_r_r94;
    int32_t cpy_r_r95;
    char cpy_r_r96;
    char cpy_r_r97;
    char cpy_r_r98;
    tuple_T3OOO cpy_r_r99;
    tuple_T3OOO cpy_r_r100;
    tuple_T3OOO cpy_r_r101;
    PyObject *cpy_r_r102;
    PyObject **cpy_r_r104;
    PyObject *cpy_r_r105;
    char cpy_r_r106;
    tuple_T3OOO cpy_r_r107;
    tuple_T3OOO cpy_r_r108;
    PyObject *cpy_r_r109;
    PyObject *cpy_r_r110;
    PyObject *cpy_r_r111;
    PyObject **cpy_r_r113;
    PyObject *cpy_r_r114;
    int32_t cpy_r_r115;
    char cpy_r_r116;
    char cpy_r_r117;
    char cpy_r_r118;
    tuple_T3OOO cpy_r_r119;
    tuple_T3OOO cpy_r_r120;
    tuple_T3OOO cpy_r_r121;
    PyObject *cpy_r_r122;
    PyObject **cpy_r_r124;
    PyObject *cpy_r_r125;
    char cpy_r_r126;
    PyObject *cpy_r_r127;
    PyObject *cpy_r_r128;
    PyObject *cpy_r_r129;
    PyObject *cpy_r_r130;
    PyObject **cpy_r_r132;
    PyObject *cpy_r_r133;
    PyObject *cpy_r_r134;
    PyObject *cpy_r_r135;
    PyObject *cpy_r_r136;
    PyObject *cpy_r_r137;
    PyObject *cpy_r_r138;
    PyObject *cpy_r_r139;
    PyObject **cpy_r_r141;
    PyObject *cpy_r_r142;
    char cpy_r_r143;
    PyObject *cpy_r_r144;
    PyObject *cpy_r_r145;
    PyObject *cpy_r_r146;
    PyObject *cpy_r_r147;
    PyObject **cpy_r_r149;
    PyObject *cpy_r_r150;
    tuple_T3OOO cpy_r_r151;
    tuple_T3OOO cpy_r_r152;
    PyObject *cpy_r_r153;
    PyObject *cpy_r_r154;
    PyObject *cpy_r_r155;
    PyObject **cpy_r_r157;
    PyObject *cpy_r_r158;
    int32_t cpy_r_r159;
    char cpy_r_r160;
    char cpy_r_r161;
    char cpy_r_r162;
    tuple_T3OOO cpy_r_r163;
    tuple_T3OOO cpy_r_r164;
    tuple_T3OOO cpy_r_r165;
    PyObject *cpy_r_r166;
    PyObject **cpy_r_r168;
    PyObject *cpy_r_r169;
    char cpy_r_r170;
    PyObject *cpy_r_r171;
    PyObject *cpy_r_r172;
    cpy_r_r0 = CPyModule_os;
    cpy_r_r1 = CPyStatics[14]; /* 'path' */
    cpy_r_r2 = CPyObject_GetAttr(cpy_r_r0, cpy_r_r1);
    if (unlikely(cpy_r_r2 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 97, CPyStatic_globals);
        goto CPyL111;
    }
    cpy_r_r3 = CPyStatics[38]; /* 'getsize' */
    cpy_r_r4 = CPyObject_GetAttr(cpy_r_r2, cpy_r_r3);
    CPy_DECREF(cpy_r_r2);
    if (unlikely(cpy_r_r4 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 97, CPyStatic_globals);
        goto CPyL111;
    }
    PyObject *cpy_r_r5[1] = {cpy_r_file_path};
    cpy_r_r6 = (PyObject **)&cpy_r_r5;
    cpy_r_r7 = _PyObject_Vectorcall(cpy_r_r4, cpy_r_r6, 1, 0);
    CPy_DECREF(cpy_r_r4);
    if (unlikely(cpy_r_r7 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 97, CPyStatic_globals);
        goto CPyL111;
    }
    if (likely(PyLong_Check(cpy_r_r7)))
        cpy_r_r8 = CPyTagged_FromObject(cpy_r_r7);
    else {
        CPy_TypeError("int", cpy_r_r7); cpy_r_r8 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r7);
    if (unlikely(cpy_r_r8 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 97, CPyStatic_globals);
        goto CPyL111;
    }
    cpy_r_r9 = CPyTagged_FloorDivide(cpy_r_r8, cpy_r_n_cpus);
    if (unlikely(cpy_r_r9 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 98, CPyStatic_globals);
        goto CPyL112;
    }
    cpy_r_r10 = PyList_New(0);
    if (unlikely(cpy_r_r10 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 99, CPyStatic_globals);
        goto CPyL113;
    }
    cpy_r_r11 = CPyStatics[22]; /* 'r+b' */
    cpy_r_r12 = CPyModule_builtins;
    cpy_r_r13 = CPyStatics[21]; /* 'open' */
    cpy_r_r14 = CPyObject_GetAttr(cpy_r_r12, cpy_r_r13);
    if (unlikely(cpy_r_r14 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL114;
    }
    PyObject *cpy_r_r15[2] = {cpy_r_file_path, cpy_r_r11};
    cpy_r_r16 = (PyObject **)&cpy_r_r15;
    cpy_r_r17 = _PyObject_Vectorcall(cpy_r_r14, cpy_r_r16, 2, 0);
    CPy_DECREF(cpy_r_r14);
    if (unlikely(cpy_r_r17 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL114;
    }
    cpy_r_r18 = PyObject_Type(cpy_r_r17);
    cpy_r_r19 = CPyStatics[23]; /* '__exit__' */
    cpy_r_r20 = CPyObject_GetAttr(cpy_r_r18, cpy_r_r19);
    if (unlikely(cpy_r_r20 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL115;
    }
    cpy_r_r21 = CPyStatics[24]; /* '__enter__' */
    cpy_r_r22 = CPyObject_GetAttr(cpy_r_r18, cpy_r_r21);
    CPy_DECREF(cpy_r_r18);
    if (unlikely(cpy_r_r22 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL116;
    }
    PyObject *cpy_r_r23[1] = {cpy_r_r17};
    cpy_r_r24 = (PyObject **)&cpy_r_r23;
    cpy_r_r25 = _PyObject_Vectorcall(cpy_r_r22, cpy_r_r24, 1, 0);
    CPy_DECREF(cpy_r_r22);
    if (unlikely(cpy_r_r25 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL116;
    }
    cpy_r_r26 = 1;
    cpy_r_r27 = CPyStatics[25]; /* 'fileno' */
    PyObject *cpy_r_r28[1] = {cpy_r_r25};
    cpy_r_r29 = (PyObject **)&cpy_r_r28;
    cpy_r_r30 = PyObject_VectorcallMethod(cpy_r_r27, cpy_r_r29, 9223372036854775809ULL, 0);
    if (unlikely(cpy_r_r30 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 103, CPyStatic_globals);
        goto CPyL117;
    }
    CPy_DECREF(cpy_r_r25);
    if (likely(PyLong_Check(cpy_r_r30)))
        cpy_r_r31 = CPyTagged_FromObject(cpy_r_r30);
    else {
        CPy_TypeError("int", cpy_r_r30); cpy_r_r31 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r30);
    if (unlikely(cpy_r_r31 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 103, CPyStatic_globals);
        goto CPyL118;
    }
    cpy_r_r32 = CPyModule_mmap;
    cpy_r_r33 = CPyStatics[26]; /* 'ACCESS_READ' */
    cpy_r_r34 = CPyObject_GetAttr(cpy_r_r32, cpy_r_r33);
    if (unlikely(cpy_r_r34 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 103, CPyStatic_globals);
        goto CPyL119;
    }
    if (likely(PyLong_Check(cpy_r_r34)))
        cpy_r_r35 = CPyTagged_FromObject(cpy_r_r34);
    else {
        CPy_TypeError("int", cpy_r_r34); cpy_r_r35 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r34);
    if (unlikely(cpy_r_r35 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 103, CPyStatic_globals);
        goto CPyL119;
    }
    cpy_r_r36 = CPyModule_mmap;
    cpy_r_r37 = CPyStatics[27]; /* 'mmap' */
    cpy_r_r38 = CPyObject_GetAttr(cpy_r_r36, cpy_r_r37);
    if (unlikely(cpy_r_r38 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL120;
    }
    cpy_r_r39 = CPyTagged_StealAsObject(cpy_r_r31);
    cpy_r_r40 = CPyStatics[65]; /* 0 */
    cpy_r_r41 = CPyTagged_StealAsObject(cpy_r_r35);
    PyObject *cpy_r_r42[3] = {cpy_r_r39, cpy_r_r40, cpy_r_r41};
    cpy_r_r43 = (PyObject **)&cpy_r_r42;
    cpy_r_r44 = CPyStatics[67]; /* ('length', 'access') */
    cpy_r_r45 = _PyObject_Vectorcall(cpy_r_r38, cpy_r_r43, 1, cpy_r_r44);
    CPy_DECREF(cpy_r_r38);
    if (unlikely(cpy_r_r45 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL121;
    }
    CPy_DECREF(cpy_r_r39);
    CPy_DECREF(cpy_r_r41);
    cpy_r_r46 = PyObject_Type(cpy_r_r45);
    cpy_r_r47 = CPyStatics[23]; /* '__exit__' */
    cpy_r_r48 = CPyObject_GetAttr(cpy_r_r46, cpy_r_r47);
    if (unlikely(cpy_r_r48 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL122;
    }
    cpy_r_r49 = CPyStatics[24]; /* '__enter__' */
    cpy_r_r50 = CPyObject_GetAttr(cpy_r_r46, cpy_r_r49);
    CPy_DECREF(cpy_r_r46);
    if (unlikely(cpy_r_r50 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL123;
    }
    PyObject *cpy_r_r51[1] = {cpy_r_r45};
    cpy_r_r52 = (PyObject **)&cpy_r_r51;
    cpy_r_r53 = _PyObject_Vectorcall(cpy_r_r50, cpy_r_r52, 1, 0);
    CPy_DECREF(cpy_r_r50);
    if (unlikely(cpy_r_r53 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL123;
    }
    cpy_r_r54 = 1;
    cpy_r_start_byte = 0;
    cpy_r_file_counter = 0;
    cpy_r_r55 = 0;
    CPyTagged_INCREF(cpy_r_r55);
    cpy_r_r56 = CPyTagged_StealAsObject(cpy_r_r55);
    cpy_r__ = cpy_r_r56;
    CPy_DECREF(cpy_r__);
CPyL23: ;
    cpy_r_r57 = cpy_r_r55 & 1;
    cpy_r_r58 = cpy_r_r57 != 0;
    if (cpy_r_r58) goto CPyL25;
    cpy_r_r59 = cpy_r_n_cpus & 1;
    cpy_r_r60 = cpy_r_r59 != 0;
    if (!cpy_r_r60) goto CPyL26;
CPyL25: ;
    cpy_r_r61 = CPyTagged_IsLt_(cpy_r_r55, cpy_r_n_cpus);
    if (cpy_r_r61) {
        goto CPyL27;
    } else
        goto CPyL124;
CPyL26: ;
    cpy_r_r62 = (Py_ssize_t)cpy_r_r55 < (Py_ssize_t)cpy_r_n_cpus;
    if (!cpy_r_r62) goto CPyL124;
CPyL27: ;
    cpy_r_r63 = CPyTagged_Add(cpy_r_file_counter, 2);
    CPyTagged_DECREF(cpy_r_file_counter);
    cpy_r_file_counter = cpy_r_r63;
    cpy_r_r64 = CPyTagged_Add(cpy_r_start_byte, cpy_r_r9);
    cpy_r_r65 = cpy_r_r8 & 1;
    cpy_r_r66 = cpy_r_r65 != 0;
    if (cpy_r_r66) goto CPyL29;
    cpy_r_r67 = cpy_r_r64 & 1;
    cpy_r_r68 = cpy_r_r67 != 0;
    if (!cpy_r_r68) goto CPyL30;
CPyL29: ;
    cpy_r_r69 = CPyTagged_IsLt_(cpy_r_r8, cpy_r_r64);
    if (cpy_r_r69) {
        goto CPyL125;
    } else
        goto CPyL32;
CPyL30: ;
    cpy_r_r70 = (Py_ssize_t)cpy_r_r8 < (Py_ssize_t)cpy_r_r64;
    if (cpy_r_r70) {
        goto CPyL125;
    } else
        goto CPyL32;
CPyL31: ;
    CPyTagged_INCREF(cpy_r_r8);
    cpy_r_r71 = cpy_r_r8;
    goto CPyL33;
CPyL32: ;
    cpy_r_r71 = cpy_r_r64;
CPyL33: ;
    cpy_r_end_byte = cpy_r_r71;
    cpy_r_r72 = CPyStatics[60]; /* b'>' */
    cpy_r_r73 = CPyStatics[40]; /* 'find' */
    cpy_r_r74 = CPyTagged_StealAsObject(cpy_r_end_byte);
    PyObject *cpy_r_r75[3] = {cpy_r_r53, cpy_r_r72, cpy_r_r74};
    cpy_r_r76 = (PyObject **)&cpy_r_r75;
    cpy_r_r77 = PyObject_VectorcallMethod(cpy_r_r73, cpy_r_r76, 9223372036854775811ULL, 0);
    if (unlikely(cpy_r_r77 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 110, CPyStatic_globals);
        goto CPyL126;
    }
    CPy_DECREF(cpy_r_r74);
    if (likely(PyLong_Check(cpy_r_r77)))
        cpy_r_r78 = CPyTagged_FromObject(cpy_r_r77);
    else {
        CPy_TypeError("int", cpy_r_r77); cpy_r_r78 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r77);
    if (unlikely(cpy_r_r78 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 110, CPyStatic_globals);
        goto CPyL127;
    }
    cpy_r_end_byte = cpy_r_r78;
    cpy_r_r79 = (Py_ssize_t)cpy_r_end_byte != -2;
    if (!cpy_r_r79) goto CPyL128;
    cpy_r_r80 = cpy_r_end_byte;
    goto CPyL38;
CPyL37: ;
    CPyTagged_INCREF(cpy_r_r8);
    cpy_r_r80 = cpy_r_r8;
CPyL38: ;
    cpy_r_end_byte = cpy_r_r80;
    CPy_INCREF(cpy_r_file_path);
    CPyTagged_INCREF(cpy_r_end_byte);
    CPyTagged_INCREF(cpy_r_file_counter);
    CPy_INCREF(cpy_r_output);
    cpy_r_r81.f0 = cpy_r_file_path;
    cpy_r_r81.f1 = cpy_r_start_byte;
    cpy_r_r81.f2 = cpy_r_end_byte;
    cpy_r_r81.f3 = cpy_r_file_counter;
    cpy_r_r81.f4 = cpy_r_output;
    cpy_r_r82 = PyTuple_New(5);
    if (unlikely(cpy_r_r82 == NULL))
        CPyError_OutOfMemory();
    PyObject *__tmp23 = cpy_r_r81.f0;
    PyTuple_SET_ITEM(cpy_r_r82, 0, __tmp23);
    PyObject *__tmp24 = CPyTagged_StealAsObject(cpy_r_r81.f1);
    PyTuple_SET_ITEM(cpy_r_r82, 1, __tmp24);
    PyObject *__tmp25 = CPyTagged_StealAsObject(cpy_r_r81.f2);
    PyTuple_SET_ITEM(cpy_r_r82, 2, __tmp25);
    PyObject *__tmp26 = CPyTagged_StealAsObject(cpy_r_r81.f3);
    PyTuple_SET_ITEM(cpy_r_r82, 3, __tmp26);
    PyObject *__tmp27 = cpy_r_r81.f4;
    PyTuple_SET_ITEM(cpy_r_r82, 4, __tmp27);
    cpy_r_r83 = PyList_Append(cpy_r_r10, cpy_r_r82);
    CPy_DECREF(cpy_r_r82);
    cpy_r_r84 = cpy_r_r83 >= 0;
    if (unlikely(!cpy_r_r84)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 112, CPyStatic_globals);
        goto CPyL129;
    }
    cpy_r_start_byte = cpy_r_end_byte;
    cpy_r_r85 = CPyTagged_Add(cpy_r_r55, 2);
    CPyTagged_DECREF(cpy_r_r55);
    CPyTagged_INCREF(cpy_r_r85);
    cpy_r_r55 = cpy_r_r85;
    cpy_r_r86 = CPyTagged_StealAsObject(cpy_r_r85);
    cpy_r__ = cpy_r_r86;
    CPy_DECREF(cpy_r__);
    goto CPyL23;
CPyL41: ;
    cpy_r_r87 = CPy_CatchError();
    cpy_r_r54 = 0;
    cpy_r_r88 = CPy_GetExcInfo();
    cpy_r_r89 = cpy_r_r88.f0;
    CPy_INCREF(cpy_r_r89);
    cpy_r_r90 = cpy_r_r88.f1;
    CPy_INCREF(cpy_r_r90);
    cpy_r_r91 = cpy_r_r88.f2;
    CPy_INCREF(cpy_r_r91);
    CPy_DecRef(cpy_r_r88.f0);
    CPy_DecRef(cpy_r_r88.f1);
    CPy_DecRef(cpy_r_r88.f2);
    PyObject *cpy_r_r92[4] = {cpy_r_r45, cpy_r_r89, cpy_r_r90, cpy_r_r91};
    cpy_r_r93 = (PyObject **)&cpy_r_r92;
    cpy_r_r94 = _PyObject_Vectorcall(cpy_r_r48, cpy_r_r93, 4, 0);
    if (unlikely(cpy_r_r94 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL130;
    }
    CPy_DecRef(cpy_r_r89);
    CPy_DecRef(cpy_r_r90);
    CPy_DecRef(cpy_r_r91);
    cpy_r_r95 = PyObject_IsTrue(cpy_r_r94);
    CPy_DecRef(cpy_r_r94);
    cpy_r_r96 = cpy_r_r95 >= 0;
    if (unlikely(!cpy_r_r96)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL47;
    }
    cpy_r_r97 = cpy_r_r95;
    if (cpy_r_r97) goto CPyL46;
    CPy_Reraise();
    if (!0) {
        goto CPyL47;
    } else
        goto CPyL131;
CPyL45: ;
    CPy_Unreachable();
CPyL46: ;
    CPy_RestoreExcInfo(cpy_r_r87);
    CPy_DecRef(cpy_r_r87.f0);
    CPy_DecRef(cpy_r_r87.f1);
    CPy_DecRef(cpy_r_r87.f2);
    goto CPyL49;
CPyL47: ;
    CPy_RestoreExcInfo(cpy_r_r87);
    CPy_DecRef(cpy_r_r87.f0);
    CPy_DecRef(cpy_r_r87.f1);
    CPy_DecRef(cpy_r_r87.f2);
    cpy_r_r98 = CPy_KeepPropagating();
    if (!cpy_r_r98) {
        goto CPyL50;
    } else
        goto CPyL132;
CPyL48: ;
    CPy_Unreachable();
CPyL49: ;
    tuple_T3OOO __tmp28 = { NULL, NULL, NULL };
    cpy_r_r99 = __tmp28;
    cpy_r_r100 = cpy_r_r99;
    goto CPyL51;
CPyL50: ;
    cpy_r_r101 = CPy_CatchError();
    cpy_r_r100 = cpy_r_r101;
CPyL51: ;
    if (!cpy_r_r54) goto CPyL133;
    cpy_r_r102 = (PyObject *)&_Py_NoneStruct;
    PyObject *cpy_r_r103[4] = {cpy_r_r45, cpy_r_r102, cpy_r_r102, cpy_r_r102};
    cpy_r_r104 = (PyObject **)&cpy_r_r103;
    cpy_r_r105 = _PyObject_Vectorcall(cpy_r_r48, cpy_r_r104, 4, 0);
    CPy_DECREF(cpy_r_r48);
    if (unlikely(cpy_r_r105 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 102, CPyStatic_globals);
        goto CPyL134;
    } else
        goto CPyL135;
CPyL53: ;
    CPy_DECREF(cpy_r_r45);
CPyL54: ;
    if (cpy_r_r100.f0 == NULL) goto CPyL69;
    CPy_Reraise();
    if (!0) {
        goto CPyL57;
    } else
        goto CPyL136;
CPyL56: ;
    CPy_Unreachable();
CPyL57: ;
    if (cpy_r_r100.f0 == NULL) goto CPyL59;
    CPy_RestoreExcInfo(cpy_r_r100);
    CPy_XDECREF(cpy_r_r100.f0);
    CPy_XDECREF(cpy_r_r100.f1);
    CPy_XDECREF(cpy_r_r100.f2);
CPyL59: ;
    cpy_r_r106 = CPy_KeepPropagating();
    if (!cpy_r_r106) {
        goto CPyL61;
    } else
        goto CPyL137;
CPyL60: ;
    CPy_Unreachable();
CPyL61: ;
    cpy_r_r107 = CPy_CatchError();
    cpy_r_r26 = 0;
    cpy_r_r108 = CPy_GetExcInfo();
    cpy_r_r109 = cpy_r_r108.f0;
    CPy_INCREF(cpy_r_r109);
    cpy_r_r110 = cpy_r_r108.f1;
    CPy_INCREF(cpy_r_r110);
    cpy_r_r111 = cpy_r_r108.f2;
    CPy_INCREF(cpy_r_r111);
    CPy_DECREF(cpy_r_r108.f0);
    CPy_DECREF(cpy_r_r108.f1);
    CPy_DECREF(cpy_r_r108.f2);
    PyObject *cpy_r_r112[4] = {cpy_r_r17, cpy_r_r109, cpy_r_r110, cpy_r_r111};
    cpy_r_r113 = (PyObject **)&cpy_r_r112;
    cpy_r_r114 = _PyObject_Vectorcall(cpy_r_r20, cpy_r_r113, 4, 0);
    if (unlikely(cpy_r_r114 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL138;
    }
    CPy_DECREF(cpy_r_r109);
    CPy_DECREF(cpy_r_r110);
    CPy_DECREF(cpy_r_r111);
    cpy_r_r115 = PyObject_IsTrue(cpy_r_r114);
    CPy_DECREF(cpy_r_r114);
    cpy_r_r116 = cpy_r_r115 >= 0;
    if (unlikely(!cpy_r_r116)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL67;
    }
    cpy_r_r117 = cpy_r_r115;
    if (cpy_r_r117) goto CPyL66;
    CPy_Reraise();
    if (!0) {
        goto CPyL67;
    } else
        goto CPyL139;
CPyL65: ;
    CPy_Unreachable();
CPyL66: ;
    CPy_RestoreExcInfo(cpy_r_r107);
    CPy_DECREF(cpy_r_r107.f0);
    CPy_DECREF(cpy_r_r107.f1);
    CPy_DECREF(cpy_r_r107.f2);
    goto CPyL69;
CPyL67: ;
    CPy_RestoreExcInfo(cpy_r_r107);
    CPy_DECREF(cpy_r_r107.f0);
    CPy_DECREF(cpy_r_r107.f1);
    CPy_DECREF(cpy_r_r107.f2);
    cpy_r_r118 = CPy_KeepPropagating();
    if (!cpy_r_r118) {
        goto CPyL70;
    } else
        goto CPyL140;
CPyL68: ;
    CPy_Unreachable();
CPyL69: ;
    tuple_T3OOO __tmp29 = { NULL, NULL, NULL };
    cpy_r_r119 = __tmp29;
    cpy_r_r120 = cpy_r_r119;
    goto CPyL71;
CPyL70: ;
    cpy_r_r121 = CPy_CatchError();
    cpy_r_r120 = cpy_r_r121;
CPyL71: ;
    if (!cpy_r_r26) goto CPyL141;
    cpy_r_r122 = (PyObject *)&_Py_NoneStruct;
    PyObject *cpy_r_r123[4] = {cpy_r_r17, cpy_r_r122, cpy_r_r122, cpy_r_r122};
    cpy_r_r124 = (PyObject **)&cpy_r_r123;
    cpy_r_r125 = _PyObject_Vectorcall(cpy_r_r20, cpy_r_r124, 4, 0);
    CPy_DECREF(cpy_r_r20);
    if (unlikely(cpy_r_r125 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 101, CPyStatic_globals);
        goto CPyL142;
    } else
        goto CPyL143;
CPyL73: ;
    CPy_DECREF(cpy_r_r17);
CPyL74: ;
    if (cpy_r_r120.f0 == NULL) {
        goto CPyL81;
    } else
        goto CPyL144;
CPyL75: ;
    CPy_Reraise();
    if (!0) {
        goto CPyL77;
    } else
        goto CPyL145;
CPyL76: ;
    CPy_Unreachable();
CPyL77: ;
    if (cpy_r_r120.f0 == NULL) goto CPyL79;
    CPy_RestoreExcInfo(cpy_r_r120);
    CPy_XDECREF(cpy_r_r120.f0);
    CPy_XDECREF(cpy_r_r120.f1);
    CPy_XDECREF(cpy_r_r120.f2);
CPyL79: ;
    cpy_r_r126 = CPy_KeepPropagating();
    if (!cpy_r_r126) goto CPyL111;
    CPy_Unreachable();
CPyL81: ;
    cpy_r_r127 = CPyModule_multiprocessing;
    cpy_r_r128 = CPyStatics[41]; /* 'Pool' */
    cpy_r_r129 = CPyObject_GetAttr(cpy_r_r127, cpy_r_r128);
    if (unlikely(cpy_r_r129 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL146;
    }
    CPyTagged_INCREF(cpy_r_n_cpus);
    cpy_r_r130 = CPyTagged_StealAsObject(cpy_r_n_cpus);
    PyObject *cpy_r_r131[1] = {cpy_r_r130};
    cpy_r_r132 = (PyObject **)&cpy_r_r131;
    cpy_r_r133 = CPyStatics[68]; /* ('processes',) */
    cpy_r_r134 = _PyObject_Vectorcall(cpy_r_r129, cpy_r_r132, 0, cpy_r_r133);
    CPy_DECREF(cpy_r_r129);
    if (unlikely(cpy_r_r134 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL147;
    }
    CPy_DECREF(cpy_r_r130);
    cpy_r_r135 = PyObject_Type(cpy_r_r134);
    cpy_r_r136 = CPyStatics[23]; /* '__exit__' */
    cpy_r_r137 = CPyObject_GetAttr(cpy_r_r135, cpy_r_r136);
    if (unlikely(cpy_r_r137 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL148;
    }
    cpy_r_r138 = CPyStatics[24]; /* '__enter__' */
    cpy_r_r139 = CPyObject_GetAttr(cpy_r_r135, cpy_r_r138);
    CPy_DECREF(cpy_r_r135);
    if (unlikely(cpy_r_r139 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL149;
    }
    PyObject *cpy_r_r140[1] = {cpy_r_r134};
    cpy_r_r141 = (PyObject **)&cpy_r_r140;
    cpy_r_r142 = _PyObject_Vectorcall(cpy_r_r139, cpy_r_r141, 1, 0);
    CPy_DECREF(cpy_r_r139);
    if (unlikely(cpy_r_r142 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL149;
    }
    cpy_r_r143 = 1;
    cpy_r_r144 = CPyStatic_globals;
    cpy_r_r145 = CPyStatics[43]; /* 'process_chunk' */
    cpy_r_r146 = CPyDict_GetItem(cpy_r_r144, cpy_r_r145);
    if (unlikely(cpy_r_r146 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 116, CPyStatic_globals);
        goto CPyL150;
    }
    cpy_r_r147 = CPyStatics[44]; /* 'starmap' */
    PyObject *cpy_r_r148[3] = {cpy_r_r142, cpy_r_r146, cpy_r_r10};
    cpy_r_r149 = (PyObject **)&cpy_r_r148;
    cpy_r_r150 = PyObject_VectorcallMethod(cpy_r_r147, cpy_r_r149, 9223372036854775811ULL, 0);
    if (unlikely(cpy_r_r150 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 116, CPyStatic_globals);
        goto CPyL151;
    } else
        goto CPyL152;
CPyL89: ;
    CPy_DECREF(cpy_r_r142);
    CPy_DECREF(cpy_r_r146);
    CPy_DECREF(cpy_r_r10);
    goto CPyL98;
CPyL90: ;
    cpy_r_r151 = CPy_CatchError();
    cpy_r_r143 = 0;
    cpy_r_r152 = CPy_GetExcInfo();
    cpy_r_r153 = cpy_r_r152.f0;
    CPy_INCREF(cpy_r_r153);
    cpy_r_r154 = cpy_r_r152.f1;
    CPy_INCREF(cpy_r_r154);
    cpy_r_r155 = cpy_r_r152.f2;
    CPy_INCREF(cpy_r_r155);
    CPy_DecRef(cpy_r_r152.f0);
    CPy_DecRef(cpy_r_r152.f1);
    CPy_DecRef(cpy_r_r152.f2);
    PyObject *cpy_r_r156[4] = {cpy_r_r134, cpy_r_r153, cpy_r_r154, cpy_r_r155};
    cpy_r_r157 = (PyObject **)&cpy_r_r156;
    cpy_r_r158 = _PyObject_Vectorcall(cpy_r_r137, cpy_r_r157, 4, 0);
    if (unlikely(cpy_r_r158 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL153;
    }
    CPy_DecRef(cpy_r_r153);
    CPy_DecRef(cpy_r_r154);
    CPy_DecRef(cpy_r_r155);
    cpy_r_r159 = PyObject_IsTrue(cpy_r_r158);
    CPy_DecRef(cpy_r_r158);
    cpy_r_r160 = cpy_r_r159 >= 0;
    if (unlikely(!cpy_r_r160)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL96;
    }
    cpy_r_r161 = cpy_r_r159;
    if (cpy_r_r161) goto CPyL95;
    CPy_Reraise();
    if (!0) {
        goto CPyL96;
    } else
        goto CPyL154;
CPyL94: ;
    CPy_Unreachable();
CPyL95: ;
    CPy_RestoreExcInfo(cpy_r_r151);
    CPy_DecRef(cpy_r_r151.f0);
    CPy_DecRef(cpy_r_r151.f1);
    CPy_DecRef(cpy_r_r151.f2);
    goto CPyL98;
CPyL96: ;
    CPy_RestoreExcInfo(cpy_r_r151);
    CPy_DecRef(cpy_r_r151.f0);
    CPy_DecRef(cpy_r_r151.f1);
    CPy_DecRef(cpy_r_r151.f2);
    cpy_r_r162 = CPy_KeepPropagating();
    if (!cpy_r_r162) {
        goto CPyL99;
    } else
        goto CPyL155;
CPyL97: ;
    CPy_Unreachable();
CPyL98: ;
    tuple_T3OOO __tmp30 = { NULL, NULL, NULL };
    cpy_r_r163 = __tmp30;
    cpy_r_r164 = cpy_r_r163;
    goto CPyL100;
CPyL99: ;
    cpy_r_r165 = CPy_CatchError();
    cpy_r_r164 = cpy_r_r165;
CPyL100: ;
    if (!cpy_r_r143) goto CPyL156;
    cpy_r_r166 = (PyObject *)&_Py_NoneStruct;
    PyObject *cpy_r_r167[4] = {cpy_r_r134, cpy_r_r166, cpy_r_r166, cpy_r_r166};
    cpy_r_r168 = (PyObject **)&cpy_r_r167;
    cpy_r_r169 = _PyObject_Vectorcall(cpy_r_r137, cpy_r_r168, 4, 0);
    CPy_DECREF(cpy_r_r137);
    if (unlikely(cpy_r_r169 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 115, CPyStatic_globals);
        goto CPyL157;
    } else
        goto CPyL158;
CPyL102: ;
    CPy_DECREF(cpy_r_r134);
CPyL103: ;
    if (cpy_r_r164.f0 == NULL) goto CPyL110;
    CPy_Reraise();
    if (!0) {
        goto CPyL106;
    } else
        goto CPyL159;
CPyL105: ;
    CPy_Unreachable();
CPyL106: ;
    if (cpy_r_r164.f0 == NULL) goto CPyL108;
    CPy_RestoreExcInfo(cpy_r_r164);
    CPy_XDECREF(cpy_r_r164.f0);
    CPy_XDECREF(cpy_r_r164.f1);
    CPy_XDECREF(cpy_r_r164.f2);
CPyL108: ;
    cpy_r_r170 = CPy_KeepPropagating();
    if (!cpy_r_r170) goto CPyL111;
    CPy_Unreachable();
CPyL110: ;
    cpy_r_r171 = Py_None;
    CPy_INCREF(cpy_r_r171);
    return cpy_r_r171;
CPyL111: ;
    cpy_r_r172 = NULL;
    return cpy_r_r172;
CPyL112: ;
    CPyTagged_DecRef(cpy_r_r8);
    goto CPyL111;
CPyL113: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    goto CPyL111;
CPyL114: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r10);
    goto CPyL111;
CPyL115: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r17);
    CPy_DecRef(cpy_r_r18);
    goto CPyL111;
CPyL116: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r17);
    CPy_DecRef(cpy_r_r20);
    goto CPyL111;
CPyL117: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r25);
    goto CPyL61;
CPyL118: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    goto CPyL61;
CPyL119: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPyTagged_DecRef(cpy_r_r31);
    goto CPyL61;
CPyL120: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPyTagged_DecRef(cpy_r_r31);
    CPyTagged_DecRef(cpy_r_r35);
    goto CPyL61;
CPyL121: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r39);
    CPy_DecRef(cpy_r_r41);
    goto CPyL61;
CPyL122: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r45);
    CPy_DecRef(cpy_r_r46);
    goto CPyL61;
CPyL123: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r45);
    CPy_DecRef(cpy_r_r48);
    goto CPyL61;
CPyL124: ;
    CPyTagged_DECREF(cpy_r_r8);
    CPyTagged_DECREF(cpy_r_r9);
    CPy_DECREF(cpy_r_r53);
    CPyTagged_DECREF(cpy_r_start_byte);
    CPyTagged_DECREF(cpy_r_file_counter);
    CPyTagged_DECREF(cpy_r_r55);
    goto CPyL49;
CPyL125: ;
    CPyTagged_DECREF(cpy_r_r64);
    goto CPyL31;
CPyL126: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r53);
    CPyTagged_DecRef(cpy_r_start_byte);
    CPyTagged_DecRef(cpy_r_file_counter);
    CPyTagged_DecRef(cpy_r_r55);
    CPy_DecRef(cpy_r_r74);
    goto CPyL41;
CPyL127: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r53);
    CPyTagged_DecRef(cpy_r_start_byte);
    CPyTagged_DecRef(cpy_r_file_counter);
    CPyTagged_DecRef(cpy_r_r55);
    goto CPyL41;
CPyL128: ;
    CPyTagged_DECREF(cpy_r_end_byte);
    goto CPyL37;
CPyL129: ;
    CPyTagged_DecRef(cpy_r_r8);
    CPyTagged_DecRef(cpy_r_r9);
    CPy_DecRef(cpy_r_r53);
    CPyTagged_DecRef(cpy_r_file_counter);
    CPyTagged_DecRef(cpy_r_r55);
    CPyTagged_DecRef(cpy_r_end_byte);
    goto CPyL41;
CPyL130: ;
    CPy_DecRef(cpy_r_r89);
    CPy_DecRef(cpy_r_r90);
    CPy_DecRef(cpy_r_r91);
    goto CPyL47;
CPyL131: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r17);
    CPy_DecRef(cpy_r_r20);
    CPy_DecRef(cpy_r_r45);
    CPy_DecRef(cpy_r_r48);
    CPy_DecRef(cpy_r_r87.f0);
    CPy_DecRef(cpy_r_r87.f1);
    CPy_DecRef(cpy_r_r87.f2);
    goto CPyL45;
CPyL132: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r17);
    CPy_DecRef(cpy_r_r20);
    CPy_DecRef(cpy_r_r45);
    CPy_DecRef(cpy_r_r48);
    goto CPyL48;
CPyL133: ;
    CPy_DECREF(cpy_r_r45);
    CPy_DECREF(cpy_r_r48);
    goto CPyL54;
CPyL134: ;
    CPy_DecRef(cpy_r_r45);
    goto CPyL57;
CPyL135: ;
    CPy_DECREF(cpy_r_r105);
    goto CPyL53;
CPyL136: ;
    CPy_DECREF(cpy_r_r10);
    CPy_DECREF(cpy_r_r17);
    CPy_DECREF(cpy_r_r20);
    CPy_XDECREF(cpy_r_r100.f0);
    CPy_XDECREF(cpy_r_r100.f1);
    CPy_XDECREF(cpy_r_r100.f2);
    goto CPyL56;
CPyL137: ;
    CPy_DECREF(cpy_r_r10);
    CPy_DECREF(cpy_r_r17);
    CPy_DECREF(cpy_r_r20);
    goto CPyL60;
CPyL138: ;
    CPy_DecRef(cpy_r_r109);
    CPy_DecRef(cpy_r_r110);
    CPy_DecRef(cpy_r_r111);
    goto CPyL67;
CPyL139: ;
    CPy_DECREF(cpy_r_r10);
    CPy_DECREF(cpy_r_r17);
    CPy_DECREF(cpy_r_r20);
    CPy_DECREF(cpy_r_r107.f0);
    CPy_DECREF(cpy_r_r107.f1);
    CPy_DECREF(cpy_r_r107.f2);
    goto CPyL65;
CPyL140: ;
    CPy_DECREF(cpy_r_r10);
    CPy_DECREF(cpy_r_r17);
    CPy_DECREF(cpy_r_r20);
    goto CPyL68;
CPyL141: ;
    CPy_DECREF(cpy_r_r17);
    CPy_DECREF(cpy_r_r20);
    goto CPyL74;
CPyL142: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r17);
    goto CPyL77;
CPyL143: ;
    CPy_DECREF(cpy_r_r125);
    goto CPyL73;
CPyL144: ;
    CPy_DECREF(cpy_r_r10);
    goto CPyL75;
CPyL145: ;
    CPy_XDECREF(cpy_r_r120.f0);
    CPy_XDECREF(cpy_r_r120.f1);
    CPy_XDECREF(cpy_r_r120.f2);
    goto CPyL76;
CPyL146: ;
    CPy_DecRef(cpy_r_r10);
    goto CPyL111;
CPyL147: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r130);
    goto CPyL111;
CPyL148: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r134);
    CPy_DecRef(cpy_r_r135);
    goto CPyL111;
CPyL149: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r134);
    CPy_DecRef(cpy_r_r137);
    goto CPyL111;
CPyL150: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r142);
    goto CPyL90;
CPyL151: ;
    CPy_DecRef(cpy_r_r10);
    CPy_DecRef(cpy_r_r142);
    CPy_DecRef(cpy_r_r146);
    goto CPyL90;
CPyL152: ;
    CPy_DECREF(cpy_r_r150);
    goto CPyL89;
CPyL153: ;
    CPy_DecRef(cpy_r_r153);
    CPy_DecRef(cpy_r_r154);
    CPy_DecRef(cpy_r_r155);
    goto CPyL96;
CPyL154: ;
    CPy_DecRef(cpy_r_r134);
    CPy_DecRef(cpy_r_r137);
    CPy_DecRef(cpy_r_r151.f0);
    CPy_DecRef(cpy_r_r151.f1);
    CPy_DecRef(cpy_r_r151.f2);
    goto CPyL94;
CPyL155: ;
    CPy_DecRef(cpy_r_r134);
    CPy_DecRef(cpy_r_r137);
    goto CPyL97;
CPyL156: ;
    CPy_DECREF(cpy_r_r134);
    CPy_DECREF(cpy_r_r137);
    goto CPyL103;
CPyL157: ;
    CPy_DecRef(cpy_r_r134);
    goto CPyL106;
CPyL158: ;
    CPy_DECREF(cpy_r_r169);
    goto CPyL102;
CPyL159: ;
    CPy_XDECREF(cpy_r_r164.f0);
    CPy_XDECREF(cpy_r_r164.f1);
    CPy_XDECREF(cpy_r_r164.f2);
    goto CPyL105;
}

PyObject *CPyPy_read_file_in_chunks(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"file_path", "output", "n_cpus", 0};
    static CPyArg_Parser parser = {"OOO:read_file_in_chunks", kwlist, 0};
    PyObject *obj_file_path;
    PyObject *obj_output;
    PyObject *obj_n_cpus;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_file_path, &obj_output, &obj_n_cpus)) {
        return NULL;
    }
    PyObject *arg_file_path;
    if (likely(PyUnicode_Check(obj_file_path)))
        arg_file_path = obj_file_path;
    else {
        CPy_TypeError("str", obj_file_path); 
        goto fail;
    }
    PyObject *arg_output;
    if (likely(PyUnicode_Check(obj_output)))
        arg_output = obj_output;
    else {
        CPy_TypeError("str", obj_output); 
        goto fail;
    }
    CPyTagged arg_n_cpus;
    if (likely(PyLong_Check(obj_n_cpus)))
        arg_n_cpus = CPyTagged_BorrowFromObject(obj_n_cpus);
    else {
        CPy_TypeError("int", obj_n_cpus); goto fail;
    }
    PyObject *retval = CPyDef_read_file_in_chunks(arg_file_path, arg_output, arg_n_cpus);
    return retval;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "read_file_in_chunks", 96, CPyStatic_globals);
    return NULL;
}

char CPyDef_process_fasta_file(PyObject *cpy_r_file_path, PyObject *cpy_r_output, CPyTagged cpy_r_n_cpus) {
    PyObject *cpy_r_r0;
    char cpy_r_r1;
    cpy_r_r0 = CPyDef_read_file_in_chunks(cpy_r_file_path, cpy_r_output, cpy_r_n_cpus);
    if (unlikely(cpy_r_r0 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "process_fasta_file", 119, CPyStatic_globals);
        goto CPyL2;
    } else
        goto CPyL3;
CPyL1: ;
    return 1;
CPyL2: ;
    cpy_r_r1 = 2;
    return cpy_r_r1;
CPyL3: ;
    CPy_DECREF(cpy_r_r0);
    goto CPyL1;
}

PyObject *CPyPy_process_fasta_file(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames) {
    static const char * const kwlist[] = {"file_path", "output", "n_cpus", 0};
    static CPyArg_Parser parser = {"OOO:process_fasta_file", kwlist, 0};
    PyObject *obj_file_path;
    PyObject *obj_output;
    PyObject *obj_n_cpus;
    if (!CPyArg_ParseStackAndKeywordsSimple(args, nargs, kwnames, &parser, &obj_file_path, &obj_output, &obj_n_cpus)) {
        return NULL;
    }
    PyObject *arg_file_path;
    if (likely(PyUnicode_Check(obj_file_path)))
        arg_file_path = obj_file_path;
    else {
        CPy_TypeError("str", obj_file_path); 
        goto fail;
    }
    PyObject *arg_output;
    if (likely(PyUnicode_Check(obj_output)))
        arg_output = obj_output;
    else {
        CPy_TypeError("str", obj_output); 
        goto fail;
    }
    CPyTagged arg_n_cpus;
    if (likely(PyLong_Check(obj_n_cpus)))
        arg_n_cpus = CPyTagged_BorrowFromObject(obj_n_cpus);
    else {
        CPy_TypeError("int", obj_n_cpus); goto fail;
    }
    char retval = CPyDef_process_fasta_file(arg_file_path, arg_output, arg_n_cpus);
    if (retval == 2) {
        return NULL;
    }
    PyObject *retbox = Py_None;
    CPy_INCREF(retbox);
    return retbox;
fail: ;
    CPy_AddTraceback("process_fasta_input.py", "process_fasta_file", 118, CPyStatic_globals);
    return NULL;
}

char CPyDef___top_level__(void) {
    PyObject *cpy_r_r0;
    PyObject *cpy_r_r1;
    char cpy_r_r2;
    PyObject *cpy_r_r3;
    PyObject *cpy_r_r4;
    PyObject **cpy_r_r5;
    PyObject **cpy_r_r6;
    PyObject **cpy_r_r7;
    PyObject **cpy_r_r8;
    PyObject **cpy_r_r9;
    void *cpy_r_r11;
    void *cpy_r_r13;
    PyObject *cpy_r_r14;
    PyObject *cpy_r_r15;
    PyObject *cpy_r_r16;
    PyObject *cpy_r_r17;
    char cpy_r_r18;
    PyObject *cpy_r_r19;
    PyObject *cpy_r_r20;
    PyObject *cpy_r_r21;
    PyObject *cpy_r_r22;
    PyObject *cpy_r_r23;
    PyObject *cpy_r_r24;
    PyObject *cpy_r_r25;
    PyObject *cpy_r_r26;
    PyObject **cpy_r_r28;
    PyObject *cpy_r_r29;
    CPyTagged cpy_r_r30;
    PyObject *cpy_r_r31;
    PyObject *cpy_r_r32;
    PyObject *cpy_r_r33;
    int32_t cpy_r_r34;
    char cpy_r_r35;
    char cpy_r_r36;
    cpy_r_r0 = CPyModule_builtins;
    cpy_r_r1 = (PyObject *)&_Py_NoneStruct;
    cpy_r_r2 = cpy_r_r0 != cpy_r_r1;
    if (cpy_r_r2) goto CPyL3;
    cpy_r_r3 = CPyStatics[45]; /* 'builtins' */
    cpy_r_r4 = PyImport_Import(cpy_r_r3);
    if (unlikely(cpy_r_r4 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "<module>", -1, CPyStatic_globals);
        goto CPyL10;
    }
    CPyModule_builtins = cpy_r_r4;
    CPy_INCREF(CPyModule_builtins);
    CPy_DECREF(cpy_r_r4);
CPyL3: ;
    cpy_r_r5 = (PyObject **)&CPyModule_argparse;
    cpy_r_r6 = (PyObject **)&CPyModule_os;
    cpy_r_r7 = (PyObject **)&CPyModule_time;
    cpy_r_r8 = (PyObject **)&CPyModule_mmap;
    cpy_r_r9 = (PyObject **)&CPyModule_multiprocessing;
    PyObject **cpy_r_r10[5] = {cpy_r_r5, cpy_r_r6, cpy_r_r7, cpy_r_r8, cpy_r_r9};
    cpy_r_r11 = (void *)&cpy_r_r10;
    int64_t cpy_r_r12[5] = {1, 2, 3, 4, 5};
    cpy_r_r13 = (void *)&cpy_r_r12;
    cpy_r_r14 = CPyStatics[74]; /* (('argparse', 'argparse', 'argparse'), ('os', 'os', 'os'),
                                   ('time', 'time', 'time'), ('mmap', 'mmap', 'mmap'),
                                   ('multiprocessing', 'multiprocessing', 'multiprocessing')) */
    cpy_r_r15 = CPyStatic_globals;
    cpy_r_r16 = CPyStatics[50]; /* 'process_fasta_input.py' */
    cpy_r_r17 = CPyStatics[51]; /* '<module>' */
    cpy_r_r18 = CPyImport_ImportMany(cpy_r_r14, cpy_r_r11, cpy_r_r15, cpy_r_r16, cpy_r_r17, cpy_r_r13);
    if (!cpy_r_r18) goto CPyL10;
    cpy_r_r19 = CPyStatics[75]; /* ('Dict', 'Union', 'List') */
    cpy_r_r20 = CPyStatics[55]; /* 'typing' */
    cpy_r_r21 = CPyStatic_globals;
    cpy_r_r22 = CPyImport_ImportFromMany(cpy_r_r20, cpy_r_r19, cpy_r_r19, cpy_r_r21);
    if (unlikely(cpy_r_r22 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "<module>", 6, CPyStatic_globals);
        goto CPyL10;
    }
    CPyModule_typing = cpy_r_r22;
    CPy_INCREF(CPyModule_typing);
    CPy_DECREF(cpy_r_r22);
    cpy_r_r23 = CPyStatics[56]; /* 'SC_PAGE_SIZE' */
    cpy_r_r24 = CPyModule_os;
    cpy_r_r25 = CPyStatics[57]; /* 'sysconf' */
    cpy_r_r26 = CPyObject_GetAttr(cpy_r_r24, cpy_r_r25);
    if (unlikely(cpy_r_r26 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "<module>", 9, CPyStatic_globals);
        goto CPyL10;
    }
    PyObject *cpy_r_r27[1] = {cpy_r_r23};
    cpy_r_r28 = (PyObject **)&cpy_r_r27;
    cpy_r_r29 = _PyObject_Vectorcall(cpy_r_r26, cpy_r_r28, 1, 0);
    CPy_DECREF(cpy_r_r26);
    if (unlikely(cpy_r_r29 == NULL)) {
        CPy_AddTraceback("process_fasta_input.py", "<module>", 9, CPyStatic_globals);
        goto CPyL10;
    }
    if (likely(PyLong_Check(cpy_r_r29)))
        cpy_r_r30 = CPyTagged_FromObject(cpy_r_r29);
    else {
        CPy_TypeError("int", cpy_r_r29); cpy_r_r30 = CPY_INT_TAG;
    }
    CPy_DECREF(cpy_r_r29);
    if (unlikely(cpy_r_r30 == CPY_INT_TAG)) {
        CPy_AddTraceback("process_fasta_input.py", "<module>", 9, CPyStatic_globals);
        goto CPyL10;
    }
    cpy_r_r31 = CPyStatic_globals;
    cpy_r_r32 = CPyStatics[11]; /* 'MMAP_PAGE_SIZE' */
    cpy_r_r33 = CPyTagged_StealAsObject(cpy_r_r30);
    cpy_r_r34 = CPyDict_SetItem(cpy_r_r31, cpy_r_r32, cpy_r_r33);
    CPy_DECREF(cpy_r_r33);
    cpy_r_r35 = cpy_r_r34 >= 0;
    if (unlikely(!cpy_r_r35)) {
        CPy_AddTraceback("process_fasta_input.py", "<module>", 9, CPyStatic_globals);
        goto CPyL10;
    }
    return 1;
CPyL10: ;
    cpy_r_r36 = 2;
    return cpy_r_r36;
}

int CPyGlobalsInit(void)
{
    static int is_initialized = 0;
    if (is_initialized) return 0;
    
    CPy_Init();
    CPyModule_process_fasta_input = Py_None;
    CPyModule_builtins = Py_None;
    CPyModule_argparse = Py_None;
    CPyModule_os = Py_None;
    CPyModule_time = Py_None;
    CPyModule_mmap = Py_None;
    CPyModule_multiprocessing = Py_None;
    CPyModule_typing = Py_None;
    if (CPyStatics_Initialize(CPyStatics, CPyLit_Str, CPyLit_Bytes, CPyLit_Int, CPyLit_Float, CPyLit_Complex, CPyLit_Tuple, CPyLit_FrozenSet) < 0) {
        return -1;
    }
    is_initialized = 1;
    return 0;
}

PyObject *CPyStatics[76];
const char * const CPyLit_Str[] = {
    "\v\001\n\000\005UTF-8\005write\006rstrip\areplace\005split\001 \016MMAP_PAGE_SIZE\nfastafile_\004.faa",
    "\n\004path\004join\006remove\aOSError\016fasta-headers_\004.txt\001a\004open\003r+b\b__exit__",
    "\n\t__enter__\006fileno\vACCESS_READ\004mmap\006access\006offset\004seek\breadline\004iter\001\r",
    "\v\001>\001*\001[\001r\agetsize\006length\004find\004Pool\tprocesses\rprocess_chunk\astarmap",
    "\006\bbuiltins\bargparse\002os\004time\017multiprocessing\026process_fasta_input.py",
    "\a\b<module>\004Dict\005Union\004List\006typing\fSC_PAGE_SIZE\asysconf",
    "",
};
const char * const CPyLit_Bytes[] = {
    "\a\001\n\001\r\001>\001 \001*\001[\000",
    "",
};
const char * const CPyLit_Int[] = {
    "\0010",
    "",
};
const double CPyLit_Float[] = {0};
const double CPyLit_Complex[] = {0};
const int CPyLit_Tuple[] = {
    10, 2, 28, 29, 2, 39, 28, 1, 42, 3, 46, 46, 46, 3, 47, 47, 47, 3,
    48, 48, 48, 3, 27, 27, 27, 3, 49, 49, 49, 5, 69, 70, 71, 72, 73, 3,
    52, 53, 54
};
const int CPyLit_FrozenSet[] = {0};
CPyModule *CPyModule_process_fasta_input_internal = NULL;
CPyModule *CPyModule_process_fasta_input;
PyObject *CPyStatic_globals;
CPyModule *CPyModule_builtins;
CPyModule *CPyModule_argparse;
CPyModule *CPyModule_os;
CPyModule *CPyModule_time;
CPyModule *CPyModule_mmap;
CPyModule *CPyModule_multiprocessing;
CPyModule *CPyModule_typing;
tuple_T3IOO CPyDef_process_line(PyObject *cpy_r_line, PyObject *cpy_r_ff, PyObject *cpy_r_fh);
PyObject *CPyPy_process_line(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_align_offset(PyObject *cpy_r_offset, PyObject *cpy_r_page_size);
PyObject *CPyPy_align_offset(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
char CPyDef_process_chunk(PyObject *cpy_r_file_path, PyObject *cpy_r_start_byte, PyObject *cpy_r_end_byte, CPyTagged cpy_r_file_counter, PyObject *cpy_r_output);
PyObject *CPyPy_process_chunk(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
tuple_T3IOO CPyDef_process_line_no_write(PyObject *cpy_r_line);
PyObject *CPyPy_process_line_no_write(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_process_whole_file(PyObject *cpy_r_file_path);
PyObject *CPyPy_process_whole_file(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
tuple_T2OO CPyDef_process_genome(PyObject *cpy_r_d, PyObject *cpy_r_seq, tuple_T3IOO cpy_r_line);
PyObject *CPyPy_process_genome(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
PyObject *CPyDef_read_file_in_chunks(PyObject *cpy_r_file_path, PyObject *cpy_r_output, CPyTagged cpy_r_n_cpus);
PyObject *CPyPy_read_file_in_chunks(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
char CPyDef_process_fasta_file(PyObject *cpy_r_file_path, PyObject *cpy_r_output, CPyTagged cpy_r_n_cpus);
PyObject *CPyPy_process_fasta_file(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
char CPyDef___top_level__(void);
