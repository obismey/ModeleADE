#include <Rcpp.h>
using namespace Rcpp;

#ifndef ETATPROJECTION_H
#define ETATPROJECTION_H

/*colonnes : "Qx_Immo_H"  "Qx_Perso_H" "Qx_Pro_H"   "Qx_Immo_F"  "Qx_Perso_F" "Qx_Pro_F"  */
/*ages 18 : 90 */
static NumericMatrix MatrixTableMortalite;

/*"Immo_H"  "Perso_H" "Pro_H"   "Immo_F"  "Perso_F" "Pro_F"  */
/*ages 18 : 67*/
static NumericMatrix MatrixTableEntreeAT;

/*Mois 3 : 599 */
/*ages 20 : 67*/
static NumericMatrix MatrixTableMaintienAT ;
static NumericMatrix MatrixTableMaintienConstitAT;

struct EtatProjection
{
  double Periode;
  double Id_MP;
  double EtatPret_EstEnCours;
  double EtatPret_EstDiffereEnCours;
  double Ech_TxNomMens;
  double Ech_MensPer_Diff;
  double Ech_MensPer_amort;
  double Ech_CRDDebPer;
  double Ech_InteretsPer;
  double Ech_MensPer;
  double Ech_AMortPer;
  double Ech_DureeRestPretDebPer;
  double Assu_AgeAnnee;
  double Assu_EstAssureDC;
  double Assu_EstAssureAT;
  double Assu_EstPaiementAssurance;
  double Assu_ProbSurvieCreditDebPer;
  double Assu_TxMortMens;
  double Assu_TxRAMens;
  double Primes_TxActuEtSurvie;
  double Effectif_Valide;
  double Primes_VAN_AssietteCI ;
  double Primes_VAN_AssietteCRD ;
  double Res_VAN_AssietteCI;
  double Res_VAN_AssietteCRD;
  double Effectif_DcPtia;
  double DcPtia_PrestProableDcPtia;
  double DcPtia_VAN_Sin;
  double Res_VAN_Sin_DCPTIA;
  double ITTIPT_TxMensEntree3Mois;
  double ITTIPT_VAN_Sin ;
  double Effectif_ITTIPT ;
  double Res_VAN_Sin_ITTIPT;
};

EtatProjection CreerEtatProjection(double ID_MP)
;
/* type de pret, sexe , age */
double Contante_Table_Morta(double,double,double)
;

/* type de pret, sexe , age */
/*"Immo_H"  "Perso_H" "Pro_H"   "Immo_F"  "Perso_F" "Pro_F"  */
/*ages 18 : 67*/
double Table_Morta_Standard(double typepret, double sexe, double age)
;
double Contante_Table_EntreeAT(double,double,double)
;
/* type de pret, sexe , age */
/*colonnes : "Immo_H"  "Perso_H" "Pro_H"   "Immo_F"  "Perso_F" "Pro_F"  */
/*ages 18 : 67 */
double Table_EntreeAT_Standard(double typepret, double sexe, double age)
;

/*age , duree maintien */
double Contante_Table_MaintienAT(double,double)
;

/*age , duree maintien */
/*Mois 3 : 599 */
/*ages 20 : 67*/
double Table_MaintienAT_Standard(double age,double dureemaintien)
;
/*age , duree maintien */
/*Mois 3 : 599 */
/*ages 20 : 67*/
double Table_MaintienConstitAT_Standard(double age,double dureemaintien)
;

/* type pret, duree restante*/
double Contante_Table_Rachat(double,double)
;


List Setup(NumericMatrix TableMortalite,
           NumericMatrix TableEntreeAT, 
           NumericMatrix TableMaintienAT, 
           NumericMatrix TableMaintienConstitAT );

#endif