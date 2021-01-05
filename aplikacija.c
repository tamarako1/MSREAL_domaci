#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{	
	FILE* fp;
	int br[4];
	int  rez[3];
	char znak[3];

//	while(1){ 
		printf("\nUnesite izraz: ");	
		scanf("%d%c%d%c%d%c%d",&br[0], &znak[0], &br[1], &znak[1], &br[2], &znak[2], &br[3]);
		printf("\nBroj br[0]je %d", br[0]);
		printf("\nznak[0]je %c", znak[0]);
		printf("\nBroj br[1]je %d", br[1]);
		printf("\nznak[1]je %c", znak[1]);
		printf("\nBroj br[2]je %d", br[2]);
		printf("\nznak[2]je %c", znak[2]);
		printf("\nBroj br[3]je %d", br[3]);

/*		if(argc==7){
		printf("Uspesno set uneli 7 argumenata");
	}
	else
	{
		printf("Pogresan broj argumenata\n");
		return -1;
	}*/
		// Upisi vrednost operacije
/*	fp = fopen("/dev/alu", "w");
	if(fp == NULL)
	{
		printf("Problem pri otvaranju /dev/alu\n");
		return -1;
	}*/

if(znak[0]=='*'){  					//br[0]*br[1]=rez[0]
	fp = fopen("/dev/alu", "w");                              //otvori
	if(fp == NULL)
	{
		printf("Problem pri otvaranju /dev/alu\n");
		return -1;
	}
	fprintf(fp, "regA=%d", br[0]); 				//upise	
	fprintf(fp, "regB=%d", br[1]);
	fputs(fp, "regA * regB");  //  ECHO
	if(fclose(fp)){						//zatvori
	printf("Problem pri zatvaranju /dev/led");
	return -1;
	}
	fp=fopen("/dev/alu","r");				//otvori
	fscanf(fp,"%d", &rez[0]); //cat				procita
	if(fclose(fp)){						//zatvori
	printf("Problem pri zatvaranju /dev/led");
	return -1;
	}
	printf("Rez[0]=%d", rez[0]);
}/*
	if(znak[1]=='*'){   			//br[0]*br[1]*br[2]
		fp = fopen("/dev/alu", "w");
	//rez[1]=rez[0]*br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", br[2]);
		fputs(fp, "regA * regB");  //dvostruki navodnici  ECHO
		fscanf(fp,"%d", &rez[1]);
	
		if(znak[2]=='*'){   				//br[0]*br[1]*br[2]*br[3]
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}	
		else if(znak[2]=='/'){				//br[0]*br[1]*br[2]/br[3]
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}	
		else if(znak[2]=='+'){				//br[0]*br[1]*br[2]+br[3]
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}
		else if(znak[2]=='-'){				//br[0]*br[1]*br[2]-br[3]
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]-br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}			
	}
	
	else if(znak[1]=='/'){				
		fp = fopen("/dev/alu", "w");
	//rez[1]=rez[0]/br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", br[2]);
		fputs(fp, "regA / regB");  //ECHO
		fscanf(fp,"%d", &rez[1]);	//cat
	
		if(znak[2]=='*'){   				
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}
		else if(znak[2]=='/'){
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}
		else if(znak[2]=='+'){				
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}
		else if(znak[2]=='-'){				
	//rez[2]=rez[1]-br[3];		
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);
		}
	}
	else if(znak[1]=='+'){   //rez[0]=br[0]*br[1]
			if(znak[2]=='*'){   //br[0]*br[1]+br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		
		else if(znak[2]=='/'){   //br[0]*br[1]+br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}		
				
		else if(znak[2]=='+'){			//br[0]*br[1]+br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}	
		else if(znak[2]=='-'){				//br[0]/br[1]+br[2]-br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		fp = fopen("/dev/alu", "w");
		//rez[2]=rez[0]-rez[1]
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", rez[1]);
		fputs(fp, "regA + regB");  //  ECHO
		fscanf(fp, "%d", &rez[2]);
	}
	
	else if(znak[1]=='-'){ //rez[0]=br[0]*br[1]
		if(znak[2]=='*'){   //br[0]*br[1]-br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		else if(znak[2]=='/'){   //br[0]*br[1]-br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}		
				
		else if(znak[2]=='+'){			//br[0]*br[1]-br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}	
		else if(znak[2]=='-'){				//br[0]*br[1]-br[2]-br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		//rez[2]=rez[0]-rez[1]
		fp = fopen("/dev/alu", "w");
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", rez[1]);
		fputs(fp, "regA - regB");  //  ECHO
		fscanf(fp, "%d", &rez[2]);
	}
	
	
	printf("Konacni rezultat je %d", rez[2]);
}
	
/*
else if(znak[0]=='/'){   //br[0]/br[1]

fprintf(fp, "regA=%d", br[0]);
fprintf(fp, "regB=%d", br[1]);
	//rez[0]=br[0]/br[1];
	fputs(fp, "regA / regB");  //  ECHO
	fscanf(fp,"%d", &rez[0]);
	
	if(znak[1]=='*'){   			//br[0]/br[1]*br[2]
		//rez[1]=rez[0]*br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", br[2]);
		fputs(fp, "regA * regB");  //dvostruki navodnici  ECHO
		fscanf(fp,"%d", &rez[1]);

		
		if(znak[2]=='*'){   				//br[0]/br[1]*br[2]*br[3]
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
		else if(znak[2]=='/'){				//br[0]/br[1]*br[2]/br[3]
			//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
		else if(znak[2]=='+'){				//br[0]/br[1]*br[2]+br[3]
			//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
		else if(znak[2]=='-'){				//br[0]/br[1]*br[2]-br[3]
			//rez[2]=rez[1]-br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp,"%d",&rez[2]);//CAT
		}			
	}
	
	else if(znak[1]=='/'){				//br[0]/br[1]/br[2]
		//rez[1]=rez[0]/br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", br[2]);
		fputs(fp, "regA / regB");  //dvostruki navodnici  ECHO
		fscanf(fp,"%d", &rez[1]);//CAT
	
		if(znak[2]=='*'){   				//br[0]/br[1]/br[2]*br[3]
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
		else if(znak[2]=='/'){				//br[0]/br[1]/br[2]/br[3]
			//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
		else if(znak[2]=='+'){				//br[0]/br[1]/br[2]+br[3]
			//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
		else if(znak[2]=='-'){				//br[0]/br[1]/br[2]-br[3]
			//rez[2]=rez[1]-br[3];		
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp,"%d", &rez[2]);//CAT
		}
	}
	
	else if(znak[1]=='+'){   //rez[0]=br[0]/br[1]
		if(znak[2]=='*'){   //br[0]/br[1]+br[2]*br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		
		else if(znak[2]=='/'){   //br[0]/br[1]+br[2]/br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}		
				
		else if(znak[2]=='+'){			//br[0]/br[1]+br[2]+br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}	
		else if(znak[2]=='-'){				//br[0]/br[1]+br[2]-br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		//rez[2]=rez[0]-rez[1]
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", rez[1]);
		fputs(fp, "regA + regB");  //  ECHO
		fscanf(fp, "%d", &rez[2]);
	}
	
	else if(znak[1]=='-'){ //rez[0]=br[0]/br[1]
		if(znak[2]=='*'){   //br[0]/br[1]-br[2]*br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		else if(znak[2]=='/'){   //br[0]/br[1]-br[2]/br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}		
				
		else if(znak[2]=='+'){			//br[0]/br[1]-br[2]+br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}	
		else if(znak[2]=='-'){				//br[0]/br[1]-br[2]-br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]);
		}
		//rez[2]=rez[0]-rez[1]
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", rez[1]);
		fputs(fp, "regA - regB");  //  ECHO
		fscanf(fp, "%d", &rez[2]);
	}
	
	printf("Konacni rezultat je %d", rez[2]);
}


else if(znak[0]=='+'){ 			//br[0]+br[1]
	if(znak[1]=='*'){   			//znak1 *	
	fprintf(fp, "regA=%d", br[1]);
	fprintf(fp, "regB=%d", br[2]); //br[0]+ (br[1]*br[2])
		//rez[0]=br[1]*br[2];
		fputs(fp, "regA * regB");  //dvostruki navodnici  ECHO
		fscanf(fp,"%d", &rez[0]);
		
		if(znak[2]=='*'){   				//br[0]+br[1]*br[2]*br[3]
			//rez[1]=rez[0]*br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		}	
		else if(znak[2]=='/'){				//br[0]+br[1]*br[2]/br[3]
			//rez[1]=rez[0]/br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		}	
		else if(znak[2]=='+'){				//br[0]+br[1]*br[2]+br[3]
			//rez[1]=rez[0]+br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]*br[2]-br[3]
			//rez[1]=rez[0]-br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		} 			
	}
	
	else if(znak[1]=='/'){				//znak1 /
	fprintf(fp, "regA=%d", br[1]);
	fprintf(fp, "regB=%d", br[2]); //br[0]+ (br[1]/br[2])
		//rez[0]=br[1]/br[2];
		fputs(fp, "regA / regB");  //dvostruki navodnici  ECHO
		fscanf(fp,"%d", &rez[0]);
		
		if(znak[2]=='*'){   				//br[0]+br[1]/br[2]*br[3]
			//rez[1]=rez[0]*br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		}	
		else if(znak[2]=='/'){				//br[0]+br[1]/br[2]/br[3]
			//rez[1]=rez[0]/br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		}	
		else if(znak[2]=='+'){				//br[0]+br[1]/br[2]+br[3]
			//rez[1]=rez[0]+br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]); 
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]/br[2]-br[3]
			//rez[1]=rez[0]-br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
		}			
	}
	
	else if(znak[1]=='+'){
		if(znak[2]=='*'){   //br[0]+br[1]+br[2]*br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		
		else if(znak[2]=='/'){   //br[0]+br[1]+br[2]/br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}		
				
		else if(znak[2]=='+'){			//br[0]+br[1]+br[2]+br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]+br[2]-br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		//rez[1]=br[1]+rez[0];
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fputs(fp, "regA + regB");  //  ECHO
		fscanf(fp, "%d", &rez[1]);
	}
	
	
	else if(znak[1]=='-'){
		
		if(znak[2]=='*'){   //br[0]+br[1]-br[2]*br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		else if(znak[2]=='/'){   //br[0]+br[1]-br[2]/br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}		
				
		else if(znak[2]=='+'){			//br[0]+br[1]-br[2]+br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]-br[2]-br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		
		//rez[1]=br[1]-rez[0];
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fputs(fp, "regA - regB");  //  ECHO
		fscanf(fp, "%d", &rez[1]);
	}
	//rez[2]=br[0]+rez[1];
	fprintf(fp, "regA=%d", br[0]);
	fprintf(fp, "regB=%d", rez[1]);
	fputs(fp, "regA + regB");  //  ECHO
	fscanf(fp, "%d", &rez[2]);
		
	printf("Konacni rezultat je %d", rez[2]);
}

else if(znak[0]=='-'){  			//br[0]-br[1]		
	if(znak[1]=='*'){   			//znak1 * br[0]-br[1]*br[2]	
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", br[2]); // br[0]- (br[1]*br[2])
		//rez[0]=br[1]*br[2];
		fputs(fp, "regA * regB");  // ECHO
		fscanf(fp, "%d", &rez[0]); //CAT
		
		if(znak[2]=='*'){   				//znak2 *
			//rez[1]=rez[0]*br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}	
		else if(znak[2]=='/'){				//znak2 /
			//rez[1]=rez[0]/br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}
		else if(znak[2]=='+'){				//znak2 +
			//rez[1]=rez[0]+br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", r&ez[1]); //CAT
		}	
		else if(znak[2]=='-'){				//znak2 -
			//rez[1]=rez[0]-br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}
	}
	
	else if(znak[1]=='/'){				
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", br[2]); // br[0]- (br[1]/br[2])
		//rez[0]=br[1]/br[2];
		fputs(fp, "regA / regB");  //dvostruki navodnici  ECHO
		fscanf(fp, "%d", &rez[0]); //CAT
		
		if(znak[2]=='*'){   				
			//rez[1]=rez[0]*br[3];  //br[0]- ((br[1]/br[2]) * br[3])
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}	
		else if(znak[2]=='/'){				
			//rez[1]=rez[0]/br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}
		else if(znak[2]=='+'){				
			//rez[1]=rez[0]+br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}
		else if(znak[2]=='-'){		
			//rez[1]=rez[0]-br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[1]); //CAT
		}
	}
	else if(znak[1]=='+'){
		if(znak[2]=='*'){   //br[0]-br[1]+br[2]*br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		
		else if(znak[2]=='/'){   //br[0]-br[1]+br[2]/br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}		
				
		else if(znak[2]=='+'){			//br[0]-br[1]+br[2]+br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}	
		else if(znak[2]=='-'){				//br[0]-br[1]+br[2]-br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		//rez[1]=br[1]+rez[0];
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fputs(fp, "regA + regB");  //  ECHO
		fscanf(fp, "%d", &rez[1]);
	}
	
	
	else if(znak[1]=='-'){  //br[0]-br[1]-br[2]
		
		if(znak[2]=='*'){   //br[0]-br[1]-br[2]*br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA * regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		else if(znak[2]=='/'){   //br[0]-br[1]-br[2]/br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA / regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}		
				
		else if(znak[2]=='+'){			//br[0]-br[1]-br[2]+br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA + regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}	
		else if(znak[2]=='-'){				//br[0]-br[1]-br[2]-br[3]
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fputs(fp, "regA - regB");  //  ECHO
			fscanf(fp, "%d", &rez[0]);
		}
		
		//rez[1]=br[1]-rez[0];
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fputs(fp, "regA - regB");  //  ECHO
		fscanf(fp, "%d", &rez[1]);
	}
	
	
	//rez[2]=br[0]-rez[1];
	fprintf(fp, "regA=%d", br[0]);
	fprintf(fp, "regB=%d", rez[1]);
	fputs(fp, "regA - regB");  //  ECHO
	fscanf(fp, "%d",&rez[1]);
	
	printf("Konacni rezultat je %d", rez[2]);
} else printf("Doslo je do greske prilikom koriscenja /dev/alu");
*/
/*		if(fclose(fp))
		{
			printf("Problem pri zatvaranju /dev/alu\n");
			return -1;
		}*/
//usleep(percentage*period);

		// Ugasi diode
	//	fp = fopen("/dev/alu", "w");
	//	if(fp == NULL)
	//	{
	//		printf("Problem pri otvaranju /dev/alu\n");
	//		return -1;
	//	}
	//	fputs("0x00\n", fp);
	//	if(fclose(fp))
	//	{
	//	printf("Problem pri zatvaranju /dev/alu\n");
	//	return -1;
	//	}
	//	usleep((1-percentage)*period);
//	}
	return 0;
}

