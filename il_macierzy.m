function PROD = il_macierzy (X,Y,z=1)
  
  %Program obliczeniowy iloczynu dwoch macierzy
  [l_wieX,l_kolX]=size(X);
  [l_wieY,l_kolY]=size(Y);
    if l_kolX == l_wieY % Sprawdzam warunek mnozenia macierzy
      PROD=zeros(l_wieX,l_kolY); % Wypelniam macierz PROD zerami
        for i=1:l_wieX
          for j=1:l_kolY
            suma=0; % Zmienna pomocnicza do mnozenia macierzy
            for k=1:l_kolX
              suma=suma+X(i,k)*Y(k,j); 
            endfor
            PROD(i,j)=suma; % Przypisanie wartosci zmiennej suma do odpowiedniego elementu macierzy
          endfor
        endfor
    
    [l_wierszy_PROD,l_kolumn_PROD]=size(PROD); % Okreslenie rozmiaru macierzy PROD po mnozeniu
    if(z!=1)
      for i=1:l_wierszy_PROD
        for j=1:l_kolumn_PROD
          PROD(i,j)=PROD(i,j)*z; % Mnozenie macierzy PROD przez stala
        endfor
      endfor
    endif
    else 
      disp("Macierze nie spelniaja warunkow do mnozenia!");
    endif
endfunction