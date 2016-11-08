//
//  main.c
//  TDS
//
//  Created by chen jeremy on 5/26/16.
//  Copyright © 2016 chen jeremy. All rights reserved.
//

#include <stdio.h>


/////////////////////////////VALUE for (temp,tds)//////////////////////////////////////////////

#define VALUE__40DEGREE_0TDS 380
#define VALUE__50DEGREE_0TDS 388
#define VALUE__60DEGREE_0TDS 412
#define VALUE__70DEGREE_0TDS 446
#define VALUE__80DEGREE_0TDS 472


#define VALUE__40DEGREE_25TDS 440
#define VALUE__50DEGREE_25TDS 472
#define VALUE__60DEGREE_25TDS 507
#define VALUE__70DEGREE_25TDS 550
#define VALUE__80DEGREE_25TDS 580


#define VALUE__40DEGREE_50TDS 490
#define VALUE__50DEGREE_50TDS 528
#define VALUE__60DEGREE_50TDS 565
#define VALUE__70DEGREE_50TDS 590
#define VALUE__80DEGREE_50TDS 635


#define VALUE__40DEGREE_75TDS 553
#define VALUE__50DEGREE_75TDS 591
#define VALUE__60DEGREE_75TDS 625
#define VALUE__70DEGREE_75TDS 643
#define VALUE__80DEGREE_75TDS 655


#define VALUE__40DEGREE_100TDS 587
#define VALUE__50DEGREE_100TDS 623
#define VALUE__60DEGREE_100TDS 648
#define VALUE__70DEGREE_100TDS 665
#define VALUE__80DEGREE_100TDS 710

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

int Determine_TDSintervial(double TEMP_taste,double TDS_taste);
double Determine_SLOPE(double Temp,double TempNext,int TDSConsentration);
double Determine_THEORETICAL_SLOPE_UP(double TEMP,double TDS,int interval);
double Determine_THEORETICAL_SLOPE_DOWN(double TEMP,double TDS,int interval);
double Determine_THEORETICAL_TDS(double TEMP_taste,double TDS_taste,double interval_taste,double TEMP_current);

int main() {
    // insert code here...
    double TEMP_current,TDS_current,TDS_Theoretical,TEMP_predict,TDS_taste,TEMP_taste;
    int    interval_current,interval_taste,interval;
    double i,j,Slope,SLOPE__interpolation;//測試碼宣告
    
    
    printf("Enter the taste of TEMP:");
    scanf("%lf",&TEMP_taste);
    
    printf("Enter the taste of TDS:");
    scanf("%lf",&TDS_taste);
    
    for (i =80; i!=35; i=i-5) {
        TEMP_predict = i;
        interval_taste = Determine_TDSintervial(TEMP_taste,TDS_taste);//enter the current TEMP and TDS
        TDS_Theoretical = Determine_THEORETICAL_TDS(TEMP_taste,TDS_taste, interval_taste, TEMP_predict);
        printf("%lf \n",TDS_Theoretical);
    }
    
    return 0;
}
//算ＴＤＳ在哪ㄧ個區間
int Determine_TDSintervial(double TEMP_taste,double TDS_taste){
    int intervial=1;//含自己的區間
    
    if (50 >= TEMP_taste) {
        
            if (Determine_SLOPE(40.0, 50.0, 0)*(TEMP_taste - 40)+VALUE__40DEGREE_0TDS >= TDS_taste)     {intervial = 0;}
            else if (Determine_SLOPE(40.0, 50.0, 25)*(TEMP_taste - 40)+VALUE__40DEGREE_25TDS >= TDS_taste)   {intervial = 25;}
            else if (Determine_SLOPE(40.0, 50.0, 50)*(TEMP_taste - 40)+VALUE__40DEGREE_50TDS >= TDS_taste)   {intervial = 50;}
            else if (Determine_SLOPE(40.0, 50.0, 75)*(TEMP_taste - 40)+VALUE__40DEGREE_75TDS >= TDS_taste)   {intervial = 75;}
            else if (Determine_SLOPE(40.0, 50.0, 100)*(TEMP_taste - 40)+VALUE__40DEGREE_100TDS >= TDS_taste) {intervial = 100;}
            else if (TDS_taste > Determine_SLOPE(40.0, 50.0, 100)*(TEMP_taste - 40)+VALUE__40DEGREE_100TDS ) {intervial = 100;}
    }
    
    else if (60 >= TEMP_taste) {
        
            if (Determine_SLOPE(50.0, 60.0, 0)*(TEMP_taste - 50)+VALUE__50DEGREE_0TDS >= TDS_taste)   {intervial = 0;}
            else  if (Determine_SLOPE(50.0, 60.0, 25)*(TEMP_taste - 50)+VALUE__50DEGREE_25TDS >= TDS_taste)  {intervial = 25;}
            else  if (Determine_SLOPE(50.0, 60.0, 50)*(TEMP_taste - 50)+VALUE__50DEGREE_50TDS >= TDS_taste)  {intervial = 50;}
            else  if (Determine_SLOPE(50.0, 60.0, 75)*(TEMP_taste - 50)+VALUE__50DEGREE_75TDS >= TDS_taste)  {intervial = 75;}
            else  if (Determine_SLOPE(50.0, 60.0, 100)*(TEMP_taste - 50)+VALUE__50DEGREE_100TDS >= TDS_taste) {intervial = 100;}
            else  if (TDS_taste > Determine_SLOPE(50.0, 60.0, 100)*(TEMP_taste - 50)+VALUE__50DEGREE_100TDS)  {intervial = 100;}
    }
    
    else if (70 >= TEMP_taste) {
            if (Determine_SLOPE(60.0, 70.0, 0)*(TEMP_taste - 60)+VALUE__60DEGREE_0TDS >= TDS_taste)   {intervial = 0;}
            else if (Determine_SLOPE(60.0, 70.0, 25)*(TEMP_taste - 60)+VALUE__60DEGREE_25TDS >= TDS_taste)  {intervial = 25;}
            else if (Determine_SLOPE(60.0, 70.0, 50)*(TEMP_taste - 60)+VALUE__60DEGREE_50TDS >= TDS_taste)  {intervial = 50;}
            else if (Determine_SLOPE(60.0, 70.0, 75)*(TEMP_taste - 60)+VALUE__60DEGREE_75TDS >= TDS_taste)  {intervial = 75;}
            else if (Determine_SLOPE(60.0, 70.0, 100)*(TEMP_taste - 60)+VALUE__60DEGREE_100TDS >= TDS_taste) {intervial = 100;}
            else if (TDS_taste > Determine_SLOPE(60.0, 70.0, 100)*(TEMP_taste - 60)+VALUE__60DEGREE_100TDS)  {intervial = 100;}
    }
    
    else {
            if (Determine_SLOPE(70.0, 80.0, 0)*(TEMP_taste - 70)+VALUE__70DEGREE_0TDS >= TDS_taste)   {intervial = 0;}
            else if (Determine_SLOPE(70.0, 80.0, 25)*(TEMP_taste - 70)+VALUE__70DEGREE_25TDS >= TDS_taste)  {intervial = 25;}
            else if (Determine_SLOPE(70.0, 80.0, 50)*(TEMP_taste - 70)+VALUE__70DEGREE_50TDS >= TDS_taste)  {intervial = 50;}
            else if (Determine_SLOPE(70.0, 80.0, 75)*(TEMP_taste - 70)+VALUE__70DEGREE_75TDS >= TDS_taste)  {intervial = 75;}
            else if (Determine_SLOPE(70.0, 80.0, 100)*(TEMP_taste - 70)+VALUE__70DEGREE_100TDS >= TDS_taste) {intervial = 100;}
            else if (TDS_taste > Determine_SLOPE(70.0, 80.0, 100)*(TEMP_taste - 70)+VALUE__70DEGREE_100TDS)  {intervial = 100;}
            else{intervial=1;}
    }
    
    return intervial;
}
//算溫度區間指定ＴＤＳ斜率
double Determine_SLOPE(double Temp,double TempNext,int TDSConsentration){
    //算0TDS個溫度區間的斜率
    double Slope;
    if (TDSConsentration == 0) {
        if (Temp == 40 && TempNext == 50) {
            Slope = (VALUE__50DEGREE_0TDS-VALUE__40DEGREE_0TDS)/(50.0-40.0);
            return Slope;
        }
        if (Temp == 50 && TempNext == 60) {
            Slope = (VALUE__60DEGREE_0TDS-VALUE__50DEGREE_0TDS)/(60.0-50.0);
            return Slope;
        }
        if (Temp == 60 && TempNext == 70) {
            Slope = (VALUE__70DEGREE_0TDS-VALUE__60DEGREE_0TDS)/(70.0-60.0);
            return Slope;
        }
        if (Temp == 70 && TempNext == 80) {
            Slope = (VALUE__80DEGREE_0TDS-VALUE__70DEGREE_0TDS)/(80.0-70.0);
            return Slope;
        }
        
    }
    
    if (TDSConsentration == 25) {
        if (Temp == 40 && TempNext == 50) {
            Slope = (VALUE__50DEGREE_25TDS-VALUE__40DEGREE_25TDS)/(50.0-40.0);
            return Slope;
        }
        if (Temp == 50 && TempNext == 60) {
            Slope = (VALUE__60DEGREE_25TDS-VALUE__50DEGREE_25TDS)/(60.0-50.0);
            return Slope;
        }
        if (Temp == 60 && TempNext == 70) {
            Slope = (VALUE__70DEGREE_25TDS-VALUE__60DEGREE_25TDS)/(70.0-60.0);
            return Slope;
        }
        if (Temp == 70 && TempNext == 80) {
            Slope = (VALUE__80DEGREE_25TDS-VALUE__70DEGREE_25TDS)/(80.0-70.0);
            return Slope;
        }
        
    }
    
    if (TDSConsentration == 50) {
        if (Temp == 40 && TempNext == 50) {
            Slope = (VALUE__50DEGREE_50TDS-VALUE__40DEGREE_50TDS)/(50.0-40.0);
            return Slope;
        }
        if (Temp == 50 && TempNext == 60) {
            Slope = (VALUE__60DEGREE_50TDS-VALUE__50DEGREE_50TDS)/(60.0-50.0);
            return Slope;
        }
        if (Temp == 60 && TempNext == 70) {
            Slope = (VALUE__70DEGREE_50TDS-VALUE__60DEGREE_50TDS)/(70.0-60.0);
            return Slope;
        }
        if (Temp == 70 && TempNext == 80) {
            Slope = (VALUE__80DEGREE_50TDS-VALUE__70DEGREE_50TDS)/(80.0-70.0);
            return Slope;
        }
        
    }
    
    if (TDSConsentration == 75) {
        if (Temp == 40 && TempNext == 50) {
            Slope = (VALUE__50DEGREE_75TDS-VALUE__40DEGREE_75TDS)/(50.0-40.0);
            return Slope;
        }
        if (Temp == 50 && TempNext == 60) {
            Slope = (VALUE__60DEGREE_75TDS-VALUE__50DEGREE_75TDS)/(60.0-50.0);
            return Slope;
        }
        if (Temp == 60 && TempNext == 70) {
            Slope = (VALUE__70DEGREE_75TDS-VALUE__60DEGREE_75TDS)/(70.0-60.0);
            return Slope;
        }
        if (Temp == 70 && TempNext == 80) {
            Slope = (VALUE__80DEGREE_75TDS-VALUE__70DEGREE_75TDS)/(80.0-70.0);
            return Slope;
        }
        
    }
    
    if (TDSConsentration == 100) {
        if (Temp == 40 && TempNext == 50) {
            Slope = (VALUE__50DEGREE_100TDS-VALUE__40DEGREE_100TDS)/(50.0-40.0);
            return Slope;
        }
        if (Temp == 50 && TempNext == 60) {
            Slope = (VALUE__60DEGREE_100TDS-VALUE__50DEGREE_100TDS)/(60.0-50.0);
            return Slope;
        }
        if (Temp == 60 && TempNext == 70) {
            Slope = (VALUE__70DEGREE_100TDS-VALUE__60DEGREE_100TDS)/(70.0-60.0);
            return Slope;
        }
        if (Temp == 70 && TempNext == 80) {
            Slope = (VALUE__80DEGREE_100TDS-VALUE__70DEGREE_100TDS)/(80.0-70.0);
            return Slope;
        }
        
    }
    
    return  1;

}
//算理論上的斜率，利用內插法，以本身與往上點的斜率為基準
double Determine_THEORETICAL_SLOPE_UP(double TEMP,double TDS,int interval){
    double uplimit_tds,downlimit_tds,SLOPE_interpolation = 0.0,THEORETICAL_SLOPE = 0.0,TEMP_range;
    
    TEMP_range = TEMP/10;
    
    if (interval == 0) {
        if (TEMP_range < 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 0)*(TEMP - 40)+VALUE__40DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;

        }
        else if (5 <= TEMP_range && TEMP_range < 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 0)*(TEMP - 50)+VALUE__50DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;

        }
        else if (6 <= TEMP_range && TEMP_range < 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 0)*(TEMP - 60)+VALUE__60DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;
            
        }
        else if (7 <= TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 0)*(TEMP - 70)+VALUE__70DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;
            
        }else{printf("omething Wrong with Determine_THEORETICAL_SLOPE in interval 0\n");}
    }
    
    if (interval == 25) {
        if (TEMP_range < 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 25)*(TEMP - 40)+VALUE__40DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 0)*(TEMP - 40)+VALUE__40DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 25)-Determine_SLOPE(40, 50, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 0);
            
        }
        else if (5 <= TEMP_range && TEMP_range < 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 25)*(TEMP - 50)+VALUE__50DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 0)*(TEMP - 50)+VALUE__50DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 25)-Determine_SLOPE(50, 60, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 0);
            
        }
        else if (6 <= TEMP_range && TEMP_range < 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 25)*(TEMP - 60)+VALUE__60DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 0)*(TEMP - 60)+VALUE__60DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 25)-Determine_SLOPE(60, 70, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 0);
            
        }
        else if (7 <= TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 25)*(TEMP - 70)+VALUE__70DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 0)*(TEMP - 70)+VALUE__70DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 25)-Determine_SLOPE(70, 80, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 0);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 25\n");}
    }
    
    if (interval == 50) {
        if (TEMP_range < 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 50)*(TEMP - 40)+VALUE__40DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 25)*(TEMP - 40)+VALUE__40DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 50)-Determine_SLOPE(40, 50, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 25);
            
        }
        else if (5 <= TEMP_range && TEMP_range < 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 50)*(TEMP - 50)+VALUE__50DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 25)*(TEMP - 50)+VALUE__50DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 50)-Determine_SLOPE(50, 60, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 25);
            
        }
        else if (6 <= TEMP_range && TEMP_range < 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 50)*(TEMP - 60)+VALUE__60DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 25)*(TEMP - 60)+VALUE__60DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 50)-Determine_SLOPE(60, 70, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 25);
            
        }
        else if (7 <= TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 50)*(TEMP - 70)+VALUE__70DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 25)*(TEMP - 70)+VALUE__70DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 50)-Determine_SLOPE(70, 80, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 25);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 50\n");}
    }
    
    if (interval == 75) {
        if (TEMP_range < 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 75)*(TEMP - 40)+VALUE__40DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 50)*(TEMP - 40)+VALUE__40DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 75)-Determine_SLOPE(40, 50, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 50);
            
        }
        else if (5 <= TEMP_range && TEMP_range < 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 75)*(TEMP - 50)+VALUE__50DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 50)*(TEMP - 50)+VALUE__50DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 75)-Determine_SLOPE(50, 60, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 50);
            
        }
        else if (6 <= TEMP_range && TEMP_range < 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 75)*(TEMP - 60)+VALUE__60DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 50)*(TEMP - 60)+VALUE__60DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 75)-Determine_SLOPE(60, 70, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 50);
            
        }
        else if (7 <= TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 75)*(TEMP - 70)+VALUE__70DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 50)*(TEMP - 70)+VALUE__70DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 75)-Determine_SLOPE(70, 80, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 50);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 75\n");}
    }
    
    if (interval == 100) {
        if (TEMP_range < 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 100)*(TEMP - 40)+VALUE__40DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 75)*(TEMP - 40)+VALUE__40DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 100)-Determine_SLOPE(40, 50, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 75);
            
        }
        else if (5 <= TEMP_range && TEMP_range < 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 100)*(TEMP - 50)+VALUE__50DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 75)*(TEMP - 50)+VALUE__50DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 100)-Determine_SLOPE(50, 60, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 75);
            
        }
        else if (6 <= TEMP_range && TEMP_range < 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 100)*(TEMP - 60)+VALUE__60DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 75)*(TEMP - 60)+VALUE__60DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 100)-Determine_SLOPE(60, 70, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 75);
            
        }
        else if (7 <= TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 100)*(TEMP - 70)+VALUE__70DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 75)*(TEMP - 70)+VALUE__70DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 100)-Determine_SLOPE(70, 80, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 75);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 100\n");}
    }
    if (interval ==1) {
        printf("Something wrong with interval\n");
    }
    
    return THEORETICAL_SLOPE;

}

//算理論上的斜率，利用內插法，以本身與往上點的斜率為基準
double Determine_THEORETICAL_SLOPE_DOWN(double TEMP,double TDS,int interval){
    double uplimit_tds,downlimit_tds,SLOPE_interpolation = 0.0,THEORETICAL_SLOPE = 0.0,TEMP_range;
    
    TEMP_range = TEMP/10;
    
    if (interval == 0) {
        if (TEMP_range <= 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 0)*(TEMP - 40)+VALUE__40DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;
            
        }
        else if (5 < TEMP_range && TEMP_range <= 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 0)*(TEMP - 50)+VALUE__50DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;
            
        }
        else if (6 < TEMP_range && TEMP_range <= 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 0)*(TEMP - 60)+VALUE__60DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;
            
        }
        else if (7 < TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 0)*(TEMP - 70)+VALUE__70DEGREE_0TDS;
            downlimit_tds = 0;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 0)-0)/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+0;
            
        }else{printf("omething Wrong with Determine_THEORETICAL_SLOPE in interval 0\n");}
    }
    
    if (interval == 25) {
        if (TEMP_range <= 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 25)*(TEMP - 40)+VALUE__40DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 0)*(TEMP - 40)+VALUE__40DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 25)-Determine_SLOPE(40, 50, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 0);
            
        }
        else if (5 < TEMP_range && TEMP_range <= 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 25)*(TEMP - 50)+VALUE__50DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 0)*(TEMP - 50)+VALUE__50DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 25)-Determine_SLOPE(50, 60, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 0);
            
        }
        else if (6 < TEMP_range && TEMP_range <= 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 25)*(TEMP - 60)+VALUE__60DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 0)*(TEMP - 60)+VALUE__60DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 25)-Determine_SLOPE(60, 70, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 0);
            
        }
        else if (7 < TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 25)*(TEMP - 70)+VALUE__70DEGREE_25TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 0)*(TEMP - 70)+VALUE__70DEGREE_0TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 25)-Determine_SLOPE(70, 80, 0))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 0);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 25\n");}
    }
    
    if (interval == 50) {
        if (TEMP_range <= 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 50)*(TEMP - 40)+VALUE__40DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 25)*(TEMP - 40)+VALUE__40DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 50)-Determine_SLOPE(40, 50, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 25);
            
        }
        else if (5 < TEMP_range && TEMP_range <= 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 50)*(TEMP - 50)+VALUE__50DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 25)*(TEMP - 50)+VALUE__50DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 50)-Determine_SLOPE(50, 60, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 25);
            
        }
        else if (6 < TEMP_range && TEMP_range <= 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 50)*(TEMP - 60)+VALUE__60DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 25)*(TEMP - 60)+VALUE__60DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 50)-Determine_SLOPE(60, 70, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 25);
            
        }
        else if (7 < TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 50)*(TEMP - 70)+VALUE__70DEGREE_50TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 25)*(TEMP - 70)+VALUE__70DEGREE_25TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 50)-Determine_SLOPE(70, 80, 25))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 25);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 50\n");}
    }
    
    if (interval == 75) {
        if (TEMP_range <= 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 75)*(TEMP - 40)+VALUE__40DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 50)*(TEMP - 40)+VALUE__40DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 75)-Determine_SLOPE(40, 50, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 50);
            
        }
        else if (5 < TEMP_range && TEMP_range <= 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 75)*(TEMP - 50)+VALUE__50DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 50)*(TEMP - 50)+VALUE__50DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 75)-Determine_SLOPE(50, 60, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 50);
            
        }
        else if (6 < TEMP_range && TEMP_range <= 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 75)*(TEMP - 60)+VALUE__60DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 50)*(TEMP - 60)+VALUE__60DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 75)-Determine_SLOPE(60, 70, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 50);
            
        }
        else if (7 < TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 75)*(TEMP - 70)+VALUE__70DEGREE_75TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 50)*(TEMP - 70)+VALUE__70DEGREE_50TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 75)-Determine_SLOPE(70, 80, 50))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 50);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 75\n");}
    }
    
    if (interval == 100) {
        if (TEMP_range <= 5) {
            uplimit_tds = Determine_SLOPE(40, 50, 100)*(TEMP - 40)+VALUE__40DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(40, 50, 75)*(TEMP - 40)+VALUE__40DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(40, 50, 100)-Determine_SLOPE(40, 50, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(40, 50, 75);
            
        }
        else if (5 < TEMP_range && TEMP_range <= 6) {
            uplimit_tds = Determine_SLOPE(50, 60, 100)*(TEMP - 50)+VALUE__50DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(50, 60, 75)*(TEMP - 50)+VALUE__50DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(50, 60, 100)-Determine_SLOPE(50, 60, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(50, 60, 75);
            
        }
        else if (6 < TEMP_range && TEMP_range <= 7) {
            uplimit_tds = Determine_SLOPE(60, 70, 100)*(TEMP - 60)+VALUE__60DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(60, 70, 75)*(TEMP - 60)+VALUE__60DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(60, 70, 100)-Determine_SLOPE(60, 70, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(60, 70, 75);
            
        }
        else if (7 < TEMP_range) {
            uplimit_tds = Determine_SLOPE(70, 80, 100)*(TEMP - 70)+VALUE__70DEGREE_100TDS;
            downlimit_tds = Determine_SLOPE(70, 80, 75)*(TEMP - 70)+VALUE__70DEGREE_75TDS;
            SLOPE_interpolation = (Determine_SLOPE(70, 80, 100)-Determine_SLOPE(70, 80, 75))/(uplimit_tds-downlimit_tds);
            THEORETICAL_SLOPE = SLOPE_interpolation*(TDS-downlimit_tds)+Determine_SLOPE(70, 80, 75);
            
        }else{printf("Something Wrong with Determine_THEORETICAL_SLOPE in interval 100\n");}
    }
    if (interval ==1) {
        printf("Something wrong with interval\n");
    }
    
    return THEORETICAL_SLOPE;
    
}
//算在那溫度下，理論上ＴＤＳ值是多少
double Determine_THEORETICAL_TDS(double TEMP_taste,double TDS_taste,double interval_taste,double TEMP_current){

    double Slope,TDS_Theoretical,uplimit_temp,downlimit_temp,uplimit_tds,downlimit_tds;
    int TEMP_taste_digit,TEMP_current_digit,i,j;
    
    //算溫度的十位數
    TEMP_taste_digit = TEMP_taste/10;
    TEMP_current_digit = TEMP_current/10;
    
    Slope = Determine_THEORETICAL_SLOPE_UP(TEMP_taste, TDS_taste, interval_taste);

    //算TEMP_taste這溫度區間的溫度最大值與ＴＤＳ最大值
    uplimit_temp = TEMP_taste_digit*10+10;
    uplimit_tds = Slope*(uplimit_temp - TEMP_taste) + TDS_taste;
    
    //算TEMP_taste這溫度區間的溫度最小值與ＴＤＳ最小值
    downlimit_temp = TEMP_taste_digit*10;
    downlimit_tds = Slope*(downlimit_temp - TEMP_taste) + TDS_taste;
    
    
    if (TEMP_current_digit == TEMP_taste_digit) {
        Slope = Determine_THEORETICAL_SLOPE_UP(TEMP_taste, TDS_taste, interval_taste);
        TDS_Theoretical = Slope*(TEMP_current - TEMP_taste) + TDS_taste;
        return TDS_Theoretical;
    }
    
    if (TEMP_current_digit > TEMP_taste_digit) {
        
        
        //往上100度為限
        for (i = 1; i<10 ; i++) {
            if (TEMP_current_digit == TEMP_taste_digit+i) {
                
                for (j = 1; j<i ; j++) {
                    
                    Slope = Determine_THEORETICAL_SLOPE_UP(uplimit_temp, uplimit_tds, interval_taste);
                    uplimit_tds = Slope*(10)+uplimit_tds;//10度差(之後uplimit-之前uplimit)
                    uplimit_temp =uplimit_temp +10;
                    
                }
                Slope = Determine_THEORETICAL_SLOPE_UP(uplimit_temp, uplimit_tds, interval_taste);
                TDS_Theoretical = Slope*(TEMP_current - uplimit_temp) + uplimit_tds;
                return TDS_Theoretical;
            }

        }
        
        
        
    }
    
    if (TEMP_current_digit < TEMP_taste_digit) {
        
        
        //往下100度為限
        for (i = 1; i<10 ; i++) {
            if (TEMP_current_digit == TEMP_taste_digit-i) {
                
                for (j = 1; j<i ; j++) {
                    
                    Slope = Determine_THEORETICAL_SLOPE_DOWN(downlimit_temp, downlimit_tds, interval_taste);
                    downlimit_tds = Slope*(-10)+downlimit_tds;//10度差(之後uplimit-之前uplimit)
                    downlimit_temp =downlimit_temp -10;
                    
                }
                Slope = Determine_THEORETICAL_SLOPE_DOWN(downlimit_temp, downlimit_tds, interval_taste);
                TDS_Theoretical = Slope*(TEMP_current-downlimit_temp)+downlimit_tds;
                return TDS_Theoretical;
            }
            
        }
        
    }


    return 1;//error

}



