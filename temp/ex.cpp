#include <iostream>
 
using namespace std;
 
class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line(double len); 
 
   private:
      double length;
};
 

#if 0
Line::Line( double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
 
#endif

Line::Line( double len):length(len)
{
    cout << "Object is being created, length = " << len << endl;
}
 


void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}



int main( )
{
   Line line(10.0);
 
   cout << "Length of line : " << line.getLength() <<endl;
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   return 0;
}
