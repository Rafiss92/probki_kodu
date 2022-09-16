function [srednia]=srednia_f(Z,wys=0)
  %Funkcja obliczajaca srednia z podanych liczb
  srednia=zeros(rows(Z),1);
    for j=1:columns(Z)
      suma=0;
      for i=1:rows(Z)
        suma+=Z(i,j);
      endfor
    srednia(j)=suma/rows(Z);
      if(wys==1)
        printf("Wiersz X nr: %d - średnia arytmetyczna: %f\n",j, srednia(j));
      endif
    endfor
     if(wys==1)
        printf("\n");
      endif
endfunction