#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
	
	FILE *optab,*symtab,*symtabread,*interFile,*prgrmFile,*lenFile,*tempFile;
	remove("symtab.txt");
	
	symtab=fopen("symtab.txt","a");
	
	interFile=fopen("intermediate.txt","w");
	prgrmFile=fopen("program.txt","r");
	lenFile=fopen("length.txt","w");
	
	char label[10],opcode[10],operand[10],symbol[10],mnemonic[10],temp[10];
	int locctr,start,found_opcode,symflag;
    

	fscanf(prgrmFile,"%s\t%s\t%s",label,opcode,operand);
	
	if(strcmp(opcode,"START")==0){
		
		
		tempFile=fopen("tempFile.txt","w");
		fprintf(tempFile,"%s",operand);
		
		fclose(tempFile);
		tempFile=fopen("tempFile.txt","r");
		fscanf(tempFile,"%x",&locctr);
		fclose(tempFile);
		start=locctr;
       
		
		fprintf(interFile,"**\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(prgrmFile,"%s\t%s\t%s",label,opcode,operand);
	}else{
		locctr=0x0;
		start=0x0;
	}
	
	while(!feof(prgrmFile)){
		printf("\t%x\n",locctr);
		if(strcmp(opcode,"END")!=0)
			fprintf(interFile,"%x\t",locctr);
		else
			fprintf(interFile,"**\t**");	
		symflag=0;
		if(strcmp(label,"-")!=0){
			symflag=1;
			
			fclose(symtab);
			symtabread=fopen("symtab.txt","r");
			while(!feof(symtabread)){
				
				fscanf(symtabread,"%s\t%s",symbol,temp);
				
				if(strcmp(symbol,label)==0){
					printf("error :duplicate symnbol found ; %s",symbol);
					exit(1);
				}			
			}
			symtab=fopen("symtab.txt","a");
		}
		if(symflag==1)
			fprintf(symtab,"%s\t%x\n",label,locctr);
		
		found_opcode=0;
        optab=fopen("optab.txt","r");
		while(!feof(optab)){
            
			fscanf(optab,"%s",mnemonic);
			
			if(strcmp(mnemonic,opcode)==0){
				found_opcode=1;
				locctr+=0x3;
				break;			
			}
            
				
		}
        fclose(optab);
		if(found_opcode==0 && strcmp(opcode,"END")!=0){
			
			if(strcmp(opcode,"BYTE")==0)
				locctr+=0x1;
			else if(strcmp(opcode,"RESB")==0)
				locctr+=atoi(operand);
			else if(strcmp(opcode,"WORD")==0)
				locctr+=0x3;
			else if(strcmp(opcode,"RESW")==0)
				locctr+=(atoi(operand)*0x3);
			else{
				printf("invalid opcode found : %s",opcode);
				exit(1);			
			}
			
		}
		else if(strcmp(opcode,"END")==0){
			fprintf(interFile,"\t%s\t%s",opcode,operand);
			printf("%x",locctr);
			fprintf(lenFile,"%x",locctr-start);
			exit(0);
					
		}
		
		fprintf(interFile,"%s\t%s\t%s\n",label,opcode,operand);
		fscanf(prgrmFile,"%s\t%s\t%s",label,opcode,operand);
		

	}
	fclose(interFile);
	fclose(prgrmFile);
	fclose(symtab);
	fclose(symtabread);
	fclose(optab);
}
