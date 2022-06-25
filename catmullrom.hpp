#pragma once

template<class T>
struct Point
{
    T x;
    T y;
    Point(T a, T b) { x = a;  y = b; }
    Point() {}

    Point operator+(Point v)
    {
        Point r;
        r.x = this->x + v.x;
        r.y = this->y + v.y;
        return r;
    }
    Point operator-(Point v)
    {
        Point r;
        r.x = this->x - v.x;
        r.y = this->y - v.y;
        return r;
    }
    Point operator+(T value)
    {
        Point r;
        r.x = this->x + value;
        r.y = this->y + value;
        return r;
    }
    Point operator-(T value)
    {
        Point r;
        r.x = this->x - value;
        r.y = this->y - value;
        return r;
    }
    Point operator*(T value)
    {
        Point r;
        r.x = this->x * value;
        r.y = this->y * value;
        return r;
    }
    Point operator/(T value)
    {
        Point r;
        r.x = this->x / value;
        r.y = this->y / value;
        return r;
    }
    template<class X, class Y>
    Point operator()(const X& x, const Y& y)
    { 
        this->x = x;
        this->y = y;
        return *this;
    }
};

inline Point<float> operator*(float value, Point<float> v)
{
    return v * value;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class catmullrom
{
    public:
        Point<float>* p;
        Point<float>* v;
        const int points;
        bool smooth;

        catmullrom(const int segments, bool smooth = true): points(segments)
        {
            this->smooth = smooth;
            p = new Point<float>[points];
            v = new Point<float>[points];
        }
       ~catmullrom()
        {
            delete v;
            delete p;
        }


    Point<float> getft(float time)
    {
        Point<float> ret;
        int n = points-1;
        int i = (int)time;
        float t = time - i;
        if(i == n)
        {
            ret = (2*p[i]-2*p[0]+v[i]+v[0])*t*t*t
                + (-3*p[i]+3*p[0]-2*v[i]-v[0])*t*t
                + v[i]*t
                + p[i];
        }
        else
        {
            ret = (2*p[i]-2*p[i+1]+v[i]+v[i+1])*t*t*t
                + (-3*p[i]+3*p[i+1]-2*v[i]-v[i+1])*t*t
                + v[i]*t
                + p[i];
        }
        return ret;
    }

    void calcv()
    {
        Point<float> temp;
        if(smooth)
        {
            temp = (p[1]-p[points-2])/2;
            v[0] = temp;
            for(int i = 1;i < points-1;i++)
            {
                temp = (p[i+1]-p[i-1])/2;
                v[i] = temp;
            }
            temp = (p[0]-p[points-2])/2;
            v[points-1] = temp;
        }
        else
        {
            temp = (p[1]-p[0])*2-(p[2]-p[0])/2;
            v[0] = temp;
            for(int i = 1; i < points-1; i++)
            {
                temp = (p[i+1]-p[i-1])/2;
                v[i] = temp;
            }
            temp = (p[points-1]-p[points-2])*2-(p[points-1]-p[points-2])/2;
            v[points-1] = temp;
        }
    }
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
