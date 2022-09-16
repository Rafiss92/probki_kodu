function suma_pola = pole_figury_f(X,Y,Z)
% Funkcja tworzy struktury a,b,c,d i przypisuje do nich odpowiednie punkty w przestrzeni z macierzy X, Y i Z.
% Funkcja zwraca zmienna suma_pola, co jest koncowym wynikiem obliczen.
a=struct;
b=struct;
c=struct;
d=struct;

   suma_pola = 0.0;
    for i = 1:19
       for j=1:19
           a.x=X(i); a.y=Y(j); a.z=Z(i,j);
           b.x=X(i + 1); b.y=Y(j); b.z=Z(i + 1,j);
           c.x=X(i); c.y=Y(j + 1); c.z=Z(i,j + 1);
           d.x=X(i + 1); d.y=Y(j + 1); d.z=Z(i + 1, j + 1);
           suma_pola += pole(a,b,c,d);
       endfor
    endfor
endfunction