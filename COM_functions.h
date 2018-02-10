
int no_readBYTES = 1;
int no_sendBYTES = 1;


HANDLE hCom;
const char *pcCommPort = TEXT("COM3");
DCB dcb;

int helptabR[1]={0};
int helptabW[1]={0};


int COM_INIT()
{
     hCom = CreateFile(  pcCommPort,
                        GENERIC_WRITE|GENERIC_READ,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

    if (hCom == INVALID_HANDLE_VALUE)
    {
        std:: cout<<"CreateFile failed with error: "<<GetLastError()<<std::endl;
        return (1); //error opening handle
    }
    return 0; //success
}

int COM_CONFIG()
{
  ZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);

   bool fSuccess = GetCommState(hCom, &dcb);

   if (!fSuccess)
   {
       std:: cout<<"GetCommState failed with error: "<<GetLastError()<<std::endl;
      return (2); //error reading
   }

    dcb.BaudRate = CBR_9600;      //  baud rate
    dcb.ByteSize = 8;             //  data size
    dcb.Parity   = NOPARITY;      //  parity bit
    dcb.StopBits = ONESTOPBIT;    //  stop bit

   fSuccess = SetCommState(hCom, &dcb);

   if (!fSuccess)
    {
        std:: cout<<"SetCommState failed with error: "<<GetLastError()<<std::endl;
      return (3); //error writing
    }
   return 0;
}




void ComWriteInt(int input)
{

    std::string send = int2str(input);
    char *Data=&send[0];
    //cout<<"wysyla:"<<Data<<endl;
    no_sendBYTES = strlen (Data);
  bool okw = WriteFile( hCom,
                Data,
                no_sendBYTES,
                NULL,
                NULL);
            if(!okw)
               std:: cout<<"write failed with error.\n"<<GetLastError()<<std::endl;
}

void ComWrite(std::string input)
{


    char *Data=&input[0];
    //cout<<"wysyla:"<<Data<<endl;
    bool okw = WriteFile( hCom,
                Data,
                1,
                NULL,
                NULL);
            if(!okw)
               std:: cout<<"write failed with error.\n"<<GetLastError()<<std::endl;
}

int ComRead()
{
helptabR[0] = 0;
int *Data=helptabR;
bool okr = ReadFile( hCom,
                    Data,
                    no_readBYTES,
                    NULL,
                    NULL);
if(!okr)
    std::cout<<"read failed with error.\n"<<GetLastError()<<std::endl;
    return helptabR[0];
}

bool motorDone()
{
    int r = 0;
    do
    {
        r = ComRead();
        if (GetKeyState(VK_ESCAPE) < 0)
            break;
    }while(r!=107);
return true;
}

