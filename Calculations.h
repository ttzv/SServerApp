


double LST(double longtitude)
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    double seconds = (ms.count()/1000.0) - 946728000;
    double D = seconds / (24.0*3600.0);
    double GMST = 18.697374558 + 24.06570982441908 * D;
    return fmod(GMST, 24) + longtitude/15;
}

void showLST()
{
 double LSTdb = LST(LON);int LSTh = LSTdb;

 double LSTdbm = (LSTdb - LSTh)*60.0;int LSTm = LSTdbm;

 double LSTdbs = (LSTdbm - LSTm)*60.0;int LSTs = LSTdbs;


 std::cout<<"   LST: "<<LSTh<<":"<<LSTm<<":"<<LSTs<<std::endl;
}

void GetCoords(double lat,
               double LON,
               double DEC,
               double RA,
               double &direction,
               double &angle2)
{

    double dec = deg2rad(DEC);
    double ha = deg2rad((LST(LON) - RA) * 15);
    double A = (sin(lat) * sin(dec)) + (cos(lat) * cos(dec) * cos(ha));
    double B = (cos(lat) * sin(dec)) - (sin(lat) * cos(dec) * cos(ha));
    double C = - (cos(dec) * sin(ha));

    double radius1 = sqrt(pow(B,2.0)+pow(C,2.0));
    double angle1 = rad2deg(atan2(C,B));

    direction = fmod((angle1 + 360),360); //AZ

    double radius2 = sqrt(pow(radius1,2.0)+pow(A,2.0));

    angle2 = rad2deg(atan2(A,radius1)); //ALT
}

int GetALTSteps(double ALT_new)
{
    double ALTdiff,
           StepRes = 0.0140625,
           ALTf,
           ALTSteps;

    int ALTSteps_out=0;

  ALTdiff = ALT_new - ALT_old;
//std::cout<<"altdiff: "<<ALTdiff<<std::endl;
       if (fabs(ALTdiff)>=StepRes)
       {
           ALTSteps = fabs(ALTdiff)/StepRes;
           ALTf = getFract(ALTSteps);
           if (ALTf < 0.5)
                ALTSteps = floor(ALTSteps);
           if (ALTf >= 0.5)
                ALTSteps = ceil(ALTSteps);
           if (ALTdiff < 0)
           ALTSteps_out = ALTSteps + 25600;
           else ALTSteps_out = ALTSteps;

           ALT_old = ALT_new;

           return ALTSteps_out;
       }
    return ALTSteps_out;
}

int GetAZSteps(double AZ_new)
{
    double AZdiff,
           StepRes = 0.0140625,
           AZf,
           AZSteps;
    int AZSteps_out=0;

        AZdiff = AZ_new - AZ_old;

        if(fabs(AZdiff)>= 180.0) //jak najkrocej
            {
            if(AZdiff<0)
                AZdiff+=360.0;
            else
                AZdiff-=360.0;
            }
//std::cout<<"azdiff: "<<fabs(AZdiff)<<std::endl;
       if (fabs(AZdiff)>=StepRes)
       {
           AZSteps = fabs(AZdiff)/StepRes;
           AZf = getFract(AZSteps);
           if (AZf < 0.5)
                AZSteps = floor(AZSteps);
           if (AZf >= 0.5)
                AZSteps = ceil(AZSteps);
           if (AZdiff < 0)
                AZSteps_out = AZSteps + 25600;
           else AZSteps_out = AZSteps;

           AZ_old = AZ_new;

           return AZSteps_out;
       }
    return AZSteps_out;
}
