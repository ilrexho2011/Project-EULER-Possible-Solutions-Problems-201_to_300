#include <iostream>
using namespace std;

typedef long long Int;

template <int N> struct Count
{
   static Int const a= Count<N-1>::a + Count<N-1>::b + 1;
   static Int const b= Count<N-1>::a + Count<N-1>::b + 1;
   static Int const nb_steps= 1 + a;
};

template <> struct Count<0>
{
   static Int const a= 0;
   static Int const b= 0;
   static Int const nb_steps= 1;
};





static Int const dx[]= { 0, 1, 0, -1 };
static Int const dy[]= { 1, 0, -1, 0 };

struct Position
{
   Int x, y;
   Position() : x(0), y(0), angle(0) {}

   int angle; // 0=North, 1=E, 2=S, 3=W 

   Position F() const
     {
      Position p (*this);
      p.x+= dx[angle];
      p.y+= dy[angle];
      return p;
     }

   Position Turn (int n) const
     {
      Position p (*this);
      p.angle= (p.angle+4+n) % 4;
      return p;
     }

   Position L() const
     {
      return Turn (-1);
     }

   Position R() const
     {
      return Turn (1);
     }

   Position Add (Position const& src) const
     {
      Position p (*this);
      switch (angle)
        {
         case 0: p.x+= src.x; p.y+= src.y; break;
         case 1: p.x+= src.y; p.y-= src.x; break;
         case 2: p.x-= src.x; p.y-= src.y; break;
         case 3: p.x-= src.y; p.y+= src.x; break;
        }
      p.angle= (angle+src.angle)%4;
      return p;
     }
};

template <int N> struct Advance
{
   static Position a()
     {
      static Position const result= Advance<N-1>::a().R().Add(Advance<N-1>::b()).F().R();
      return result;
     }

   static Position b()
     {
      static Position const result= Position().L().F().Add(Advance<N-1>::a()).L().Add(Advance<N-1>::b());
      return result;
     }
};




template <> struct Advance<0>
{
   static Position a() { static Position const result; return result; }
   static Position b() { static Position const result; return result; }
};

template <int N> Position GetPos()
{
   static Position const result= Position().F().Add(Advance<N>::a());
   return result;
}


template <int N> struct Advance2
{
   static Position a (Int nb_steps)
     {
      Position result;
      Do_a (nb_steps, result); if (nb_steps <= 0) return result;
      Do_R (nb_steps, result); if (nb_steps <= 0) return result;
      Do_b (nb_steps, result); if (nb_steps <= 0) return result;
      Do_F (nb_steps, result); if (nb_steps <= 0) return result;
      Do_R (nb_steps, result); if (nb_steps <= 0) return result;
      return result;
     }

   static Position b (Int nb_steps)
     {
      Position result;
      Do_L (nb_steps, result); if (nb_steps <= 0) return result;
      Do_F (nb_steps, result); if (nb_steps <= 0) return result;
      Do_a (nb_steps, result); if (nb_steps <= 0) return result;
      Do_L (nb_steps, result); if (nb_steps <= 0) return result;
      Do_b (nb_steps, result); if (nb_steps <= 0) return result;
      return result;
     }

   static void Do_L (Int& nb_steps, Position& pos)
     {
      pos= pos.L();
     }

   static void Do_R (Int& nb_steps, Position& pos)
     {
      pos= pos.R();
     }

   static void Do_F (Int& nb_steps, Position& pos)
     {
      pos= pos.F();
      --nb_steps;
     }

   static void Do_a (Int& nb_steps, Position& pos)
     {
      if (Count<N-1>::a <= nb_steps)
        {
         pos= pos.Add (Advance<N-1>::a());
         nb_steps-= Count<N-1>::a;
        }
      else
        {
         pos= pos.Add (Advance2<N-1>::a(nb_steps));
         nb_steps= 0;
        }
     }

   static void Do_b (Int& nb_steps, Position& pos)
     {
      if (Count<N-1>::b <= nb_steps)
        {
         pos= pos.Add (Advance<N-1>::b());
         nb_steps-= Count<N-1>::b;
        }
      else
        {
         pos= pos.Add (Advance2<N-1>::b(nb_steps));
         nb_steps= 0;
        }
     }
};

template <> struct Advance2<0>
{
   static Position a (Int) { static Position const result; return result; }
   static Position b (Int) { static Position const result; return result; }
};

template <int N> Position GetPos2 (Int nb_steps)
{
   Position result= Position();
   result= result.F(); nb_steps--;
   Position const a_= Advance2<N>::a(nb_steps);
   result= result.Add (a_);
   return result;
}


ostream& operator << (ostream& os, Position const& p)
{
   return os << "(" << p.x <<"," << p.y << ", " <<p.angle<<")";
}

int main()
{
   Position const p= GetPos2<50>(1000000000000L); cout << p << "\n"; return 1;
}