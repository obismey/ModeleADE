#include <Rcpp.h>
using namespace Rcpp;

#ifndef CALCULPROJECTIONMP_CPP
#define CALCULPROJECTIONMP_CPP

#include "CalculProjectionMP.h"

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
{
  etat->Periode++;
  
  CalculVarEtatPret(etat, DUREE_AMORT_MOIS, DUREE_DIFF_MOIS, DEBUT_PRET_MOIS);
  
  CalculEcheancier(
    etat, 
    CI_ASSURE, 
    DUREE_AMORT_MOIS, DUREE_DIFF_MOIS, DIFFERE_TYPE, 
    TXNOM_TYPE_MENS, TXNOM_ANN);
  
  CalculAssurance(
    etat, 
    AGE_SOUS_ANN, 
    AGE_FIN_DC_ANN, AGE_FIN_AT_ANN,
    PART_H, 
    PART_IMMO, PART_PERSO,
    Table_Morta_Standard, Contante_Table_Rachat);
  
  CalculAssiettesPrimes(etat, CI_ASSURE, TXACTUMENS);
  
  CalculDcPtia(etat, PRIX_PTIA_POURCDCSEUL, TXACTUMENS);
  
  CalculConstitIttIpt(
    etat,
    AGE_SOUS_ANN,
    PART_H, 
    PART_IMMO, PART_PERSO,
    AGE_FIN_AT_ANN, ABT_AT_PERTEREV, TXACTUMENS,
    Table_EntreeAT_Standard, Table_MaintienConstitAT_Standard);
  
}

//' Title
//' Projette les modeles points
//' @param ID_MP
//' Identifiant unique de chaque modele moint
//' @param DUREE_AMORT_MOIS 
//' Duree amortissement du pret ( en mois )
//' @param DUREE_DIFF_MOIS
//' Duree differe du pret ( en mois ) 
//' @param DEBUT_PRET_MOIS
//' Debut du pret à partir de la date de projection  ( en mois )
//' @param CI_ASSURE 
//' Capital emprunte assure ( quotite comprise )
//' @param DIFFERE_TYPE 
//' Type de differe ( 1 == Partiel , 2 == Total )
//' @param TXNOM_TYPE_MENS 
//' Type de mensualisation du taux nominal ( 1 == Proportionnel , 2 == Equivalent )
//' @param TXNOM_ANN 
//' Taux nominal du pret
//' @param AGE_SOUS_ANN 
//' Age a la souscription ( en annees )
//' @param AGE_FIN_DC_ANN 
//' Age fin de la garantie deces ( en annees )
//' @param AGE_FIN_AT_ANN 
//' Age fin  arret de travail ( en annees )
//' @param PART_H 
//' Proportion des hommes
//' @param PART_IMMO 
//' Proportion des prets immos
//' @param PART_PERSO 
//' Proportion des prets persos
//' @param TXACTUMENS 
//' Taux actualisation mensuel
//' @param PRIX_PTIA_POURCDCSEUL 
//' Prix de la PTIA
//' @param ABT_AT_PERTEREV
//' Taux abattement pour la perte de revenu 
//' @param NombrePeriodes 
//' Nombre de mois de projection
//' @return 
//' Une liste de matrices (Nombre de MP * Nombre de Periodes)
//' \item{EtatPret_EstDiffereEnCours}{indique si le prêt est dans sa periode de differe}
//' \item{EtatPret_EstEnCours}{indique si le prêt est en cours}
//' \item{Ech_CRDDebPer}{CRD de debut de periode}
//' \item{Assu_ProbSurvieCreditDebPer}{Probabilite de survie en debut de periode}
//' \item{Assu_TxMortMens}{Taux de mortalite mensuel}
//' \item{Assu_TxRAMens}{Taux de rachat mensuel}
//' \item{Res_VAN_AssietteCI}{VAN assiette  CI}
//' \item{Res_VAN_AssietteCRD}{VAN assiette CRD}
//' \item{DcPtia_VAN_Sin}{VAN sinistre DC}
//' \item{Effectif_DcPtia}{Effectif cumule DC}
//' \item{DcPtia_PrestProableDcPtia}{Prestation probable DC}
//' \item{Res_VAN_Sin_DCPTIA}{VAN Cumule sinistre DC}
//' \item{ITTIPT_VAN_Sin}{VAN sinistre AT}
//' \item{ITTIPT_TxMensEntree3Mois}{Taux mensuel entree AT}
//' \item{Effectif_ITTIPT}{Effectif cumule AT}
//' \item{Res_VAN_Sin_ITTIPT}{VAN Cumule sinistre AT}
//' @export
//' 
//' @examples
// [[Rcpp::export]]
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
{
  int mp_size = ID_MP.size();
  
  NumericMatrix EtatPret_EstDiffereEnCours(mp_size, NombrePeriodes);
  NumericMatrix EtatPret_EstEnCours(mp_size, NombrePeriodes);
  NumericMatrix Ech_CRDDebPer(mp_size, NombrePeriodes);
  
  NumericMatrix Assu_ProbSurvieCreditDebPer(mp_size, NombrePeriodes);
  NumericMatrix Assu_TxMortMens(mp_size, NombrePeriodes);
  NumericMatrix Assu_TxRAMens(mp_size, NombrePeriodes);
  
  NumericMatrix Res_VAN_AssietteCI(mp_size, NombrePeriodes);
  NumericMatrix Res_VAN_AssietteCRD(mp_size, NombrePeriodes);
  
  NumericMatrix DcPtia_VAN_Sin(mp_size, NombrePeriodes);
  NumericMatrix Effectif_DcPtia(mp_size, NombrePeriodes);
  NumericMatrix DcPtia_PrestProableDcPtia(mp_size, NombrePeriodes);
  NumericMatrix Res_VAN_Sin_DCPTIA(mp_size, NombrePeriodes);
  
  NumericMatrix ITTIPT_VAN_Sin(mp_size, NombrePeriodes);
  NumericMatrix ITTIPT_TxMensEntree3Mois(mp_size, NombrePeriodes);
  NumericMatrix Effectif_ITTIPT(mp_size, NombrePeriodes);
  NumericMatrix Res_VAN_Sin_ITTIPT(mp_size, NombrePeriodes);
  
  EtatProjection EmptyEtat;
  EtatProjection etat;
  
  for(int j = 0; j < mp_size; j++)
  {
    etat = EmptyEtat;
    etat.Id_MP = ID_MP[j];
    etat.Periode = 0.0;
    double dureeproj = std::min(NombrePeriodes, DUREE_AMORT_MOIS[j]+DUREE_DIFF_MOIS[j] );
    
    for(int i = 0; i < dureeproj; i++)
    {
      CalculProjectionMP(
         &etat,
         ID_MP[j], 
         DUREE_AMORT_MOIS[j], 
         DUREE_DIFF_MOIS[j],
         DEBUT_PRET_MOIS[j],
         CI_ASSURE[j], 
         DIFFERE_TYPE[j],   
         TXNOM_TYPE_MENS[j], 
         TXNOM_ANN[j], 
         AGE_SOUS_ANN[j], 
         AGE_FIN_DC_ANN[j],
         AGE_FIN_AT_ANN[j], 
         PART_H[j], 
         PART_IMMO[j],
         PART_PERSO[j],
         TXACTUMENS[j],
         PRIX_PTIA_POURCDCSEUL[j],
         ABT_AT_PERTEREV[j],
         NombrePeriodes);
      
      EtatPret_EstDiffereEnCours[i*mp_size + j] = etat.EtatPret_EstDiffereEnCours;
      EtatPret_EstEnCours[i*mp_size + j] = etat.EtatPret_EstEnCours;
      Ech_CRDDebPer[i*mp_size + j] = etat.Ech_CRDDebPer;
      
      Assu_ProbSurvieCreditDebPer[i*mp_size + j] = etat.Assu_ProbSurvieCreditDebPer;
      Assu_TxMortMens[i*mp_size + j] = etat.Assu_TxMortMens;
      Assu_TxRAMens[i*mp_size + j] = etat.Assu_TxRAMens;
      
      Res_VAN_AssietteCI[i*mp_size + j] = etat.Res_VAN_AssietteCI;
      Res_VAN_AssietteCRD[i*mp_size + j] = etat.Res_VAN_AssietteCRD;
      
      DcPtia_VAN_Sin[i*mp_size + j] = etat.DcPtia_VAN_Sin;
      Effectif_DcPtia[i*mp_size + j] = etat.Effectif_DcPtia;
      DcPtia_PrestProableDcPtia[i*mp_size + j]=etat.DcPtia_PrestProableDcPtia;
      Res_VAN_Sin_DCPTIA[i*mp_size + j] = etat.Res_VAN_Sin_DCPTIA;
      
      ITTIPT_VAN_Sin[i*mp_size + j] = etat.ITTIPT_VAN_Sin;
      Effectif_ITTIPT[i*mp_size + j] = etat.Effectif_ITTIPT;
      ITTIPT_TxMensEntree3Mois[i*mp_size + j] = etat.ITTIPT_TxMensEntree3Mois;
      Res_VAN_Sin_ITTIPT[i*mp_size + j] = etat.Res_VAN_Sin_ITTIPT;
      
      
    }
  }
  List result;
  
  
  result["EtatPret_EstDiffereEnCours"]= EtatPret_EstDiffereEnCours;
  result["EtatPret_EstEnCours"]= EtatPret_EstEnCours;
  result["Ech_CRDDebPer"]= Ech_CRDDebPer;
  
  result["Assu_ProbSurvieCreditDebPer"]= Assu_ProbSurvieCreditDebPer;
  result["Assu_TxMortMens"]= Assu_TxMortMens;
  result["Assu_TxRAMens"]= Assu_TxRAMens;
  
  result["Res_VAN_AssietteCI"]= Res_VAN_AssietteCI;
  result["Res_VAN_AssietteCRD"]= Res_VAN_AssietteCRD;
  
  result["DcPtia_VAN_Sin"]= DcPtia_VAN_Sin;
  result["Effectif_DcPtia"]= Effectif_DcPtia;
  result["DcPtia_PrestProableDcPtia"]= DcPtia_PrestProableDcPtia;
  result["Res_VAN_Sin_DCPTIA"]= Res_VAN_Sin_DCPTIA;
  
  result["ITTIPT_VAN_Sin"]= ITTIPT_VAN_Sin;
  result["Effectif_ITTIPT"]= Effectif_ITTIPT;
  result["ITTIPT_TxMensEntree3Mois"]= ITTIPT_TxMensEntree3Mois;
  result["Res_VAN_Sin_ITTIPT"]= Res_VAN_Sin_ITTIPT;
  
  return result;
}



//' Title
//' Projette les modeles points
//' @param ID_MP
//' Identifiant unique de chaque modele point 
//' @param ID_MP_AGG
//' Identifiant unique de chaque groupe de modele point
//' @param DUREE_AMORT_MOIS 
//' Duree amortissement du pret ( en mois )
//' @param DUREE_DIFF_MOIS
//' Duree differe du pret ( en mois ) 
//' @param DEBUT_PRET_MOIS
//' Debut du pret à partir de la date de projection  ( en mois )
//' @param CI_ASSURE 
//' Capital emprunte assure ( quotite comprise )
//' @param DIFFERE_TYPE 
//' Type de differe ( 1 == Partiel , 2 == Total )
//' @param TXNOM_TYPE_MENS 
//' Type de mensualisation du taux nominal ( 1 == Proportionnel , 2 == Equivalent )
//' @param TXNOM_ANN 
//' Taux nominal du pret
//' @param AGE_SOUS_ANN 
//' Age a la souscription ( en annees )
//' @param AGE_FIN_DC_ANN 
//' Age fin de la garantie deces ( en annees )
//' @param AGE_FIN_AT_ANN 
//' Age fin  arret de travail ( en annees )
//' @param PART_H 
//' Proportion des hommes
//' @param PART_IMMO 
//' Proportion des prets immos
//' @param PART_PERSO 
//' Proportion des prets persos
//' @param TXACTUMENS 
//' Taux actualisation mensuel
//' @param PRIX_PTIA_POURCDCSEUL 
//' Prix de la PTIA
//' @param ABT_AT_PERTEREV
//' Taux abattement pour la perte de revenu 
//' @param Periodes_AGG 
//' Nombre de mois de projection
//' @return
//' Une liste de matrices (Nombre de MP * Nombre de Periodes)
//' \item{Ech_CRDDebPer}{CRD de debut de periode}
//' \item{Assu_ProbSurvieCreditDebPer}{Probabilite de survie en debut de periode}
//' \item{Res_VAN_AssietteCI}{VAN assiette  CI}
//' \item{Res_VAN_AssietteCRD}{VAN assiette CRD}
//' \item{Res_VAN_Sin_DCPTIA}{VAN Cumule sinistre DC}
//' \item{Res_VAN_Sin_ITTIPT}{VAN Cumule sinistre AT}
//' @export
//' 
//' @examples
// [[Rcpp::export]]
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
{
  int mp_size = ID_MP.size();
  double maxagg = max(ID_MP_AGG);
  
  double maxperagg = max(Periodes_AGG);
  double NombrePeriodes = Periodes_AGG.size();
  
  
  NumericMatrix Ech_CRDDebPer(maxagg, NombrePeriodes);
  NumericMatrix Assu_ProbSurvieCreditDebPer(maxagg, NombrePeriodes);
  NumericMatrix Res_VAN_AssietteCI(maxagg, NombrePeriodes);
  NumericMatrix Res_VAN_AssietteCRD(maxagg, NombrePeriodes);
  NumericMatrix Res_VAN_Sin_DCPTIA(maxagg, NombrePeriodes);
  NumericMatrix Res_VAN_Sin_ITTIPT(maxagg, NombrePeriodes);
  
  EtatProjection EmptyEtat;
  EtatProjection etat;
  
  for(int j = 0; j < mp_size; j++)
  {
    etat = EmptyEtat;
    etat.Id_MP = ID_MP[j];
    etat.Periode = 0.0;
    
    double prev=0;
    
    for(int k = 0; k < NombrePeriodes; k++)
    {
      double cur = Periodes_AGG[k];
      
      double dureeproj = std::min(cur, DUREE_AMORT_MOIS[j]+DUREE_DIFF_MOIS[j] );
      
      for(int i = prev; i < dureeproj; i++)
      {
        
        CalculProjectionMP(
          &etat,
          ID_MP[j],
          DUREE_AMORT_MOIS[j], 
          DUREE_DIFF_MOIS[j],
          DEBUT_PRET_MOIS[j],
          CI_ASSURE[j], 
          DIFFERE_TYPE[j],   
          TXNOM_TYPE_MENS[j], 
          TXNOM_ANN[j], 
          AGE_SOUS_ANN[j],
          AGE_FIN_DC_ANN[j],
          AGE_FIN_AT_ANN[j], 
          PART_H[j], 
          PART_IMMO[j],
          PART_PERSO[j],
          TXACTUMENS[j],
          PRIX_PTIA_POURCDCSEUL[j],
          ABT_AT_PERTEREV[j],
          NombrePeriodes);
        
        Ech_CRDDebPer[k*maxagg + (ID_MP_AGG[j]-1)] += etat.Ech_CRDDebPer;
        Assu_ProbSurvieCreditDebPer[k*maxagg + (ID_MP_AGG[j]-1)] += etat.Assu_ProbSurvieCreditDebPer;
        Res_VAN_AssietteCI[k*maxagg + (ID_MP_AGG[j]-1)] += etat.Primes_VAN_AssietteCI;
        Res_VAN_AssietteCRD[k*maxagg + (ID_MP_AGG[j]-1)] += etat.Primes_VAN_AssietteCRD;
        Res_VAN_Sin_DCPTIA[k*maxagg + (ID_MP_AGG[j]-1)]  += etat.DcPtia_VAN_Sin;
        Res_VAN_Sin_ITTIPT[k*maxagg + (ID_MP_AGG[j]-1)]  += etat.ITTIPT_VAN_Sin;
        
      }
        
      prev = cur;
    }
    
  }
  
  for(int j = 0; j < maxagg; j++)
  {
    for(int i = 1; i < NombrePeriodes; i++)
    { 
      int cur = i*maxagg + (j-1);
      int prev = (i-1)*maxagg + (j-1);
      Res_VAN_AssietteCI[cur] += Res_VAN_AssietteCI[prev];
      Res_VAN_AssietteCRD[cur] += Res_VAN_AssietteCRD[prev];
      Res_VAN_Sin_DCPTIA[cur]  += Res_VAN_Sin_DCPTIA[prev];
      Res_VAN_Sin_ITTIPT[cur]  += Res_VAN_Sin_ITTIPT[prev];
      
    }
  }
  
  List result;
  
  result["Ech_CRDDebPer"]= Ech_CRDDebPer;
  result["Assu_ProbSurvieCreditDebPer"]= Assu_ProbSurvieCreditDebPer;
  result["Res_VAN_AssietteCI"]= Res_VAN_AssietteCI;
  result["Res_VAN_AssietteCRD"]= Res_VAN_AssietteCRD;
  result["Res_VAN_Sin_DCPTIA"]= Res_VAN_Sin_DCPTIA;
  result["Res_VAN_Sin_ITTIPT"]= Res_VAN_Sin_ITTIPT;
  return result;
}




#endif