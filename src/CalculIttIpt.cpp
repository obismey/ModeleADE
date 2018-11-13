#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULITTIPT_CPP
#define CALCULITTIPT_CPP

#include "CalculIttIpt.h"

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
{
  
  double ITTIPT_TxAnnEntree3Mois = 
    (PART_H*TBLENTREEAT(1, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLENTREEAT(1, 2, etat->Assu_AgeAnnee))*PART_IMMO + 
    (PART_H*TBLENTREEAT(2, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLENTREEAT(2, 2, etat->Assu_AgeAnnee))*PART_PERSO+ 
    (PART_H*TBLENTREEAT(3, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLENTREEAT(3, 2, etat->Assu_AgeAnnee))*(1 - PART_IMMO - PART_PERSO);
  
  etat->ITTIPT_TxMensEntree3Mois = 1.0-pow(1.0-ITTIPT_TxAnnEntree3Mois,1.0/12.0);
  
  double ITTIPT_NbMoisRestCouvDebPer = 
    std::max(
      std::min(
        etat->Ech_DureeRestPretDebPer,
        (AGE_FIN_AT_ANN-AGE_SOUS_ANN)*12-etat->Periode+1)
    ,0.0);
  
  
  if(ITTIPT_NbMoisRestCouvDebPer > 3)
  {
    double CapConstit =0.0;
    for(double i=3.0; i < ITTIPT_NbMoisRestCouvDebPer; i++ )
    {
      double mensualiate_at = (i+etat->Periode)<= DUREE_DIFF_MOIS ? etat->Ech_MensPer_Diff : etat->Ech_MensPer_amort;
      CapConstit +=  (TBLEMAINTIENAT(etat->Assu_AgeAnnee, i)/TBLEMAINTIENAT(etat->Assu_AgeAnnee, 3.0))*pow(1+TXACTUMENS, -i)*mensualiate_at;
    }
    
    etat->Effectif_ITTIPT = etat->Assu_ProbSurvieCreditDebPer * etat->ITTIPT_TxMensEntree3Mois * CapConstit 
      * etat->Assu_EstAssureAT * pow(1+TXACTUMENS,-(etat->Periode -0.5));
    
    etat->ITTIPT_VAN_Sin =  etat->Effectif_ITTIPT * (1.0 - ABT_AT_PERTEREV) ;
  }
  else
  {
    etat->ITTIPT_VAN_Sin = 0.0;
    etat->Effectif_ITTIPT = 0.0;
  }
  
  etat->Res_VAN_Sin_ITTIPT += etat->ITTIPT_VAN_Sin;
}


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
{
  
  double ITTIPT_TxAnnEntree3Mois = 
    (PART_H*TBLENTREEAT(1, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLENTREEAT(1, 2, etat->Assu_AgeAnnee))*PART_IMMO + 
    (PART_H*TBLENTREEAT(2, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLENTREEAT(2, 2, etat->Assu_AgeAnnee))*PART_PERSO+ 
    (PART_H*TBLENTREEAT(3, 1, etat->Assu_AgeAnnee)+(1-PART_H)*TBLENTREEAT(3, 2, etat->Assu_AgeAnnee))*(1 - PART_IMMO - PART_PERSO);
  
  etat->ITTIPT_TxMensEntree3Mois = 1.0-pow(1.0-ITTIPT_TxAnnEntree3Mois,1.0/12.0);
  
  double ITTIPT_NbMoisRestCouvDebPer = 
    std::max(
      std::min(
        etat->Ech_DureeRestPretDebPer,
        (AGE_FIN_AT_ANN-AGE_SOUS_ANN)*12-etat->Periode+1)
    ,0.0);
  
  
  if(ITTIPT_NbMoisRestCouvDebPer > 3)
  {
    double CapConstit =TBLECONSTITMAINTIENAT(etat->Assu_AgeAnnee, ITTIPT_NbMoisRestCouvDebPer-1);
    double CapConstitDiff =0.0;
    
    
    if(ITTIPT_NbMoisRestCouvDebPer > 3)
    {
      
    }
    
    
    etat->Effectif_ITTIPT = etat->Assu_ProbSurvieCreditDebPer * etat->ITTIPT_TxMensEntree3Mois * CapConstit 
      * etat->Assu_EstAssureAT * pow(1+TXACTUMENS,-(etat->Periode -0.5));
    
    etat->ITTIPT_VAN_Sin =  etat->Effectif_ITTIPT * (1.0 - ABT_AT_PERTEREV)* etat->Ech_MensPer_amort ;
  }
  else
  {
    etat->ITTIPT_VAN_Sin = 0.0;
    etat->Effectif_ITTIPT = 0.0;
  }
  
  etat->Res_VAN_Sin_ITTIPT += etat->ITTIPT_VAN_Sin;
}

#endif
