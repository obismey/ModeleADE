#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULPROJECTIONMP_H
#define CALCULPROJECTIONMP_H

#include "EtatProjection.h"
#include "CalculVarEtatPret.h"
#include "CalculEcheancier.h"
#include "CalculAssurance.h"
#include "CalculAssiettesPrimes.h"
#include "CalculDcPtia.h"
#include "CalculIttIpt.h"


void CalculProjectionMP(
    EtatProjection* etat,
    double ID_MP, 
    double DUREE_AMORT_MOIS, 
    double DUREE_DIFF_MOIS,
    double DEBUT_PRET_MOIS,
    double CI_ASSURE , 
    double DIFFERE_TYPE,   
    double TXNOM_TYPE_MENS, 
    double TXNOM_ANN, 
    double AGE_SOUS_ANN, 
    double AGE_FIN_DC_ANN,
    double AGE_FIN_AT_ANN, 
    double PART_H, 
    double PART_IMMO,
    double PART_PERSO,
    double TXACTUMENS,
    double PRIX_PTIA_POURCDCSEUL,
    double ABT_AT_PERTEREV,
    double NombrePeriodes)
;

List Simulate(
    NumericVector ID_MP, 
    NumericVector DUREE_AMORT_MOIS, 
    NumericVector DUREE_DIFF_MOIS,
    NumericVector DEBUT_PRET_MOIS,
    NumericVector CI_ASSURE , 
    NumericVector DIFFERE_TYPE,   
    NumericVector TXNOM_TYPE_MENS, 
    NumericVector TXNOM_ANN, 
    NumericVector AGE_SOUS_ANN, 
    NumericVector AGE_FIN_DC_ANN,
    NumericVector AGE_FIN_AT_ANN, 
    NumericVector PART_H, 
    NumericVector PART_IMMO,
    NumericVector PART_PERSO,
    NumericVector TXACTUMENS,
    NumericVector PRIX_PTIA_POURCDCSEUL,
    NumericVector ABT_AT_PERTEREV,
    double NombrePeriodes)
  ;
List SimulateAgg(
    NumericVector ID_MP, 
    NumericVector ID_MP_AGG,
    NumericVector DUREE_AMORT_MOIS, 
    NumericVector DUREE_DIFF_MOIS,
    NumericVector DEBUT_PRET_MOIS,
    NumericVector CI_ASSURE , 
    NumericVector DIFFERE_TYPE,   
    NumericVector TXNOM_TYPE_MENS, 
    NumericVector TXNOM_ANN, 
    NumericVector AGE_SOUS_ANN, 
    NumericVector AGE_FIN_DC_ANN,
    NumericVector AGE_FIN_AT_ANN, 
    NumericVector PART_H, 
    NumericVector PART_IMMO,
    NumericVector PART_PERSO,
    NumericVector TXACTUMENS,
    NumericVector PRIX_PTIA_POURCDCSEUL,
    NumericVector ABT_AT_PERTEREV,
    NumericVector Periodes_AGG)
  ;
#endif