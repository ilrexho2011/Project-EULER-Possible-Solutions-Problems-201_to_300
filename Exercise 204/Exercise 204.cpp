#include <iostream>
using namespace std ;

#define HAMMING_TYPE 100
#define IloscPreDoHT 25

int tab[25] = { 
       2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
       31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
       73, 79, 83, 89, 97
       } ;
       
   bool dziel(int L)
   {
    bool Hamming_number = true ;
    int temp ;
    
     while(L > HAMMING_TYPE && Hamming_number)
     {
      int i = 0 ;
      temp = L ;
      
      for( ; i < IloscPreDoHT ; i++)
      {
        if(L%tab[i]==0)
        {
        L/=tab[i] ;  
        i = 0 ;       
        }     
      }
      
      if(temp==L)
      Hamming_number = false ;        
      }
     
     if(L<=HAMMING_TYPE) return true ; 
     else return false ;
     
   }

int main()
{ 
   
   int temp=0, miliard = 1000*1000*1000 ;
   int ilosc=HAMMING_TYPE ; 
   
   for(int i = HAMMING_TYPE ; i < miliard ; i++)
   {
     temp = i ;
     if(dziel(temp)) ilosc++ ;
   }

cout << ilosc ;

return 0 ;  
}