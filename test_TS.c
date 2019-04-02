#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "table_Symbole.hs"



int main()
{
	init();

	inserer("p", "var simple");
	insererType("p","int");
	insererTaille("p", 1);

	inserer("w", "var simple");
	insererType("w","char");
	insererTaille("w", 1);

	inserer("waka", "tableau");
	insererType("waka","int");
	insererTaille("waka", 5);

	inserer("piwi", "Constante");
	insererType("piwi","float");
	insererTaille("piwi", 1);
	
	//w existe déja dans la TS --->1
	printf("%d\n",doubleDeclaration("w"));

	//x n'existe pas dans la TS --->0
	printf("%d\n",doubleDeclaration("x"));

	afficher();
	system("PAUSE");

}
