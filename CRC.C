#include<stdio.h>
#include<conio.h>
#include<string.h>
#define SIZE 100
#define NULL 0
char* appendingZeros(int total, char dividend[]){
	int dividendLen, i;
	dividendLen = strlen(dividend);
	for(i=0; i<total; i++)
		dividend[dividendLen+i] = '0';
	dividend[dividendLen+i] = '\0';
	return dividend;
}
char* removePreceedingZeros(char str[]){
	int i, j, k;
	char temp[SIZE];
	for(i = 0; i<strlen(str); i++)
		if(str[i] != '0')
			break;
	for(j = i, k=0; j<strlen(str); j++, k++)
		temp[k] = str[j];
	temp[k] = '\0';
	return temp;
}
char* XOR(char divisor[], char dividend[]){
	char temp[SIZE];
	int j;
	for(j=0; j<strlen(divisor); j++)
		if(divisor[j] == dividend[j])
			temp[j] = '0';
		else
			temp[j] = '1';
	temp[j] = '\0';
	return temp;
}
char* append(char s[], char c){
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
	return s;
}
int checkIfCharactersAreZeros(char str[]){
	int i;
	for(i=0; i<strlen(str); i++)
		if(str[i] != '0')
			break;
	if(str[i] != '\0')
		return 0;
	return 1;
}
char* division(char dividend[], char divisor[]){
	int i, j, toBeBroughtDown, toBeBroughtDownPrevious = 0, remaining = 0;
	char *temp = NULL;
	strcpy(temp, dividend);
	temp[strlen(divisor)] = '\0';
	do{
		temp = XOR(divisor, temp);
		temp = removePreceedingZeros(temp);
		toBeBroughtDown = strlen(divisor) - strlen(temp);
		for(i=0; i<toBeBroughtDown; i++)
			temp = append(temp, dividend[strlen(temp) + toBeBroughtDown + toBeBroughtDownPrevious]);
		toBeBroughtDownPrevious += toBeBroughtDown;
		remaining = strlen(dividend) - toBeBroughtDownPrevious;
	}while(dividend[strlen(divisor) +toBeBroughtDownPrevious - 1] != '\0' && (remaining > toBeBroughtDown));
	if(!strlen(temp))
		temp = "0";
	if(strlen(temp) == strlen(divisor))
		temp = XOR(divisor, temp);
	return temp;
}
void onReceiverSide(char divisor[], char oriDivi[], char rem[]){
	int i, j;
	char *senderRemainder, *receiverDividend, *toAdd;
	i = strlen(divisor) - strlen(rem);
	if(i == 0){
		for(j=0; j<strlen(divisor); j++)
			rem[j] = rem[j+1];
		rem[j] = '\0';
		receiverDividend = strcat(oriDivi, rem);
	}
	else if(i > 1){
		for(j=0; j<i-1; j++)
			toAdd[j] = '0';
		toAdd[j] = '\0';
		strcat(toAdd, rem);
		receiverDividend = strcat(oriDivi, toAdd);
	}else
		receiverDividend = strcat(oriDivi, rem);
	printf("\nDivisor: %s",divisor);
	printf("\nDividend of receiver: %s", receiverDividend);
	rem = division(receiverDividend, divisor);
	printf("\nRemainder: %s", rem);
	if(checkIfCharactersAreZeros(rem))
		printf("\nNo Error");
	else
		printf("\nError has Occured");
}
int checkWhetherBinary(char str[]){
	int i;
	for(i=0; i<strlen(str); i++)
		if(str[i] != '1' && str[i] != '0')
			return 0;
	return 1;
}
void main(){
	int flag=0, lenOfDivisor, noOfRedundantBits;
	char *newDividend, *toAdd, dividend[SIZE], divisor[SIZE], *rem, *oriDivi;
	char *receiverDividend;
	clrscr();
	do{
		flag = 0;
		printf("\n\nEnter the dividend at sender side: ");
		gets(dividend);
		printf("\nEnter the divisor: ");
		gets(divisor);
		if(!checkWhetherBinary(divisor) || !checkWhetherBinary(dividend) || !strcmp(dividend,"") || !strcmp(divisor, "")){
			printf("\nInvalid divisor or dividend. Enter again.");
			flag = 1;
		}
		else{
			//If dividend or divisor is being preceeding by 0s
			strcpy(divisor,removePreceedingZeros(divisor));
			strcpy(dividend,removePreceedingZeros(dividend));
			//Copy the value of dividend and storing in original Dividend
			strcpy(oriDivi, dividend);
			lenOfDivisor = strlen(divisor);
			noOfRedundantBits = lenOfDivisor - 1;
			newDividend = appendingZeros(noOfRedundantBits, dividend);
			rem = division(newDividend, divisor);
			printf("\nDivisor: %s",divisor);
			printf("\nDividend of sender: %s", newDividend);
			printf("\nRemainder: %s", rem);
			printf("\n");
			onReceiverSide(divisor, oriDivi, rem);
		}
	}while(flag == 1);
	getch();
}

