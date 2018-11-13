#include <Rcpp.h>
using namespace Rcpp;


#ifndef CALCULASSURANCE_H
#define CALCULASSURANCE_H

#include "EtatProjection.h"

void CalculAssurance(
    EtatProjection* etat, 
    double AGE_SOUS_ANN, 
    double AGE_FIN_DC_ANN,
    double AGE_FIN_AT_ANN, 
    double PART_H, 
    double PART_IMMO,
    double PART_PERSO,
    double TBLEMORT(double,double,double) , /* type de pret, sexe , age */
    double TBLERACHAT(double,double)) /*type de pret , duree restante */
;

#endif