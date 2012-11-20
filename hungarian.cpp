/*
  hungarian
  Harold Cooper <hbc@mit.edu>
  hungarian.cpp 2004-09-02
*/

#include "Python.h"
#include "numpy/arrayobject.h"
#include "asp.h"

static PyObject *
hungarian(PyObject *self, PyObject *args)
//hungarian(costs)
{
  PyObject *ocosts;
  PyArrayObject *costs;
  int n;
  npy_intp n2;
  long *rowsol;
  long *colsol;
  cost *buf,**ccosts;
  npy_intp *strides;
  PyObject * rowo;
  PyObject * colo;

  if (!PyArg_ParseTuple(args, "O", &ocosts))
    return NULL;
  costs = (PyArrayObject*)PyArray_FromAny(
                                          ocosts,PyArray_DescrFromType(COST_TYPE_NPY),2,2,
                                          NPY_CONTIGUOUS|NPY_ALIGNED|NPY_FORCECAST,0
                                          );

  if (costs->nd!=2)
    {
      PyErr_SetString(PyExc_ValueError,"lap() requires a 2-D matrix");
      goto error;
    }
  n = costs->dimensions[0];
  n2 = costs->dimensions[0];
  if (costs->dimensions[1]!=n)
    {
      PyErr_SetString(PyExc_ValueError,"lap() requires a square matrix");
      goto error;
    }

  //get inputted matrix as a 1-D C array:
  buf = (cost*)PyArray_DATA(costs);

  //copy inputted matrix into a 2-dimensional C array:
  strides = PyArray_STRIDES(costs);
  assert(strides[1] == sizeof(cost));
  ccosts = (cost **)malloc(sizeof(cost *)*n);
  if(!ccosts)
    {
      PyErr_NoMemory();
      free(ccosts);
      goto error;
    }
  for(int i=0;i<n;i++)
    ccosts[i] = buf+i*(strides[0]/sizeof(cost));

  //allocate data for the output array
  rowo = PyArray_SimpleNew(1, &n2, NPY_LONG);
  colo = PyArray_SimpleNew(1, &n2, NPY_LONG);
  rowsol = (long *) PyArray_DATA(rowo);
  colsol = (long *) PyArray_DATA(colo);
  if(!(rowsol&&colsol))
    {
      PyErr_NoMemory();
      free(ccosts);
      goto error;
    }

  //run hungarian!:
  asp(n,ccosts,rowsol,colsol);

  //NA_InputArray() incremented costs, but now we're done with it, so let it get GC'ed:
  Py_XDECREF(costs);

  free(ccosts);
  return Py_BuildValue("(NN)",
                       rowo, colo
                       );
 error:
  Py_XDECREF(costs);
  return NULL;
}

static PyMethodDef HungarianMethods[] = {
  {"lap",  hungarian, METH_VARARGS,
   "Solves the linear assignment problem using the Hungarian\nalgorithm.\n\nhungarian() takes a single argument - a square cost matrix - and returns a\ntuple of the form\n(row_assigns,col_assigns)."},
  {NULL, NULL, 0, NULL}        /* Sentinel (terminates structure) */
};

PyMODINIT_FUNC
inithungarian(void)
{
  (void) Py_InitModule("hungarian", HungarianMethods);
  import_array();
}

int
main(int argc, char *argv[])
{
  /* Pass argv[0] to the Python interpreter */
  Py_SetProgramName(argv[0]);

  /* Initialize the Python interpreter.  Required. */
  Py_Initialize();

  /* Add a static module */
  inithungarian();

  return 0;
}
