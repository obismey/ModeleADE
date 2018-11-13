#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULECHEANCIER_CPP
#define CALCULECHEANCIER_CPP

#include "CalculEcheancier.h"

void CalculEcheancier (
    EtatProjection* etat,
    double CI_ASSURE , 
    double DUREE_AMORT_MOIS,
    double DUREE_DIFF_MOIS , 
    double DIFFERE_TYPE  ,  /* 1 == "Partiel" */ 
    double TXNOM_TYPE_MENS, /* 1 == "Proportionnel" */ 
    double TXNOM_ANN)
{
  if(etat->Periode == 1.0)
  {
    etat->Ech_TxNomMens = TXNOM_TYPE_MENS == 1 ? TXNOM_ANN / 12.0  : pow( 1 + TXNOM_ANN, 1.0/12.0)-1 ;
    
    etat->Ech_MensPer_Diff = DUREE_DIFF_MOIS > 0 && DIFFERE_TYPE == 1  ? CI_ASSURE * etat->Ech_TxNomMens : 0;
    
    etat->Ech_MensPer_amort  = 
      etat->Ech_TxNomMens == 0 ?
      CI_ASSURE / DUREE_AMORT_MOIS :
      CI_ASSURE * etat->Ech_TxNomMens / (1-pow(1+etat->Ech_TxNomMens,-DUREE_AMORT_MOIS));
    
    etat->Ech_CRDDebPer = CI_ASSURE;
    etat->Ech_InteretsPer = 0.0;
    etat->Ech_MensPer =0.0;
  }
  
  etat->Ech_CRDDebPer= etat->EtatPret_EstEnCours*(etat->Ech_CRDDebPer + etat->Ech_InteretsPer - etat->Ech_MensPer);
  etat->Ech_InteretsPer = etat->Ech_CRDDebPer * etat->Ech_TxNomMens;
  etat->Ech_MensPer = etat->EtatPret_EstDiffereEnCours ? etat->Ech_MensPer_Diff : etat->Ech_MensPer_amort;
  etat->Ech_DureeRestPretDebPer = DUREE_AMORT_MOIS+DUREE_DIFF_MOIS - etat->Periode + 1;
  etat->Ech_AMortPer = etat->Ech_MensPer - etat->Ech_InteretsPer;
}

#endif
