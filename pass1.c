#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main() {

	int loc, start, len, found, found1;
    	char opc[10], opr[10], lb[10], temp[10], mne[10],symlb[20],symadr[20];
    	FILE *fprg, *fout, *fopt, *fsym, *flen, *frsym;

    	fprg = fopen("program.txt", "r");
	fout = fopen("object.txt", "w");
    	fopt = fopen("optab.txt", "r");
    	fsym = fopen("symboltable.txt", "w+");
	flen = fopen("length.txt", "w");
	fscanf(fprg, "%s\t%s\t%s", lb, opc, opr);
	if(strcmp(opc, "START")==0) {
		start = atoi(opr);
		loc = start;
		fprintf(fout, "%s\t%s\t%s\n", lb, opc, opr);
		fscanf(fprg, "%s\t%s\t%s", lb, opc, opr);
	}
	else {
		loc = 0;
	}
	while(strcmp(opc, "END")!=0) {
		fprintf(fout, "%d\t", loc);
		printf("%s\t%s\t%s\n", lb, opc, opr);
		if(strcmp(lb, "-")!=0) {
			fprintf(fsym, "%s\t%d\n", lb, loc);
		}else{
			fseek(fsym,SEEK_SET,0);
			fscanf(fsym, "%s\t%s",symlb, symadr);
			while(!feof(fsym)){
				printf("%s \t %s \n",symlb,symadr);
				if(strcmp(symlb,lb)==0){
					printf("Label duplication error");
					exit(0);
				}
				fscanf(fsym,"%s\t%s",symlb,symadr);
			}
			fscanf(fopt, "%s\t%s", temp, mne);
			found = 0;
			while(strcmp(temp, "END")!=0) {
				if(strcmp(opc, temp)==0) {
					found = 1;
					loc+=3;
					break;
				}
				fscanf(fopt, "%s\t%s", temp, mne);
			}
			if(strcmp(opc, "WORD")==0) {
				loc+=3;
			}
			else if(strcmp(opc, "RESW")==0) {
				loc+=(3*(atoi(opr)));
			}
			else if(strcmp(opc, "RESB")==0) {
				loc+=(atoi(opr));
			}
			else if(strcmp(opc, "BYTE")==0) {
				loc++;
			}
			else if(found==0){
				printf("Undefined Opcode");
			}
				
		}
		fscanf(fprg, "%s\t%s\t%s", lb, opc, opr);
	}
	fprintf(fout, "%d\t%s\t%s\t%s\n", loc, lb, opc, opr);
	len = loc-start;
	printf("The length of the program: %d\n", len);
	fprintf(flen,"%d",len);
	fclose(flen);
	fclose(fprg);
	fclose(fout);
	fclose(fopt);
	fclose(fsym);
}	
