#include <Rcpp.h>
using namespace Rcpp;


#ifndef CALCULASSURANCE_CPP
#define CALCULASSURANCE_CPP

#include "CalculAssurance.h"

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
{
  
  etat->Assu_AgeAnnee = floor((AGE_SOUS_ANN*12 + etat->Periode - 1)/12);
  
  etat->Assu_EstAssureDC = (etat->Assu_AgeAnnee < AGE_FIN_DC_ANN)*etat->EtatPret_EstEnCours;
  etat->Assu_EstAssureAT = (etat->Assu_AgeAnnee < AGE_FIN_AT_ANN)*etat->EtatPret_EstEnCours;
  etat->Assu_EstPaiementAssurance = etat->Assu_EstAssureDC;
  
  etat->Assu_ProbSurvieCreditDebPer = 
    etat->Periode == 1.0 ? 1.0 :
    etat->Assu_ProbSurvieCreditDebPer * (1-etat->Assu_TxMortMens)*(1-etat->Assu_TxRAMens) * etat->EtatPret_EstEnCours;
  
  double Assu_TxRAAnn  = 
    TBLERACHAT(1, etat->Ech_DureeRestPretDebPer)*PART_IMMO + 
    TBLERACHAT(2, etat->Ech_DureeRestPretDebPer)*PART_PERSO +
    TBLERACHAT(3, etat->Ech_DureeRestPretDebPer)*(1 - PART_IMMO - PART_PERSO) ;
  
  etat->Assu_TxRAMens = 1.0-pow(1.0-Assu_TxRAAnn,1.0/12.0);
  
  double Assu_TxMortAnn = 
    (PART_H*TBLEMORT(1, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLEMORT(1, 2, etat->Assu_AgeAnnee))*PART_IMMO + 
    (PART_H*TBLEMORT(2, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLEMORT(2, 2, etat->Assu_AgeAnnee))*PART_PERSO+ 
    (PART_H*TBLEMORT(3, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLEMORT(3, 2, etat->Assu_AgeAnnee))*(1 - PART_IMMO - PART_PERSO);
  
  etat->Assu_TxMortMens = 1.0-pow(1.0-Assu_TxMortAnn,1.0/12.0);
  
  
  
}

#endif