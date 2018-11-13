#include <Rcpp.h>
using namespace Rcpp;

#ifndef ETATPROJECTION_CPP
#define ETATPROJECTION_CPP

#include "EtatProjection.h"

EtatProjection CreerEtatProjection(double ID_MP)
{
  EtatProjection result;
  result.Id_MP = ID_MP;
  result.Periode = 0.0;
  return result;
}

/* type de pret, sexe , age */
double Contante_Table_Morta(double,double,double)
{
  return 0.001;
}

/* type de pret, sexe , age */
/*"Immo_H"  "Perso_H" "Pro_H"   "Immo_F"  "Perso_F" "Pro_F"  */
/*ages 18 : 67*/
double Table_Morta_Standard(double typepret, double sexe, double age)
{
  double TbleMort_Age =  age <= 18 ? 18 : age >=90 ? 90 : age;
  
  return MatrixTableMortalite(TbleMort_Age-18, (sexe-1)*3 +(typepret-1));
}

double Contante_Table_EntreeAT(double,double,double)
{
  return 0.01;
}

/* type de pret, sexe , age */
/*colonnes : "Immo_H"  "Perso_H" "Pro_H"   "Immo_F"  "Perso_F" "Pro_F"  */
/*ages 18 : 67 */
double Table_EntreeAT_Standard(double typepret, double sexe, double age)
{
  double TbleEntAT_Age =  age <= 18 ? 18 : age >=65 ? 65 : age;
  
  return MatrixTableEntreeAT(TbleEntAT_Age-18, (sexe-1)*3 +(typepret-1));
}

/*age , duree maintien */
double Contante_Table_MaintienAT(double,double)
{
  return 0.01;
}

/*age , duree maintien */
/*Mois 3 : 599 */
/*ages 20 : 67*/
double Table_MaintienAT_Standard(double age,double dureemaintien)
{
  double TbleMaintAT_Age =  age <= 20 ? 20 : age >=65 ? 65 : age;
  
  return MatrixTableMaintienAT(TbleMaintAT_Age-20, dureemaintien - 3);
}
/*age , duree maintien */
/*Mois 3 : 599 */
/*ages 20 : 67*/
double Table_MaintienConstitAT_Standard(double age,double dureemaintien)
{
  double TbleMaintAT_Age =  age <= 20 ? 20 : age >=65 ? 65 : age;
  
  return MatrixTableMaintienConstitAT(TbleMaintAT_Age-20, dureemaintien - 3);
}

/* type pret, duree restante*/
double Contante_Table_Rachat(double,double)
{
  return 0.06;
}


//' Enregistre les differentes tables pour utilisation future par les autres fonctions
//' @param TableMortalite
//' Matrice des taux de mortalites . Cette matrice doit avoir 6 colonnes :
//' Immo_H Perso_H Pro_H Immo_F Perso_F Pro_F .Les ages vont de 18 a 90 ans.
//' @param TableEntreeAT 
//' Matrice des taux d entree en arret de travail . Cette matrice doit avoir 6 colonnes :
//' Immo_H Perso_H Pro_H Immo_F Perso_F Pro_F .Les ages vont de 18 a 67 ans.
//' @param TableMaintienAT 
//' Matrice des taux de maintien en arret de travail.
//' Il faut une franchise de 3mois sur la table
//' @param TableMaintienConstitAT 
//' Matrice des capitaux constitutifs en arret de travail.
//' Il faut une franchise de 3mois sur la table
// [[Rcpp::export]]
List Setup(NumericMatrix TableMortalite,
           NumericMatrix TableEntreeAT, 
           NumericMatrix TableMaintienAT, 
           NumericMatrix TableMaintienConstitAT )
{
  MatrixTableMortalite = clone(TableMortalite);
  MatrixTableEntreeAT = clone(TableEntreeAT);
  MatrixTableMaintienAT = clone(TableMaintienAT);
  MatrixTableMaintienConstitAT = clone(TableMaintienConstitAT);
  
  List result;
  result["TableMortalite"]=MatrixTableMortalite;
  result["TableEntreeAT"]=MatrixTableEntreeAT;
  result["TableMaintienAT"]=MatrixTableMaintienAT;
  result["TableMaintienConstitAT"]=MatrixTableMaintienConstitAT;
  
  return result;
}

// [[Rcpp::export]]
List RetrieveMatrices()
{
  
  List result;
  result["TableMortalite"]=MatrixTableMortalite;
  result["TableEntreeAT"]=MatrixTableEntreeAT;
  result["TableMaintienAT"]=MatrixTableMaintienAT;
  result["TableMaintienConstitAT"]=MatrixTableMaintienConstitAT;
  
  return result;
}


#endif