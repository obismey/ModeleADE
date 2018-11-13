#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULASSIETTESPRIMES_CPP
#define CALCULASSIETTESPRIMES_CPP

#include "CalculAssiettesPrimes.h"

void CalculAssiettesPrimes(
    EtatProjection* etat,
    double CI_ASSURE,
    double TXACTUMENS)
{
  etat->Primes_TxActuEtSurvie =  
    etat->Assu_EstPaiementAssurance * etat->Assu_ProbSurvieCreditDebPer * pow(1+TXACTUMENS,-(etat->Periode-1));
  
  etat->Effectif_Valide = etat->Primes_TxActuEtSurvie;
  
  etat->Primes_VAN_AssietteCI = CI_ASSURE * etat->Primes_TxActuEtSurvie;
  etat->Primes_VAN_AssietteCRD = etat->Ech_CRDDebPer * etat->Primes_TxActuEtSurvie;
  
  etat->Res_VAN_AssietteCI += etat->Primes_VAN_AssietteCI;
  etat->Res_VAN_AssietteCRD += etat->Primes_VAN_AssietteCRD;
}

#endif
