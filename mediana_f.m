function med = mediana_f(Z,wys=0)
  %Funkcja obliczajaca mediane z danych liczb
    med=zeros(columns(Z),1);
    Zm=sort(Z);
    for i=1:columns(Z)
      if(mod(columns(Z),2)==0)
        med(i,1)=(Zm((columns(Z)/2),i)+Zm(((columns(Z)/2)+1),i))/2;
      else
        med(i,1)=Zm((columns(Z)/2),i);
      endif
      if(wys==1)
        printf("Wiersz X nr: %d - mediana: %f\n",i, med(i));
      endif
    endfor
      if(wys==1)
        printf("\n");
      endif
endfunction