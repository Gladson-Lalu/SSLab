#include<stdio.h>
#include<string.h>
void main()
{
	FILE *fin,*ftab,*flen,*fsym,*fout;
	int i,j=0,len;
	char adr[10],symadr[10],op[10],start[10],temp[30],line[20],label[20],opc[10],operand[10],symtab[10],opmne[10];
	fin=fopen("object.txt","r");
	flen=fopen("length.txt","r");
	ftab=fopen("optab.txt","r");
	fsym=fopen("symboltable.txt","r");
	fout=fopen("output.txt","w");
	fscanf(fin,"%s\t%s\t%s\t%s",adr,label,opc,operand);
	if(strcmp(opc,"START")==0){
		strcpy(start,operand);
		fscanf(flen,"%d",&len);
	}
	printf("H^%s^%s^%d\nT^00%s^",label,start,len,start);
	fprintf(fout,"H^%s^%s^%d\nT^00%s^",label,start,len,start);
	fscanf(fin,"%s\t%s\t%s\t%s",adr,label,opc,operand);
	while(strcmp(opc,"END")!=0){
		while(!feof(ftab)){
			fscanf(ftab,"%s\t%s",opmne,op);
			if(strcmp(opc,opmne)==0){
				fclose(ftab);
				while(!feof(fsym)){
					fscanf(fsym,"%s\t%s",symadr,symtab);
					if(strcmp(operand,symtab)==0){
						printf("%s%s^",op,symadr);
						fprintf(fout,"%s%s^",op,symadr);
						break;
					}
				}
				break;
			}
		}
		if((strcmp(opc,"BYTE")==0)||(strcmp(opc,"WORD")==0)){
			if(strcmp(opc,"WORD")==0){
				printf("0000%s^",operand);
				fprintf(fout,"0000%s^",operand);
			}
			else{
				len=strlen(operand);
				for(i=2;i<len;i++){
					printf("%d",operand[i]);
					fprintf(fout,"%d",operand[i]);
				}
				printf("^");
				fprintf(fout,"^");
			}
		}
		fscanf(fin,"%s\t%s\t%s\t%s",adr,label,opc,operand);
		ftab=fopen("optab.txt","r");
		fseek(ftab,SEEK_SET,0);
	}
	printf("\nE^00%s\n\n",start);
	fprintf(fout,"\nE^00%s\n\n",start);
	fclose(fin);
	fclose(ftab);
	fclose(fsym);
	fclose(flen);
	fclose(fout);
}


