#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{	
	FILE* fp;
	int br[5];
	int  rez[4];
	char znak[4];
	char exit[5];

	while(1){ 

		printf("\nUnesite izraz: ");	
	//	scanf("%c%c%c%c", &exit[0], &exit[1], &exit[2], exit[3]);

		scanf("%d %c %d %c %d %c %d", &br[0], &znak[0], &br[1], &znak[1], &br[2], &znak[2], &br[3]);

		printf("\nBroj br[0]je %d", br[0]);
		printf("\nznak[0]je %c", znak[0]);
		printf("\nBroj br[1]je %d", br[1]);
		printf("\nznak[1]je %c", znak[1]);
		printf("\nBroj br[2]je %d", br[2]);
		printf("\nznak[2]je %c", znak[2]);
		printf("\nBroj br[3]je %d\n", br[3]);


if(znak[0]=='*'){  					//br[0]*br[1]=rez[0]
	fp = fopen("/dev/alu", "w");                              //otvori
	if(fp == NULL)
	{
		printf("Problem pri otvaranju /dev/alu\n");
		return -1;
	}
	fprintf(fp, "regA=%d", br[0]); 				//upise	
	fclose(fp);
	fp=fopen("/dev/alu", "w");
	fprintf(fp, "regB=%d", br[1]);
	fclose(fp);
	fp=fopen("/dev/alu", "w");
	fprintf(fp,"regA * regB");
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
printf("rez[0]=%d", rez[0]);
	if(znak[1]=='*'){   			//br[0]*br[1]*br[2]
		fp = fopen("/dev/alu", "w");
		//rez[1]=rez[0]*br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%d", br[2]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA * regB"); //echo
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp,"%d", &rez[1]);
		fclose(fp);

		if(znak[2]=='*'){   				//br[0]*br[1]*br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}	
		else if(znak[2]=='/'){				//br[0]*br[1]*br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}	
		else if(znak[2]=='+'){				//br[0]*br[1]*br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA + regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]); //cat
			fclose(fp);
		}
		else if(znak[2]=='-'){				//br[0]*br[1]*br[2]-br[3]
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]-br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}			
	}
	
	else if(znak[1]=='/'){				
		fp = fopen("/dev/alu", "w");
		//rez[1]=rez[0]/br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%d", br[2]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA / regB");
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp,"%d", &rez[1]);	//cat
		fclose(fp);

		if(znak[2]=='*'){   				
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
		else if(znak[2]=='/'){
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
		else if(znak[2]=='+'){				
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA + regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
		else if(znak[2]=='-'){				
		//rez[2]=rez[1]-br[3];		
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", rez[1]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
	}
	else if(znak[1]=='+'){   //rez[0]=br[0]*br[1]
			if(znak[2]=='*'){   //br[0]*br[1]+br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
			}
		
		else if(znak[2]=='/'){   //br[0]*br[1]+br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");	
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]*br[1]+br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");		
			fprintf(fp, "regA + regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]/br[1]+br[2]-br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		fp = fopen("/dev/alu", "w");
		//rez[2]=rez[0]-rez[1]
		fprintf(fp, "regA=%d", rez[0]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%d", rez[1]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA + regB");
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[2]);
		fclose(fp);
	}
	
	else if(znak[1]=='-'){ //rez[0]=br[0]*br[1]
		if(znak[2]=='*'){   //br[0]*br[1]-br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		else if(znak[2]=='/'){   //br[0]*br[1]-br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]*br[1]-br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA + regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]*br[1]-br[2]-br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%d", br[2]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB");
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		//rez[2]=rez[0]-rez[1]
		fp = fopen("/dev/alu", "w");
		fprintf(fp, "regA=%d", rez[0]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%d", rez[1]);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA - regB");
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[2]);
		fclose(fp);
	}
	
	printf("Rezultat rez[0]=%d", rez[0]);	
	printf("Rezultat rez[1]=%d", rez[1]);
	printf("Konacni rezultat je %d", rez[2]);
}
/*
else if(znak[0]=='/'){   //br[0]/br[1]
	fp=fopen("/dev/alu","w");
	fprintf(fp, "regA=%d", br[0]);
	fprintf(fp, "regB=%d", br[1]);
	//rez[0]=br[0]/br[1];
	fprintf(fp, "regA / regB");  //  ECHO
	fclose(fp);
	fp=fopen("/dev/alu","r");
	fscanf(fp,"%d", &rez[0]);
	fclose(fp);

	if(znak[1]=='*'){  
	fp=fopen("/dev/alu","w");
	//br[0]/br[1]*br[2]
		//rez[1]=rez[0]*br[2];
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", br[2]);
		fprintf(fp, "regA * regB");  //dvostruki navodnici  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp,"%d", &rez[1]);
		fclose(fp);
		
		if(znak[2]=='*'){   				//br[0]/br[1]*br[2]*br[3]
			fp=fopen("/dev/alu","w");		
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
		else if(znak[2]=='/'){				//br[0]/br[1]*br[2]/br[3]
			//rez[2]=rez[1]/br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
		else if(znak[2]=='+'){				//br[0]/br[1]*br[2]+br[3]
			//rez[2]=rez[1]+br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
		else if(znak[2]=='-'){				//br[0]/br[1]*br[2]-br[3]
			//rez[2]=rez[1]-br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp,"%d",&rez[2]);//CAT
			fclose(fp);
		}			
	}
	
	else if(znak[1]=='/'){				//br[0]/br[1]/br[2]
		//rez[1]=rez[0]/br[2];
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", br[2]);
		fprintf(fp, "regA / regB");  // ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");	
		fscanf(fp,"%d", &rez[1]);//CAT
		fclose(fp);

		if(znak[2]=='*'){   				//br[0]/br[1]/br[2]*br[3]
			//rez[2]=rez[1]*br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
		else if(znak[2]=='/'){				//br[0]/br[1]/br[2]/br[3]
			//rez[2]=rez[1]/br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
		else if(znak[2]=='+'){				//br[0]/br[1]/br[2]+br[3]
			//rez[2]=rez[1]+br[3];
			fp=fopen("/dev/alu","w");	
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
		else if(znak[2]=='-'){				//br[0]/br[1]/br[2]-br[3]
			//rez[2]=rez[1]-br[3];	
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[1]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp,"%d", &rez[2]);//CAT
			fclose(fp);
		}
	}
	
	else if(znak[1]=='+'){   //rez[0]=br[0]/br[1]
		if(znak[2]=='*'){   //br[0]/br[1]+br[2]*br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		
		else if(znak[2]=='/'){   //br[0]/br[1]+br[2]/br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]/br[1]+br[2]+br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]/br[1]+br[2]-br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		//rez[2]=rez[0]-rez[1]
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", rez[1]);
		fprintf(fp, "regA + regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");	
		fscanf(fp, "%d", &rez[2]);
		fclose(fp);
	}
	
	else if(znak[1]=='-'){ //rez[0]=br[0]/br[1]
		if(znak[2]=='*'){   //br[0]/br[1]-br[2]*br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		else if(znak[2]=='/'){   //br[0]/br[1]-br[2]/br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]/br[1]-br[2]+br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]/br[1]-br[2]-br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");	
			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		//rez[2]=rez[0]-rez[1]
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", rez[0]);
		fprintf(fp, "regB=%d", rez[1]);
		fprintf(fp, "regA - regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");	
		fscanf(fp, "%d", &rez[2]);
		fclose(fp);
	}
	
	printf("Konacni rezultat je %d", rez[2]);
}


else if(znak[0]=='+'){ 			//br[0]+br[1]
	if(znak[1]=='*'){   			//znak1 *	
	fp=fopen("/dev/alu","w");
	fprintf(fp, "regA=%d", br[1]);
	fprintf(fp, "regB=%d", br[2]); //br[0]+ (br[1]*br[2])
		//rez[0]=br[1]*br[2];
		fprintf(fp, "regA * regB");  //dvostruki navodnici  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp,"%d", &rez[0]);
		fclose(fp);

		if(znak[2]=='*'){   				//br[0]+br[1]*br[2]*br[3]
			//rez[1]=rez[0]*br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fprintf(fp, "regA * regB");  //  ECHO
			fscanf(fp,"%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='/'){				//br[0]+br[1]*br[2]/br[3]
			fp=fopen("/dev/alu","w");
			//rez[1]=rez[0]/br[3];
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp,"%d", &rez[1]);
		fclose(fp);
		}	
		else if(znak[2]=='+'){				//br[0]+br[1]*br[2]+br[3]
			//rez[1]=rez[0]+br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]*br[2]-br[3]
			//rez[1]=rez[0]-br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[1]);
			fclose(fp);
		} 			
	}
	
	else if(znak[1]=='/'){				//znak1 /
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", br[2]); //br[0]+ (br[1]/br[2])
		//rez[0]=br[1]/br[2];
		fprintf(fp, "regA / regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp,"%d", &rez[0]);
		fclose(fp);

		if(znak[2]=='*'){   				//br[0]+br[1]/br[2]*br[3]
			//rez[1]=rez[0]*br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='/'){				//br[0]+br[1]/br[2]/br[3]
			//rez[1]=rez[0]/br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak[2]=='+'){				//br[0]+br[1]/br[2]+br[3]
			//rez[1]=rez[0]+br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[1]); 
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]/br[2]-br[3]
			//rez[1]=rez[0]-br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp,"%d", &rez[1]);
			fclose(fp);
		}			
	}
	
	else if(znak[1]=='+'){
		if(znak[2]=='*'){   //br[0]+br[1]+br[2]*br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		
		else if(znak[2]=='/'){   //br[0]+br[1]+br[2]/br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]+br[1]+br[2]+br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]+br[2]-br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		//rez[1]=br[1]+rez[0];
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fprintf(fp, "regA + regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[1]);
		fclose(fp);
	}
	
	
	else if(znak[1]=='-'){
		
		if(znak[2]=='*'){   //br[0]+br[1]-br[2]*br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		else if(znak[2]=='/'){   //br[0]+br[1]-br[2]/br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]+br[1]-br[2]+br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]+br[1]-br[2]-br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		
		//rez[1]=br[1]-rez[0];
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fprintf(fp, "regA - regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[1]);
		fclose(fp);
	}
	//rez[2]=br[0]+rez[1];
	fp=fopen("/dev/alu","w");
	fprintf(fp, "regA=%d", br[0]);
	fprintf(fp, "regB=%d", rez[1]);
	fprintf(fp, "regA + regB");  //  ECHO
	fclose(fp);
	fp=fopen("/dev/alu","r");
	fscanf(fp, "%d", &rez[2]);		
	fclose(fp);
	printf("Konacni rezultat je %d", rez[2]);
}

else if(znak[0]=='-'){  			//br[0]-br[1]		
	if(znak[1]=='*'){   			//znak1 * br[0]-br[1]*br[2]	
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", br[2]); // br[0]- (br[1]*br[2])
		//rez[0]=br[1]*br[2];
		fprintf(fp, "regA * regB");  // ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[0]); //CAT
		fclose(fp);

		if(znak[2]=='*'){   				//znak2 *
			//rez[1]=rez[0]*br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}	
		else if(znak[2]=='/'){				//znak2 /
			//rez[1]=rez[0]/br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}
		else if(znak[2]=='+'){				//znak2 +
			//rez[1]=rez[0]+br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", r&ez[1]); //CAT
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//znak2 -
			//rez[1]=rez[0]-br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}
	}
	
	else if(znak[1]=='/'){				
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", br[2]); // br[0]- (br[1]/br[2])
		//rez[0]=br[1]/br[2];
		fprintf(fp, "regA / regB");  //dvostruki navodnici  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[0]); //CAT
		fclose(fp);

		if(znak[2]=='*'){   				
			//rez[1]=rez[0]*br[3];  //br[0]- ((br[1]/br[2]) * br[3])
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}	
		else if(znak[2]=='/'){				
			//rez[1]=rez[0]/br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}
		else if(znak[2]=='+'){				
			//rez[1]=rez[0]+br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}
		else if(znak[2]=='-'){		
			//rez[1]=rez[0]-br[3];
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", rez[0]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[1]); //CAT
			fclose(fp);
		}
	}
	else if(znak[1]=='+'){
		if(znak[2]=='*'){   //br[0]-br[1]+br[2]*br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		
		else if(znak[2]=='/'){   //br[0]-br[1]+br[2]/br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]-br[1]+br[2]+br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]-br[1]+br[2]-br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		//rez[1]=br[1]+rez[0];
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fprintf(fp, "regA + regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[1]);
		fclose(fp);
	}
	
	
	else if(znak[1]=='-'){  //br[0]-br[1]-br[2]
		
		if(znak[2]=='*'){   //br[0]-br[1]-br[2]*br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA * regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		else if(znak[2]=='/'){   //br[0]-br[1]-br[2]/br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA / regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}		
				
		else if(znak[2]=='+'){			//br[0]-br[1]-br[2]+br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA + regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}	
		else if(znak[2]=='-'){				//br[0]-br[1]-br[2]-br[3]
			fp=fopen("/dev/alu","w");
			fprintf(fp, "regA=%d", br[2]);
			fprintf(fp, "regB=%d", br[3]);
			fprintf(fp, "regA - regB");  //  ECHO
			fclose(fp);
			fp=fopen("/dev/alu","r");
			fscanf(fp, "%d", &rez[0]);
			fclose(fp);
		}
		
		//rez[1]=br[1]-rez[0];
		fp=fopen("/dev/alu","w");
		fprintf(fp, "regA=%d", br[1]);
		fprintf(fp, "regB=%d", rez[0]);
		fprintf(fp, "regA - regB");  //  ECHO
		fclose(fp);
		fp=fopen("/dev/alu","r");
		fscanf(fp, "%d", &rez[1]);
		fclose(fp);
	}
	
	
	//rez[2]=br[0]-rez[1];
	fp=fopen("/dev/alu","w");
	fprintf(fp, "regA=%d", br[0]);
	fprintf(fp, "regB=%d", rez[1]);
	fprintf(fp, "regA - regB");  //  ECHO
	fclose(fp);	
	fp=fopen("/dev/alu","r");
	fscanf(fp, "%d",&rez[1]);
	fclose(fp);

	printf("Konacni rezultat je %d", rez[2]);
} else printf("Doslo je do greske prilikom koriscenja /dev/alu");
*/

//	} // od exit
	} //od while
	return 0;
}

