#include <Rcpp.h>
using namespace Rcpp;


#ifndef CALCULVARETATPRET_H
#define CALCULVARETATPRET_H

#include "EtatProjection.h"

void CalculVarEtatPret(
    EtatProjection* etat,
    double DUREE_AMORT_MOIS, 
    double DUREE_DIFF_MOIS,
    double DEBUT_PRET_MOIS)
;

#endif

