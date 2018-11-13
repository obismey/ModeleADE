#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULITTIPT_H
#define CALCULITTIPT_H

#include "EtatProjection.h"

void CalculIttIpt(
    EtatProjection* etat, 
    double DUREE_DIFF_MOIS,
    double AGE_SOUS_ANN, 
    double PART_H, 
    double PART_IMMO,
    double PART_PERSO,
    double AGE_FIN_AT_ANN,
    double ABT_AT_PERTEREV, 
    double TXACTUMENS,
    double TBLENTREEAT(double,double,double) , 
    double TBLEMAINTIENAT(double,double))
;


void CalculConstitIttIpt(
    EtatProjection* etat, 
    double DUREE_DIFF_MOIS,
    double AGE_SOUS_ANN, 
    double PART_H, 
    double PART_IMMO,
    double PART_PERSO,
    double AGE_FIN_AT_ANN,
    double ABT_AT_PERTEREV, 
    double TXACTUMENS,
    double TBLENTREEAT(double,double,double) , 
    double TBLECONSTITMAINTIENAT(double,double))
;

#endif
