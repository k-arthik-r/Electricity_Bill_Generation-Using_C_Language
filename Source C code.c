// Program for Electricty Bill Generation Based on the Standards Provided by CESC(KPTCL),2022.
#include <stdio.h>
float elc_bill(int units, int prev_redg, int pres_redg); // Function with return type float. Function Declaration
int main(){
    int prev_redg, pres_redg, units, stat;
    float sum, solar_rebate = 50, intrest, arrears, others = 0, tax, total;
    unsigned long long int accid;
    char name[31], address[31], end;
    char tariff[10] = {"3LT2A1-N"}, sancload[11] = {"0.68KW+0HP"};
    printf("Enter Owner's name: ");
    scanf("%[^\n]%*c", name);
    printf("Enter The Address(Area): ");
    scanf("%[^\n]%*c", address);
    printf("Enter 10 digit Account ID: ");
    scanf("%llu", &accid);
    printf("Enter Previous meter reading(Enter 0 if prev regd is unkonwn): ");
    scanf("%d", &prev_redg);
    printf("Enter Present meter reading(Enter number of units consumed if pres regd is unkonwn: ");
    scanf("%d", &pres_redg);
    if (pres_redg < prev_redg){
        printf("Input Error:Previous Reading Cannot be equal to Present Reading ");
        return 0;
    }
    printf("Any Solar Utilization?(Enter 1 if 'YES' or Enter 0 if 'NO'): ");
    scanf("%d", &stat);
    printf("Any Arrears?( If 'YES' Then Enter Arrear Amount and Enter 0 if 'NO'): ");
    scanf("%f", &arrears);
    units = (pres_redg) - (prev_redg);
    printf("\n\n\n");

    printf("       ELECTRICTY  BILL");
    printf("\n******************************");
    printf("\nAccount details");
    printf("\nAccount ID%20llu", accid);
    printf("\n******************************");
    printf("\nPersonal details \nName & Address");
    printf("\n%s \n%s", name, address);
    printf("\n******************************");
    printf("\nConnection details");
    printf("\nTariff%24s\nSanc Load%21s", tariff, sancload);
    sum = elc_bill(units, prev_redg, pres_redg); // Function calling
    if (stat == 1){   // Solar rebate
        if (units < 51)
            solar_rebate = units * 0.50;
    }
    else
        solar_rebate = 0;       
    intrest = 0.05 * arrears;               // Intrest
    tax = 0.05 * (sum + intrest + arrears); // Tax Applied
    printf("\n******************************");
    printf("\nAdditional Charges");
    printf("\nSolar rebate%18.2f", solar_rebate);
    printf("\nIntrest%23.2f", intrest);
    printf("\nArrears%23.2f", arrears);
    printf("\nTax%27.2f", tax);
    printf("\nBill Amount%19.2f", sum);
    printf("\nOthers%24.2f", others);
    total = (sum + intrest + arrears + tax) - solar_rebate;
    printf("\n******************************");
    printf("\nNet Amt Due%19.2f", total);
    printf("\n******************************\n");
    scanf("%c",&end);
    return 0;
}

float elc_bill(int units, int prev_redg, int pres_redg){
    float pf = 1.0, a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, a0 = 4.10, b0 = 5.55, c0 = 7.10, d0 = 8.15, e0 = 0.19, sum;
    int fixed_charge = 0, a, b, c, d, e;
    printf("\n******************************");
    printf("\nConsumption details");
    printf("\nPres.Redg%21d\nPrev.Redg%21d", pres_redg, prev_redg);
    printf("\nConsumption(units)%12d\nPower factor%18.1f", units, pf);
    printf("\n******************************");
    if (units > 50) // Fixed Charges
        fixed_charge = 100;
    else
        fixed_charge = 85;
    float fc = (float)fixed_charge;
    printf("\nFixed Charges(Unit,Rate,Amt)");
    printf("\n1KW%13d%14.2f", fixed_charge, fc);
    printf("\n******************************");
    printf("\nEnergy Charges(Unit,Rate,Amt)"); // Consumption Charges
    if (units <= 50){
        a = units;
        a1 = ((units)*4.1);
        printf("\n%d%15.2f%13.2f", a, a0, a1);
    }
    else if ((units > 50) && (units <= 100)){
        a = 50;
        a1 = ((50) * 4.1);
        b = units - 50;
        b1 = ((b)*5.55);
        printf("\n%d%15.2f%13.2f", a, a0, a1);
        printf("\n%d%15.2f%13.2f", b, b0, b1);
    }
    else if ((units > 100) && (units <= 200)){
        a = 50;
        a1 = ((50) * 4.1);
        b = 50;
        b1 = ((50) * 5.55);
        c = units - 100;
        c1 = ((c)*7.10);
        printf("\n%d%15.2f%13.2f", a, a0, a1);
        printf("\n%d%15.2f%13.2f", b, b0, b1);
        if (c > 99)
            printf("\n%d%14.2f%13.2f", c, c0, c1);
        else
            printf("\n%d%15.2f%13.2f", c, c0, c1);
    }
    else if (units > 200){
        a = 50;
        b = 50;
        c = 100;
        a1 = ((50) * 4.1);
        b1 = ((50) * 5.55);
        c1 = ((100) * 7.10);
        d = units - 200;
        d1 = ((d)*8.15);
        printf("\n%d%15.2f%13.2f", a, a0, a1);
        printf("\n%d%15.2f%13.2f", b, b0, b1);
        if (c > 99)
            printf("\n%d%14.2f%13.2f", c, c0, c1);
        else
            printf("\n%d%15.2f%13.2f", c, c0, c1);
        if (d > 99)
            printf("\n%d%14.2f%13.2f", d, d0, d1);
        else
            printf("\n%d%15.2f%13.2f", d, d0, d1);
    }
    printf("\n******************************");
    printf("\nFAC Charges(Unit,Rate,Amt)"); // FAC Charges
    e = units;
    e1 = 0.19 * units;
    if (units < 99)
        printf("\n%d%15.2f%13.2f", e, e0, e1);
    else if (units > 99)
        printf("\n%d%14.2f%13.2f", e, e0, e1);
    sum = a1 + b1 + c1 + d1 + e1 + fc;
    return sum;
}