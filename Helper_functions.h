double deg2rad(double deg)
{
    return deg *( M_PI / 180 );
}
double rad2deg(double rad)
{
    return rad * ( 180 / M_PI );
}
double format(double x1, double x2, double x3)
{
    if (x1<0)
    {
        return x1-(x2/60)-(x3/3600);
    }
    else
        return x1+(x2/60)+(x3/3600);
}

std::string int2str(int i)
{
    std::stringstream ss;
    std::string temp;
    ss << i;
    ss >> temp;
    return temp;
}

std::string double2str(double dbl) //nieuzywane
{
std::ostringstream strs;
strs <<std::setprecision(10)<<dbl;
std::string str = strs.str();
return str;
}

double getFract(double num)
{
    if (num < 0)
        return abs(num)-abs(ceil(num));
    else
        return num-floor(num);
}


