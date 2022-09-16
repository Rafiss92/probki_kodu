function [PoX, PoY] = pochodna_f(X,Y,Z,wykres=0)
  %Funkcja obliczajaca pochodna
  % Funkcja przyjmuje macierze X,Y,Z oraz zmienna wykres
  % Jesli zmienna wykres bedzie rowna 1 to skrypt rysuje wykres
  PoX = zeros(20);
  PoY = zeros(20);
  
  for i=1:20
    PoX(1,i)=(Z(2,i)-Z(1,i))/(X(2)-X(1));
    PoX(20,i)=(Z(20,i)-Z(19,i))/(X(20)-X(19));
    PoY(i,1)=(Z(i,2)-Z(i,1))/(Y(2)-Y(1));
    PoY(i,20)=(Z(i,20)-Z(i,19))/(Y(20)-Y(19));
    for j=2:19
      PoX(j,i)=((Z(i,j+1)-Z(i,j-1))/(X(j+1)-X(j-1)));
      PoY(i,j)=((Z(j+1,i)-Z(j-1,i))/(Y(j+1)-Y(j-1)));
    endfor
  endfor
  if(wykres==1)
    figure()
    contourf(X,Y,PoY); % Wykres pochodnej P
    title("Pochodna po X")
    xlabel("Y");
    ylabel("X");
    colormap('hot');
    colorbar
    figure()
    contourf(X,Y,PoX); % Wykres pochodnej P
    title("Pochodna po Y")
    colormap('hot');
    xlabel("X");
    ylabel("Y");
    colorbar
  endif
endfunction
