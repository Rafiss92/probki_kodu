function A_ap=aproksymacja_kwadraty_f(x_ap,y_ap,n,linijka,zaok=100)
  % x_ap - macierz wejsciowa Y
  % y_ap - macierz wejsciowa Z
  % n - stopien wielomianu aproksymacyjnego
  % linijka - numer analizowanej linijki
  % zaok - domyslnie 100, zmienna mowiaca o liczbie punktow generowanych dla plynnego wykresu
  
  if length(x_ap)==length(y_ap)
  %ustalamy stopien wielomianu aproksymacyjnego
  stopien=n;
  n=length(x_ap);

  X_ap=zeros(stopien+1,stopien+1);
  A_ap=zeros(stopien+1,1);
  Y_ap=zeros(stopien+1,1);

  %obliczanie macierzy X
  for i=1:stopien+1
    for j=1:stopien+1
      for k=1:n
        %algorytm ustalajacy wartosci macierzy X
        X_ap(i,j)+=x_ap(1,k)^(i+(j-2));
      end
    end
  end

  %obliczanie macierzy Y
  for i=1:stopien+1
    for k=1:n
      Y_ap(i,1)+=y_ap(1,k)*x_ap(1,k)^(i-1);
    end
  end
  
  A_ap=il_macierzy(gaussinv(X_ap),Y_ap);
  
  %obliczanie wartosci funkcji na podstawie obliczonych wartosci wspolczynnikow wielomianu
  yi_ap=zeros(1,n);

  for i=1:n
    for j=1:stopien+1
      yi_ap(1,i)+=A_ap(j,1)*x_ap(i)^(j-1);
    endfor
  endfor
  
  disp("Wielomian aproksymacyjny: ");
  j_ap=stopien+1;
  for i=1:stopien
    j_ap--;
    printf("%f * x^%d + ",A_ap(j_ap+1),j_ap)
  endfor
  printf("%f\n",A_ap(j_ap))
  
  %"plynny wykres"
    step=(max(x_ap)-min(x_ap))/zaok;
    Ry_ap=zeros(1,zaok+1);
    Rx_ap=zeros(1,zaok+1);
    %obliczanie wartosci funkcji Ry na podstawie ustalonych wspolczynnikow wielomianu
    for i=1:zaok+1
      Rx_ap(1,i)=min(x_ap)+(i-1)*step;
      for j=1:stopien+1
         Ry_ap(1,i)=Ry_ap(1,i)+A_ap(j)*Rx_ap(1,i)^(j-1);
      endfor
  endfor

    tytul_rys=sprintf("Aproksymacja metoda najmniejszych kwadratow stopnia %d linijka %d", stopien, linijka);
    plot(Rx_ap, Ry_ap,'--r');
    hold on;
    plot(x_ap, y_ap,'xb');
    title(tytul_rys);
    
    grid on;
    xlabel("Y");
    ylabel("Z");
    
  else
    disp("Liczba wspolrzednych x nie jest rowna liczbie wspolrzednych y");
  end
endfunction
