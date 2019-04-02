#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED





//Pointeur sur élément de la TS
typedef struct symbole* listsymbole;

//définition de la structure élement de la table des symboles
struct symbole
{
char NomEntite[20];
char CodeEntite[20];
char TypeEntite[20];
int TailleEntite;
listsymbole suiv;
};



//Taille de la TS
#define TailleTable 1229

//Declaration de la TS comme étant un tableau de pointeurs
listsymbole table[TailleTable];


//Fonction de hashage qui retourne la position d'insertion 
//d'une entité lexicale en utilisant son nom comme clé
int hashCode(char *cle)
{
	int h = 0;
	h = cle[0]%TailleTable;
	return h;
}

//Initialisation de la table
//Tous les pointeurs sont mis à NULL
void init()
{
	int i;
	for (i = 0; i < TailleTable; ++i)
	{
		table[i] = NULL;
	}
}

/*
Recherche une entite dans une liste chainée de symboles: 
renvoie NULL si elle n'est pas dans la liste et renvoie son @ si elle y est
*/
listsymbole rechercheListe(char* entite, listsymbole list)
{
	//Commencer par la tête de liste
	listsymbole p = list;
	while(p!=NULL)
	{
		if(strcmp(p->NomEntite,entite)==0)
			return p;//Adresse de l'entite dans la liste chainée
		p = p->suiv;
	}
	return NULL;
}

/*
Recherche une entité lexicale dans toute la TS 
Reçoi en entrée le nom de l'entité
La fonction rechercheTable fait appel à la fonction rechercheListe si l'élément d'index revoyé par
la fonction hashCode() n'est pas un NULL
*/
listsymbole rechercheTable(char *cle) {
   
   //On cherche d'abord l'index retourné par la fonction de hashage
   int hashIndex = hashCode(cle);  
   
   //Si le pointeur de cet index n'est pas NULL, on fait une recherche dans la liste chainée
   if(table[hashIndex] != NULL)
   {
   	return rechercheListe(cle, table[hashIndex]);
   }     
   else
   {
    return NULL;
   }        
}


//Fonction pour créer un nouvel élément
listsymbole nouvelElt()
{
    listsymbole p=NULL;
    p=(listsymbole)malloc(sizeof(struct symbole));
    return p;
}


//insersion d'une nouvelle entité dans la table des symboles
void inserer(char* entite, char* code)
{
	
	//On s'assure que l'entité n'existe pas déja dans la TS
	if(rechercheTable(entite)==NULL && strlen(entite)<=8)
	{
		//On récupère le résultat de la fonction de hashage 
		int hashIndex = hashCode(entite); 
		listsymbole position = table[hashIndex];
		//Si le pointeur position est NULL on insère le 1er élément
		if(position==NULL)
		{
			position = nouvelElt();
			strcpy(position->NomEntite, entite);

			strcpy(position->CodeEntite, code);
			strcpy(position->TypeEntite,"");
			position->TailleEntite = 1;
			position->suiv = NULL;

			table[hashIndex] = position;
		}
		else
		// Sinon, on chaine l'élément au début
		{
			listsymbole nouv;
			nouv = nouvelElt();

			strcpy(nouv->NomEntite, entite);
			strcpy(nouv->CodeEntite, code);
			strcpy(nouv->TypeEntite,"");
			nouv->TailleEntite = 1;
			nouv->suiv = table[hashIndex]->suiv;
			table[hashIndex]->suiv = nouv;
		}
		
	}

}

//fonction pour insérer le type d'un IDF 
void insererType(char* entite, char* type)
{
	listsymbole adrEntite = rechercheTable(entite);

	strcpy(adrEntite->TypeEntite, type);
}

//fonction pour inserer la taille d'une entité (dans le cas d'un tableau)
void insererTaille(char* entite, int taille)
{
	listsymbole adrEntite = rechercheTable(entite);

	adrEntite->TailleEntite = taille;
}

//fonction qui détecte une double déclaration d'une entité: renvoie 0 si pas de double déclaration et 1 sinon
int doubleDeclaration(char* entite)
{
	listsymbole p = rechercheTable(entite);

	if(p==NULL) return 0;//pas de double déclaration
	else return 1;
}

//une fonction pour afficher la table des symbolees
void afficher ()
{
	int i;
	int j=0;
	printf("\n/********************** Table des symbolees ************************/\n");
	printf("__________________________________________________________________\n");
	printf("\t| NomEntite |  CodeEntite  |  TypeEntite   |  TailleEntite   \n");
	printf("__________________________________________________________________\n");
	
	
	for (i = 0; i < TailleTable; ++i)
	{
		listsymbole courant = table[i];
		while(courant!=NULL)
		{
			printf("\t|%10s |%12s  |%12s   |%10d   |\n",courant->NomEntite,courant->CodeEntite,courant->TypeEntite,courant->TailleEntite);
			courant = courant->suiv;
		}
	}

	
}


#endif // FONCTIONS_H_INCLUDED
