#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int btn = 7;

unsigned long int tc_roll;

unsigned long int t;
unsigned long int tp;
unsigned long int tf;
unsigned long int tc;
void HandleTime()
{
    t = millis();
    tf = t - tp;
    tc += tf;
    tc_roll += tf;
    tp = t;
}
boolean IsNewSecond()
{
    boolean c = ( tc > 1000  );
    if( c ) tc = tc % 1000;
    return c;
}

int btn_status;
void HandleBtn()
{
    if( digitalRead( btn ) == HIGH )
    {
        switch( btn_status )
        {
            case 1: btn_status = 2; break;
            case 0: btn_status = 1; break;
        }
    }
    else btn_status = 0;
}
boolean IsClicked()
{
    return ( btn_status == 1 );
}

void ShowMsg( String msg )
{
    lcd.setCursor( 0, 1 );
    lcd.print( "                " );
    lcd.setCursor( 0, 1 );
    lcd.print( msg );
}

long int money;
long int money_prev;
void ShowMoney()
{
    if( money != money_prev )
    {
        lcd.setCursor( 0, 0 );
        lcd.print( "       " );
        lcd.setCursor( 0, 0 );
        lcd.print( "$" + String( money ) );
        money_prev = money;
    }
}

unsigned int bar_1;
unsigned int bar_2;
unsigned int bar_3;
unsigned int roll_1;
unsigned int roll_2;
unsigned int roll_3;
unsigned int rmax_1;
unsigned int rmax_2;
unsigned int rmax_3;
float tf_1;
float tf_2;
float tf_3;
boolean rolling;

void ShowRoll()
{
        lcd.setCursor( 7, 0 );
        lcd.print( "< " + String( bar_1 ) + " " + String( bar_2 ) + " " + String( bar_3 ) + " >"  );
}
void FinalizeRoll()
{
    rolling = false;
    if( bar_1 == bar_2 && bar_2 == bar_3 && bar_3 == 7 )
    {
        money += 5000;
        ShowMsg( "Jackpot! +$5000" ); 
    }
    else if( bar_1 == bar_2 && bar_2 == bar_3 )
    {
        money += bar_1 * 70;
        ShowMsg( "Triple! +$70x" + String(bar_1)  ); 
    }
    else if( bar_1 == bar_2  )
    {
        money += bar_1 * 5;
        ShowMsg( "Double! +$5x" + String(bar_1)  ); 
    }
    else if( bar_2 == bar_3  )
    {
        money += bar_2 * 5;
        ShowMsg( "Double! +$5x" + String(bar_2)  ); 
    }
    else if( bar_3 == bar_1  )
    {
        money += bar_3 * 5;
        ShowMsg( "Double! +$5x" + String(bar_3)  ); 
    }
    else
    {
        ShowMsg( "Miss!" ); 
    }
    

}
void HandleRoll()
{
    if( rolling )
    {
        int rend = 0;
        int show = 0;
        boolean c = false;
        if( roll_1 < rmax_1 )
        {
            switch( roll_1 )
            {
                case 0: c = ( tc_roll > ( 1 * tf_1 ) ); break;
                case 1: c = ( tc_roll > ( 2 * tf_1 ) ); break;
                case 2: c = ( tc_roll > ( 3 * tf_1 ) ); break;
                case 3: c = ( tc_roll > ( 4 * tf_1 ) ); break;
                case 4: c = ( tc_roll > ( 5 * tf_1 ) ); break;
                case 5: c = ( tc_roll > ( 6 * tf_1 ) ); break;
                case 6: c = ( tc_roll > ( 7 * tf_1 ) ); break;
                case 7: c = ( tc_roll > ( 8 * tf_1 ) ); break;
                case 8: c = ( tc_roll > ( 9 * tf_1 ) ); break;
                case 9: c = ( tc_roll > ( 10 * tf_1 ) ); break;
            }
            if( c )
            {
                bar_1 = (bar_1 % 7) + 1;
                ++roll_1;
                ++show;
            }
        }
        else ++rend;
        
        c = false;
        if( roll_2 < rmax_2 )
        {
            switch( roll_2 )
            {
                case 0: c = ( tc_roll > ( 1 * tf_2 ) ); break;
                case 1: c = ( tc_roll > ( 2 * tf_2 ) ); break;
                case 2: c = ( tc_roll > ( 3 * tf_2 ) ); break;
                case 3: c = ( tc_roll > ( 4 * tf_2 ) ); break;
                case 4: c = ( tc_roll > ( 5 * tf_2 ) ); break;
                case 5: c = ( tc_roll > ( 6 * tf_2 ) ); break;
                case 6: c = ( tc_roll > ( 7 * tf_2 ) ); break;
                case 7: c = ( tc_roll > ( 8 * tf_2 ) ); break;
                case 8: c = ( tc_roll > ( 9 * tf_2 ) ); break;
                case 9: c = ( tc_roll > ( 10 * tf_2 ) ); break;
            }
            if( c )
            {
                bar_2 = (bar_2 % 7) + 1;
                ++roll_2;
                ++show;
            }
        }
        else ++rend;
        
        c = false;
        if( roll_3 < rmax_3 )
        {
            switch( roll_3 )
            {
                case 0: c = ( tc_roll > ( 1 * tf_3 ) ); break;
                case 1: c = ( tc_roll > ( 2 * tf_3 ) ); break;
                case 2: c = ( tc_roll > ( 3 * tf_3 ) ); break;
                case 3: c = ( tc_roll > ( 4 * tf_3 ) ); break;
                case 4: c = ( tc_roll > ( 5 * tf_3 ) ); break;
                case 5: c = ( tc_roll > ( 6 * tf_3 ) ); break;
                case 6: c = ( tc_roll > ( 7 * tf_3 ) ); break;
                case 7: c = ( tc_roll > ( 8 * tf_3 ) ); break;
                case 8: c = ( tc_roll > ( 9 * tf_3 ) ); break;
                case 9: c = ( tc_roll > ( 10 * tf_3 ) ); break;
            }
            if( c )
            {
                bar_3 = (bar_3 % 7) + 1;
                ++roll_3;
                ++show;
            }
        }
        else ++rend;
        
        
        
        if( show > 0 ) ShowRoll();
        if( rend > 2 ) FinalizeRoll();
    }
}
void Roll()
{
    bar_1 = random( 1, 8 );
    bar_2 = random( 1, 8 );
    bar_3 = random( 1, 8 );
    roll_1 = 0;
    roll_2 = 0;
    roll_3 = 0;
    rmax_1 = random( 6, 11 );
    rmax_2 = random( 6, 11 );
    rmax_3 = random( 6, 11 );
    tf_1 = random( 150, 400 );
    tf_2 = random( 150, 400 );
    tf_3 = random( 150, 400 );
    
    --money;
    rolling = true;
    ShowMsg( "Rolling..." );
    tc_roll = 0;
}


void setup()
{
    randomSeed( analogRead(0) );
    
    lcd.begin( 16, 2 );
    pinMode(btn, INPUT);
    
    tp = 0;
    money_prev = 0;
    money = 100;
    
    ShowMsg( "Click to roll..." );
    ShowRoll();
}

void loop()
{
    HandleTime();
    HandleBtn();
    HandleRoll();
    ShowMoney();
    if( IsClicked() && !rolling ) Roll();
}