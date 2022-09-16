function S = odchylenie_f(Z,wys=0)
  %Funkcja obliczajaca odchylenie standardowe
    SR=srednia_f(Z);
    [w,k] = size(Z);
    S=zeros(k,2);
  for i=1:k
    suma=0;
    for j=1:w
     suma=suma+((Z(j,i)-SR(i,1))^2);
    endfor
  S(i,1) = (suma/w);
  S(i,2) = sqrt(suma/w);
      if(wys==1)
        printf("Wiersz X nr: %d - odchylenie standardowe: %f\n",i, S(i,2));
      endif
  endfor
       if(wys==1)
        printf("\n");
      endif
endfunction