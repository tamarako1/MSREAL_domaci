#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{	
	FILE* fp;
	int br0;
	int br1;
	int br2;
	int br3;
int rez0;
int rez1;
int rez2;
	char znak0;
	char znak1;
	char znak2;
	char exit[5];
	int carry;
	size_t num_of_bytes=8;
int ret;
char *str;
	while(1){ 

		printf("\nUnesite izraz: ");	
	//	scanf("%c%c%c%c", &exit[0], &exit[1], &exit[2], exit[3]);

		scanf("%d %c %d %c %d %c %d", &br0, &znak0, &br1, &znak1, &br2, &znak2, &br3);

		printf("\nBroj br[0]je %d", br0);
		printf("\nznak[0]je %c", znak0);
		printf("\nBroj br[1]je %d", br1);
		printf("\nznak[1]je %c", znak1);
		printf("\nBroj br[2]je %d", br2);
		printf("\nznak[2]je %c", znak2);
		printf("\nBroj br[3]je %d\n", br3);


if(znak0=='*'){  					//br[0]*br[1]=rez[0]
	fp = fopen("/dev/alu", "w");                              //otvori
	if(fp == NULL)
	{
		printf("Problem pri otvaranju /dev/alu\n");
		return -1;
	}
	fprintf(fp, "regA=%x\n", br0); 				//upise	
	fclose(fp);
	printf("regA=0x%x\n",br0);
	fp=fopen("/dev/alu", "w");
	fprintf(fp, "regB=%x\n", br1);
	fclose(fp);
	printf("regB=0x%x\n", br1);
	fp=fopen("/dev/alu", "w");
	fprintf(fp,"regA * regB\n");
	fclose(fp);
	fp=fopen("/dev/alu", "r");	//otvori
	if(fp==NULL){
		printf("Problem pri otvaranju /dev/alu za citanje\n");
		return -1;
	} else	printf("Uspesno je otvoren fajl za citanje\n");

	str=(char*)malloc(num_of_bytes+1);
	if(str==NULL){
		printf("Nije lociran str\n");
		return -1;
	}else printf("Uspesno lociran str\n");
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x %d", &rez0, &carry);
//	free(str);
	printf("ret mi je %d\n", ret);//bude 0
	if(ret==2){
	printf("Uspesno procitano iz fp\n");
	printf("rez[0]=0x%x\n", rez0);
	printf("Carry je %d\n", carry);
} else printf("Doslo je do greske prilikom citanja\n");
//	fscanf(fp,"0x%x %c", &rez0, &carry); //cat				procita
	fclose(fp);

printf("rez[0]=%x\n", rez0);
//	printf("proslo je fscanf\n");

	if(znak1=='*'){   			//br[0]*br[1]*br[2]
		fp = fopen("/dev/alu", "w");
		//rez[1]=rez[0]*br[2];
		fprintf(fp, "regA=%x\n", rez0);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%x\n", br2);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA * regB\n"); //echo
		fclose(fp);
		fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x\n", &rez1);
	free(str);

//		fscanf(fp,"%x", &rez[1]);
		fclose(fp);

		if(znak2=='*'){   				//br[0]*br[1]*br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//	if(ret==1){
	printf("Uspesno procitano iz fp\n");
	printf("rez[2]=0x%x\n", rez2);
//} else printf("Doslo je do greske prilikom citanja");

//			fscanf(fp,"%x", &rez[2]);
			fclose(fp);
		}	
		else if(znak2=='/'){				//br[0]*br[1]*br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);

//			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}	
		else if(znak2=='+'){				//br[0]*br[1]*br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA + regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//			fscanf(fp,"%d", &rez[2]); //cat
			fclose(fp);
		}
		else if(znak2=='-'){				//br[0]*br[1]*br[2]-br[3]
			fp = fopen("/dev/alu", "w");
	//rez[2]=rez[1]-br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}			
	}
	
	else if(znak1=='/'){				
		fp = fopen("/dev/alu", "w");
		//rez[1]=rez[0]/br[2];
		fprintf(fp, "regA=%x\n", rez0);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%x\n", br2);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA / regB\n");
		fclose(fp);
		fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//		fscanf(fp,"%d", &rez[1]);	//cat
		fclose(fp);

		if(znak2=='*'){   				
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]*br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
		else if(znak2=='/'){
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]/br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
		else if(znak2=='+'){				
			fp = fopen("/dev/alu", "w");
			//rez[2]=rez[1]+br[3];
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA + regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
		else if(znak2=='-'){				
		//rez[2]=rez[1]-br[3];		
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", rez1);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//			fscanf(fp,"%d", &rez[2]);
			fclose(fp);
		}
	}
	else if(znak1=='+'){   //rez[0]=br[0]*br[1]
			if(znak2=='*'){   //br[0]*br[1]+br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
			}
		
		else if(znak2=='/'){   //br[0]*br[1]+br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");	
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}		
				
		else if(znak2=='+'){			//br[0]*br[1]+br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");		
			fprintf(fp, "regA + regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak2=='-'){				//br[0]/br[1]+br[2]-br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		fp = fopen("/dev/alu", "w");
		//rez[2]=rez[0]-rez[1]
		fprintf(fp, "regA=%x\n", rez0);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%x\n", rez1);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA + regB\n");
		fclose(fp);
		fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez2);
	free(str);
//		fscanf(fp, "%d", &rez[2]);
		fclose(fp);
	}
	
	else if(znak1=='-'){ //rez[0]=br[0]*br[1]
		if(znak2=='*'){   //br[0]*br[1]-br[2]*br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA * regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		else if(znak2=='/'){   //br[0]*br[1]-br[2]/br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA / regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}		
				
		else if(znak2=='+'){			//br[0]*br[1]-br[2]+br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA + regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}	
		else if(znak2=='-'){				//br[0]*br[1]-br[2]-br[3]
			fp = fopen("/dev/alu", "w");
			fprintf(fp, "regA=%x\n", br2);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regB=%x\n", br3);
			fclose(fp);
			fp=fopen("/dev/alu", "w");
			fprintf(fp, "regA - regB\n");
			fclose(fp);
			fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//			fscanf(fp, "%d", &rez[1]);
			fclose(fp);
		}
		//rez[2]=rez[0]-rez[1]
		fp = fopen("/dev/alu", "w");
		fprintf(fp, "regA=%x\n", rez0);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regB=%x\n", rez1);
		fclose(fp);
		fp=fopen("/dev/alu", "w");
		fprintf(fp, "regA - regB\n");
		fclose(fp);
		fp=fopen("/dev/alu","r");
	str=(char*)malloc(num_of_bytes+1);
	getline(&str, &num_of_bytes, fp);
	ret=sscanf(str, "0x%x", &rez1);
	free(str);
//		fscanf(fp, "%d", &rez[2]);
		fclose(fp);
	}
	
	printf("Rezultat rez[0]=0x%x\n", rez0);	
	printf("Rezultat rez[1]=0x%x\n", rez1);
	printf("Konacni rezultat je 0x%x\n", rez2);
}return 1; //da ne ode u besk petlju
} //od while
return 0;
}
