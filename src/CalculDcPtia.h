#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULDCPTIA_H
#define CALCULDCPTIA_H

#include "EtatProjection.h"

void CalculDcPtia(
    EtatProjection* etat,
    double PRIX_PTIA_POURCDCSEUL, 
    double TXACTUMENS)
;

#endif
