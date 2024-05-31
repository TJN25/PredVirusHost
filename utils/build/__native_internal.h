#ifndef MYPYC_NATIVE_INTERNAL_H
#define MYPYC_NATIVE_INTERNAL_H
#include <Python.h>
#include <CPy.h>
#include "__native.h"

int CPyGlobalsInit(void);

extern PyObject *CPyStatics[76];
extern const char * const CPyLit_Str[];
extern const char * const CPyLit_Bytes[];
extern const char * const CPyLit_Int[];
extern const double CPyLit_Float[];
extern const double CPyLit_Complex[];
extern const int CPyLit_Tuple[];
extern const int CPyLit_FrozenSet[];
extern CPyModule *CPyModule_process_fasta_input_internal;
extern CPyModule *CPyModule_process_fasta_input;
extern PyObject *CPyStatic_globals;
extern CPyModule *CPyModule_builtins;
extern CPyModule *CPyModule_argparse;
extern CPyModule *CPyModule_os;
extern CPyModule *CPyModule_time;
extern CPyModule *CPyModule_mmap;
extern CPyModule *CPyModule_multiprocessing;
extern CPyModule *CPyModule_typing;
extern tuple_T3IOO CPyDef_process_line(PyObject *cpy_r_line, PyObject *cpy_r_ff, PyObject *cpy_r_fh);
extern PyObject *CPyPy_process_line(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_align_offset(PyObject *cpy_r_offset, PyObject *cpy_r_page_size);
extern PyObject *CPyPy_align_offset(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern char CPyDef_process_chunk(PyObject *cpy_r_file_path, PyObject *cpy_r_start_byte, PyObject *cpy_r_end_byte, CPyTagged cpy_r_file_counter, PyObject *cpy_r_output);
extern PyObject *CPyPy_process_chunk(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern tuple_T3IOO CPyDef_process_line_no_write(PyObject *cpy_r_line);
extern PyObject *CPyPy_process_line_no_write(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_process_whole_file(PyObject *cpy_r_file_path);
extern PyObject *CPyPy_process_whole_file(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern tuple_T2OO CPyDef_process_genome(PyObject *cpy_r_d, PyObject *cpy_r_seq, tuple_T3IOO cpy_r_line);
extern PyObject *CPyPy_process_genome(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern PyObject *CPyDef_read_file_in_chunks(PyObject *cpy_r_file_path, PyObject *cpy_r_output, CPyTagged cpy_r_n_cpus);
extern PyObject *CPyPy_read_file_in_chunks(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern char CPyDef_process_fasta_file(PyObject *cpy_r_file_path, PyObject *cpy_r_output, CPyTagged cpy_r_n_cpus);
extern PyObject *CPyPy_process_fasta_file(PyObject *self, PyObject *const *args, size_t nargs, PyObject *kwnames);
extern char CPyDef___top_level__(void);
#endif
