/***************************************************************************
 Public methods:
 anyMissing(SEXP x, SEXP idxs)

 TO DO: Support list():s too.

 Copyright Henrik Bengtsson, 2007
 **************************************************************************/
#include <Rdefines.h>
#include "types.h"
#include "utils.h"


/*
Native API (dynamically generated via macros):

int anyMissing_internal_noIdxs(SEXP x, void *idxs, R_xlen_t nidxs)
int anyMissing_internal_intIdxs(SEXP x, void *idxs, R_xlen_t nidxs)
int anyMissing_internal_realIdxs(SEXP x, void *idxs, R_xlen_t nidxs)
*/

#define METHOD anyMissing
#define METHOD_NAME anyMissing_internal
#define RETURN_TYPE int
#define ARGUMENTS_LIST SEXP x, void *idxs, R_xlen_t nidxs

#include "templates-gen-vector.h"


SEXP anyMissing(SEXP x, SEXP idxs) {
  SEXP ans;
  R_xlen_t nx;

  nx = xlength(x);

  /* Argument 'idxs': */
  R_xlen_t nidxs;
  int idxsType;
  void *cidxs = validateIndices(idxs, nx, 1, &nidxs, &idxsType);

  PROTECT(ans = allocVector(LGLSXP, 1));
  LOGICAL(ans)[0] = 0;

  /* anyMissing() on zero-length objects should always return FALSE,
     just like any(double(0)). */
  if (nidxs == 0) {
    UNPROTECT(1);
    return(ans);
  }

  LOGICAL(ans)[0] = anyMissing_internal[idxsType](x, cidxs, nidxs);

  UNPROTECT(1); /* ans */

  return(ans);
} // anyMissing()


/***************************************************************************
 HISTORY:
 2015-06-14 [DJ]
  o Supported subsetted computation.
 2007-08-14 [HB]
  o Created using do_isna() in src/main/coerce.c as a template.
 **************************************************************************/
