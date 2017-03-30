/***************************************************************************
 Public methods:
 SEXP meanOver(SEXP x, SEXP idxs, SEXP naRm, SEXP refine)

 Copyright Henrik Bengtsson, 2014
 **************************************************************************/
#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):

double meanOver_int_aidxs(int *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine)
double meanOver_int_iidxs(int *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine)
double meanOver_int_didxs(int *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine)
double meanOver_dbl_aidxs(double *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine)
double meanOver_dbl_iidxs(double *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine)
double meanOver_dbl_didxs(double *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine)
*/

#define METHOD meanOver
#define RETURN_TYPE double
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nx, void *idxs, R_xlen_t nidxs, int narm, int refine

#define X_TYPE 'i'
#include "000.templates-gen-vector.h"
#define X_TYPE 'r'
#include "000.templates-gen-vector.h"


SEXP meanOver(SEXP x, SEXP idxs, SEXP naRm, SEXP refine) {
  SEXP ans;
  R_xlen_t nx;
  int narm, refine2;
  double avg = NA_REAL;

  /* Argument 'x': */
  assertArgVector(x, (R_TYPE_INT | R_TYPE_REAL), "x");
  nx = xlength(x);

  /* Argument 'naRm': */
  narm = asLogicalNoNA(naRm, "na.rm");

  /* Argument 'refine': */
  refine2 = asLogicalNoNA(refine, "refine");

  /* Argument 'idxs': */
  R_xlen_t nidxs;
  int idxsType;
  void *cidxs = validateIndices(idxs, nx, 1, &nidxs, &idxsType);

  /* Double matrices are more common to use. */
  if (isReal(x)) {
    avg = meanOver_dbl[idxsType](REAL(x), nx, cidxs, nidxs, narm, refine2);
  } else if (isInteger(x)) {
    avg = meanOver_int[idxsType](INTEGER(x), nx, cidxs, nidxs, narm, refine2);
  }

  /* Return results */
  PROTECT(ans = allocVector(REALSXP, 1));
  REAL(ans)[0] = avg;
  UNPROTECT(1);

  return(ans);
} // meanOver()


/***************************************************************************
 HISTORY:
 2015-07-04 [DJ]
  o Supported subsetted computation.
 2014-11-02 [HB]
  o Created.
 **************************************************************************/
