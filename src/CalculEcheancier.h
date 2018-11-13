#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULECHEANCIER_H
#define CALCULECHEANCIER_H

#include "EtatProjection.h"

void CalculEcheancier (
    EtatProjection* etat,
    double CI_ASSURE , 
    double DUREE_AMORT_MOIS,
    double DUREE_DIFF_MOIS , 
    double DIFFERE_TYPE  ,  /* 1 == "Partiel" */ 
    double TXNOM_TYPE_MENS, /* 1 == "Proportionnel" */ 
    double TXNOM_ANN)
;

#endif
