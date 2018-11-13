#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULDCPTIA_CPP
#define CALCULDCPTIA_CPP

#include "CalculDcPtia.h"

void CalculDcPtia(
    EtatProjection* etat,
    double PRIX_PTIA_POURCDCSEUL, 
    double TXACTUMENS)
{
  etat->Effectif_DcPtia = etat->Assu_TxMortMens  * etat->Assu_ProbSurvieCreditDebPer * etat->Assu_EstAssureDC;
  
  etat->DcPtia_PrestProableDcPtia = etat->Effectif_DcPtia * etat->Ech_CRDDebPer * (1+ PRIX_PTIA_POURCDCSEUL);
  
  etat->DcPtia_VAN_Sin = etat->DcPtia_PrestProableDcPtia * pow( 1+TXACTUMENS,-(etat->Periode-0.5));
  
  etat->Res_VAN_Sin_DCPTIA += etat->DcPtia_VAN_Sin;
}

#endif
