function calka = calka_f(a,b,n,fz)
% Calkowanie metoda trapezow
% a, b - przedzial
% n - liczba podzialow
% fz - funkcja anonimowa

% Funkcja zwraca zmienna calka

  suma=0;
  h=(b-a)/n;
  x=zeros(n,1);
  y=zeros(n,1);
  calka=0;
  for i=1:n
    x(i,1)=a+i*h;
    y(i,1)=fz(x(i,1));
  endfor
    
  suma=((y(1,1)+y(n,1))/2);
  
  for i=1:n-1
     suma+=fz(x(i,1));
  endfor
  calka=h*suma;
endfunction
