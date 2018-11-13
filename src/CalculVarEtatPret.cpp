#include <Rcpp.h>
using namespace Rcpp;


#ifndef CALCULVARETATPRET_CPP
#define CALCULVARETATPRET_CPP

#include "CalculVarEtatPret.h"


void CalculVarEtatPret(
    EtatProjection* etat,
    double DUREE_AMORT_MOIS, 
    double DUREE_DIFF_MOIS,
    double DEBUT_PRET_MOIS)
{
  etat->EtatPret_EstEnCours = 
    (etat->Periode >= DEBUT_PRET_MOIS) && 
    (etat->Periode <= (DUREE_DIFF_MOIS + DUREE_AMORT_MOIS + DEBUT_PRET_MOIS - 1) );
  
  etat->EtatPret_EstDiffereEnCours = 
    (etat->Periode >= DEBUT_PRET_MOIS) && 
    (etat->Periode <= (DUREE_DIFF_MOIS + DEBUT_PRET_MOIS - 1) );
  
}

#endif

