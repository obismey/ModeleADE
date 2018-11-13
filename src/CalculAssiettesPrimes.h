#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULASSIETTESPRIMES_H
#define CALCULASSIETTESPRIMES_H

#include "EtatProjection.h"

void CalculAssiettesPrimes(
    EtatProjection* etat,
    double CI_ASSURE,
    double TXACTUMENS);

#endif
