#include "headers.h"
#include "Helper_functions.h"
#include "Calculations.h"
#include "COM_functions.h"
#include "TCP_functions.h"

using namespace std;

 int main()
 {
////INICJALIZACJA PORTU COM
    if (COM_INIT())
        return 1;
////KONFIGURACJA PORTU COM
    if (COM_CONFIG()!=0)
        return 1;
////INICJALIZACJA POLACZENIA TCP - port 10001
    TCP_INIT();
////PLIK ZAW. WSPOLRZEDNE GEOGRAFICZNE
    fstream gcrds;
////ZMIENNE
    RAp = format(2,31,50.51); //WSPOLRZEDNE GWIAZDY POLARNEJ, POTRZEBNE DO BAZOWANIA 1
    DECp = format(89,15,51.4); //
    RA = 0;
    DEC = 0;
    double lat = deg2rad(LAT);
    double AZ_new, ALT_new;
    int  choice, ready;

////ROZPOCZECIE PROGRAMU
    cout<<" Oczekiwanie na sterownik..."<<endl;

    //oczekiwanie na sterownik
    do{ ready = ComRead(); }while(ready!=106);
        ComWrite("i"); cout<<" POLACZONO "<<endl; Sleep(1000);

    //oczekiwanie na polaczenie ze Stellarium
    cout<<" Oczekiwanie na Stellarium..."<<endl;
    if (TCP_CON()==true)
        {cout<<" POLACZONO"<<endl; Sleep(1000);}
    else
        {cout<<" Brak polaczenia ze Stellarium"<<endl; Sleep(1000);}
    //GLOWNA PETLA PROGRAMU
    do{


        //Odczyt wsp. geograficznych z pliku
        gcrds.open("geocoords.txt", ios::in);
        if (gcrds.good())
        {
        gcrds >> setprecision(10) >> LAT >> LON;
        }
        gcrds.close();
        //koniec odczytu


        lat = deg2rad(LAT); //zamiana szerokosci na radiany


        choice = 0;
        system("CLS");
        cout<<endl<<"  1. Bazowanie (gwiazda polarna) "
        <<endl<<"  2. Bazowanie (dowolna gwiazda) "
        <<endl<<"  3. Wyszukiwanie i sledzenie "
        <<endl<<"  4. Poziomowanie "
        <<endl<<"  5. Dane ostatniego obiektu, LST"
        <<endl<<"  6. Wspolrzedne geograficzne"
        <<endl<<"  0. Wyjscie"
        <<endl;
        choice = getch();
        if (choice == 49)//BAZOWANIE 1 - send "b"
        {
            system("CLS");
            ComWrite("b");
            cout<<"\n   BAZOWANIE"<<endl<<"   Skieruj teleskop na gwiazde polarna\n   i nacisnij ESC"<<endl;
            //PETLA BAZOWANIE: ESC - ZATWIERDZENIE/WYJSCIE
            do{

                if (GetKeyState(VK_LEFT) < 0)
                {
                    if(!CHECK_LEFT)
                    {
                        ComWrite("q");
                        cout<<"LEFT"<<endl;
                        CHECK_LEFT=TRUE;
                    }
                }
                else
                {
                    if (CHECK_LEFT)
                    {
                        ComWrite("a");
                        CHECK_LEFT=FALSE;
                    }
                }
                if (GetKeyState(VK_RIGHT) < 0)
                {
                    if(!CHECK_RIGHT)
                    {
                        ComWrite("w");
                        cout<<"RIGHT"<<endl;
                        CHECK_RIGHT=TRUE;
                    }

                }
                else
                {
                    if (CHECK_RIGHT)
                    {
                        ComWrite("s");
                        CHECK_RIGHT=FALSE;
                    }
                //system("CLS");
                }
                if (GetKeyState(VK_UP) < 0)
                {
                    if(!CHECK_UP)
                    {
                       ComWrite("e");
                        cout<<"UP"<<endl;
                        CHECK_UP=TRUE;
                    }

                }
                else
                {
                    if (CHECK_UP)
                    {
                        ComWrite("d");
                        CHECK_UP=FALSE;
                // system("CLS");
                    }
                }
                if (GetKeyState(VK_DOWN) < 0)
                {
                    if(!CHECK_DOWN)
                    {
                        ComWrite("r");
                        cout<<"DOWN"<<endl;
                        CHECK_DOWN=TRUE;
                    }

                }
                else
                {
                    if (CHECK_DOWN)
                    {
                        ComWrite("f");
                        CHECK_DOWN=FALSE;
                //system("CLS");
                    }
                }
                ////////////////////////
                //wolniej
                if (GetKeyState(VK_SUBTRACT) < 0)
                {
                        ComWrite("u");
                        cout<<"SLOWER"<<endl;
                        Sleep(1000);
                }
                //szybciej
                if (GetKeyState(VK_ADD) < 0)
                {
                        ComWrite("l");
                        cout<<"FASTER"<<endl;
                        Sleep(1000);
                }
                ////////////////////
                if (GetKeyState(VK_ESCAPE) < 0)
                {
                    ComWrite("x");
                    GetCoords(lat, LON, DECp, RAp, AZ_new, ALT_new);
                    ALT_old = ALT_new;
                    AZ_old = AZ_new;
                    break;
                }
                Sleep(1);
            }while(true);
        }
        if (choice == 50)//BAZOWANIE 2 - send "b"
        {
            system("CLS");
            ComWrite("b");
            cout<<"\n   BAZOWANIE"<<endl<<"   Przeslij dane dowolnej gwiazdy ze Stellarium\n   a nastepnie skieruj teleskop na te gwiazde"<<endl<<"\n   Oczekiwanie na dane ze Stellarium..."<<endl;
            TCP_readNewEQCoords(RA, DEC);
            cout<<"\n   Otrzymano wspolrzedne:\n   RA: "<<RA<<"\n   DEC: "<<DEC<<endl;
            cout<<"   Skieruj teleskop na wybrana gwiazde i nacisnij ESC"<<endl;
            //PETLA BAZOWANIE: ESC - ZATWIERDZENIE/WYJSCIE
            do{

                if (GetKeyState(VK_LEFT) < 0)
                {
                    if(!CHECK_LEFT)
                    {
                        ComWrite("q");
                        cout<<"LEFT"<<endl;
                        CHECK_LEFT=TRUE;
                    }
                }
                else
                {
                    if (CHECK_LEFT)
                    {
                        ComWrite("a");
                        CHECK_LEFT=FALSE;
                    }
                }
                if (GetKeyState(VK_RIGHT) < 0)
                {
                    if(!CHECK_RIGHT)
                    {
                        ComWrite("w");
                        cout<<"RIGHT"<<endl;
                        CHECK_RIGHT=TRUE;
                    }

                }
                else
                {
                    if (CHECK_RIGHT)
                    {
                        ComWrite("s");
                        CHECK_RIGHT=FALSE;
                    }
                //system("CLS");
                }
                if (GetKeyState(VK_UP) < 0)
                {
                    if(!CHECK_UP)
                    {
                       ComWrite("e");
                        cout<<"UP"<<endl;
                        CHECK_UP=TRUE;
                    }

                }
                else
                {
                    if (CHECK_UP)
                    {
                        ComWrite("d");
                        CHECK_UP=FALSE;
                // system("CLS");
                    }
                }
                if (GetKeyState(VK_DOWN) < 0)
                {
                    if(!CHECK_DOWN)
                    {
                        ComWrite("r");
                        cout<<"DOWN"<<endl;
                        CHECK_DOWN=TRUE;
                    }

                }
                else
                {
                    if (CHECK_DOWN)
                    {
                        ComWrite("f");
                        CHECK_DOWN=FALSE;
                //system("CLS");
                    }
                }
                 if (GetKeyState(VK_SUBTRACT) < 0)
                {
                        ComWrite("l");
                        cout<<"SLOWER"<<endl;
                        Sleep(1000);
                }
                //szybciej
                if (GetKeyState(VK_ADD) < 0)
                {
                        ComWrite("u");
                        cout<<"FASTER"<<endl;
                        Sleep(1000);
                }
                if (GetKeyState(VK_ESCAPE) < 0)
                {
                    ComWrite("x");
                    GetCoords(lat, LON, DEC, RA, AZ_new, ALT_new);
                    ALT_old = ALT_new;
                    cout<<"altold: "<<ALT_old<<endl;
                    AZ_old = AZ_new;
                    cout<<"azold: "<<AZ_old<<endl;
                    break;
                }
                Sleep(1);
            }while(true);
        }
        if (choice == 51)//AUTOMAT - send "c"
        {
            char degr = 176;
            ComWrite("c");
            system("cls");
            cout<<"\n   WYSZUKIWANIE I SLEDZENIE\n   Oczekiwanie na wspolrzedne ze Stellarium..."<<endl;
            TCP_readNewEQCoords(RA, DEC);
            cout<<"\n   Otrzymano wspolrzedne:\n   RA: "<<RA<<"\n   DEC: "<<DEC<<endl<<endl;
            do
            {
                GetCoords(lat, LON, DEC, RA, AZ_new, ALT_new);
                int sendAZ = GetAZSteps(AZ_new);

                if(sendAZ > 0)
                   {
                       if (sendAZ > 25600)
                       cout<<"AZ:  "<<(sendAZ-25600)*(-1)<<" ("<<((sendAZ-25600)*(-1))*0.0140625<<" st.)"<<endl;
                       else
                       cout<<"AZ:  "<<sendAZ<<" ("<<sendAZ*0.0140625<<" st.)"<<endl;
                       ComWrite("z");
                       ComWriteInt(sendAZ);
                    if (motorDone() == true)
                      ;
                   }
                GetCoords(lat, LON, DEC, RA, AZ_new, ALT_new);
                int sendALT = GetALTSteps(ALT_new);


                   if(sendALT > 0)
                   {
                       if (sendALT > 25600)
                       cout<<"ALT: "<<(sendALT-25600)*(-1)<<" ("<<((sendALT-25600)*(-1))*0.0140625<<" st.)"<<endl;
                       else
                       cout<<"ALT: "<<sendALT<<" ("<<sendALT*0.0140625<<" st.)"<<endl;
                       ComWrite("t");
                       ComWriteInt(sendALT);
                    if (motorDone() == true)
                       ;

                   }
                   if (GetKeyState(VK_ESCAPE) < 0)
                    {
                       ComWrite("x");
                       break;
                    }
           // Sleep(500);
            }while(true);
        }
        if (choice == 52)//POZIOMOWANIE - send "p" odbiera "112" gdy wypoziomowano
        {
            system("cls");
          ComWrite("p");
          cout<<"\n   Poziomowanie teleskopu\n   Jezeli dzwiek z buzzera ustal oznacza to, \n   ze teleskop jest wypoziomowany"<<endl;
          do{
            Sleep(1);
            } while(ComRead()!=112);
            cout<<"\n   Poziomowanie zakonczone"<<endl;
            Sleep(1000);
        }
        if (choice == 53)//PODGLAD
        {
            do
            {
                system("CLS");
                GetCoords(lat, LON, DEC, RA, AZ_new, ALT_new);
                cout<<"\n   Wspolrzedne ostatnio obserwowanego obiektu:\n\n   Rownikowe\n   RA: "<<RA<<endl<<"   DEC: "<<DEC<<endl;
                cout<<"\n   Horyzontalne"<<endl<<"   ALT: "<<ALT_new<<"\n   AZ: "<<AZ_new<<endl<<endl;
                showLST();
                Sleep(50);
                if (GetKeyState(VK_ESCAPE) < 0)
                    break;
            }while(true);
        }
        if (choice == 54)
        {
            system("cls");
            cout<<"\n   Wspolrzedne geograficzne\n\n   Aktualne wspolrzedne:\n     Szerokosc geograficzna: "<<LAT<<"\n     Dlugosc geograficzna: "<<LON<<"\n\n   ENTER by zmienic\n   ESC by wyjsc"<<endl;
            int key = getch();
            if (key == 13)
            {
                gcrds.open("geocoords.txt", ios::out | ios::trunc);

                double lat_new, lon_new;
                cout<<"\n   Podaj nowe wspolrzedne\n     Szerokosc geograficzna: "; cin>>lat_new; cout<<"     Dlugosc geograficzna: "; cin>>lon_new;
                if (gcrds.good())
                {
                    gcrds << setprecision(10) << lat_new << endl << lon_new;
                }
                gcrds.close();
            }
            if (key == 27)
                ;
        }
        if (choice == 48)
        {
            closesocket( mainSocket );
            CloseHandle( hCom );
            break;
        }
   }while(true);
   //koniec glownej petli

}





