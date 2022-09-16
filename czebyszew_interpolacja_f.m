function czebyszew_interpolacja_f(X,Y,Z11)
% X - macierz dla osi X
% Y - macierz dla osi Z
% Z11 - macierz dla punktow Z na wykresie (nie uczestniczy w obliczeniach

Y=trans(Z11); % Transponowanie macierzy Y
Xi=zeros(size(X)); % Zerowanie macierzy Xi

for i=1:columns(X)
  Xi(i)=(X(i)-0.5)/0.5; % Normalizacja wspolrzednych X
endfor

W=zeros(columns(X)); % Macierz W wspolczynnikow

for i=1:columns(X)
  for j=1:columns(X)
    W(i,j)=T(j-1,Xi(i)); % Wypelnianie macierzy wspolczynnikow odpowiednimi danymi
  endfor
endfor

CZEBY=gaussinv(W)*trans(Y); % Rozwiazywanie rownania za pomoca funkcji gaussinv oraz trans

printf("Wielomian interpolacyjny Czebyszewa: \n"); % Linijki wypisujace na ekran wielomian interpolacyjny
printf("%f + " ,CZEBY(1,1));
for i = 1:columns(X)-2
  printf("%f * T(%d,x) + ", CZEBY(i+1,1),i);
endfor
printf("%f * T(%d,x)\n",CZEBY(columns(X),1),columns(X)-1);

wielomian = CZEBY(1,1);
for i=1:columns(X)-1
   wielomian+=CZEBY(i+1,1) * T(i,Xi);
   cze(i)=CZEBY(i+1,1);
   wsp=T(i,Xi);
endfor
% Czesc graficzna
plot(Xi,wielomian);
title("Interpolacja Czebyszewa")
hold on;
grid on;
xlabel("Y znormalizowane");
ylabel("Z11");
plot(Xi,Z11,"og");

endfunction
