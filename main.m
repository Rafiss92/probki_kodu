clear; % Czyszczenie
A = dlmread('dane.dat', '	'); % Odczyt wspolrzednych z pliku dat

format long; % Zmiana formatu wyswietlanych wynikow
% Tworzenie macierzy X i Y

for i=1:20
  X(i)=Y(i)=A(i,2);
endfor

% Tworzenie macierzy Z

k=1;
h=1;
for i=1:rows(A)
  Z(k,h)=A(i,3);
  k+=1;
  if (k==21)
    k=1;
    h+=1;
  endif
endfor

clear A i k h; % Czyszczenie niepotrzebnej macierzy A oraz zmiennych i, k, h
srednia=srednia_f(Z,1);
mediana=mediana_f(Z,1);
odchylenie=odchylenie_f(Z,1);

[a,b]=max(odchylenie(:,2));

printf("Maksymalne odchylenie standardowe to %f i zachodzi w %d linijce\n",a,b);
printf("\n")

Z11=Z(:,b); % 11 linijka z osi Z

function wykresy_f(X,Y,Z,Z11,b)
  figure(1); % Numer wykresu
    contourf(X,trans(Y),Z); % Linijka odpowiada za rysowanie mapy
    title("Wizualizacja danych w formie mapy 2D, kolory dla wspolrzednej Z");
    xlabel("X"); % Etykieta osi X
    ylabel("Y"); % Etykieta osi Y
    colorbar; % Wyswietlanie paska kolorow (legenda)
    colormap('hot'); % Schemat kolorow
  figure(2); % Numer wykresu
    surf(X,Y,Z); % Funkcja rysujaca wykres powierzchni oparty na prostokatach
    title("Wizualizacja danych w formie powierzchni 3D");
    colorbar; % Wyswietlanie paska kolorow (legenda)
    xlabel("X"); % Etykieta osi X
    ylabel("Y"); % Etykieta osi Y
    zlabel("Z"); % Etykieta osi Z
    %view(90, 90) - nachylenie pod kątem 90 stopni - opcjonalne
    colormap('hot'); % Schemat kolorow
  figure(3); % Numer wykresu
    plot(Y,Z11,"xr"); % Funkcja rysujaca wykres punktow na podstawie macierzy Z11
    title(["Wybrane punkty z wiersza nr 11. Kryterium: Najwieksze odchylenie standardowe"])
    xlabel("X"); % Etykieta osi X
    ylabel("Z"); % Etykieta osi Z
    grid on; % Wlaczenie wyswietlania siatki
  figure(4);
    aproksymacja_kwadraty_f(Y,trans(Z11),1,1000);
  figure(5);
    czebyszew_interpolacja_f(Y,Z11,Z11);
endfunction

wykresy_f(X,Y,Z,Z11,b);                                                                                                                  

printf("\nPole powierzchni figury wynosi: %f\n", pole_figury_f(X,Y,Z));

disp("\nFunkcja pochodna_f tworzy macierze px i py, ktore stanowia dane na temat pochodnych\n");
[px, py]=pochodna_f(X,Y,Z,1); % Funkcja z opcja rysowania wykresu
disp("Pochodne obliczone, trwa liczenie calek!\n");

  % CALKA Z FUNKCJI INTERPOLACYJNEJ
    
    disp("\nUwaga! Obliczenia calek moga potrwac dosc dlugo!\n");
    
    fint=@(x) -385.248401 + 1264.712918 * T(1,x) + 391.805022 * T(2,x) + 962.990052 * T(3,x) + 207.472274 * T(4,x) + 436.817607 * T(5,x) + 5.486572 * T(6,x) + -85.105376 * T(7,x) + -103.362661 * T(8,x) + -448.016539 * T(9,x) + -163.581109 * T(10,x) + -725.923176 * T(11,x) + -361.818278 * T(12,x) + -946.060691 * T(13,x) + -473.292253 * T(14,x) +-572.605004 * T(15,x) + -68.637964 * T(16,x) + -232.008415 * T(17,x) + -97.123200 * T(18,x) + -97.101373 * T(19,x);

    tic(); printf("\nCalka z funkcji interpolacyjnej dla 100 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 100,fint)); toc
    tic(); printf("\nCalka z funkcji interpolacyjnej dla 250 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 250,fint)); toc
    tic(); printf("\nCalka z funkcji interpolacyjnej dla 400 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 400,fint)); toc
    tic(); printf("\nCalka z funkcji interpolacyjnej dla 1000 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 1000,fint)); toc
    tic(); printf("\nSprawdzenie funkcja wbudowana Octave: %f\n", quad(fint,Y(1,1),Y(1,20))); toc

  % CALKA Z FUNKCJI APROKSYMACYJNEJ

    fapr=@(x) -245.909147 * x^1 + -532.8569321;

    tic(); printf("\nCalka z funkcji aproksymacyjnej dla 100 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 100,fapr)); toc
    tic(); printf("\nCalka z funkcji aproksymacyjnej dla 250 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 250,fapr)); toc
    tic(); printf("\nCalka z funkcji aproksymacyjnej dla 400 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 400,fapr)); toc
    tic(); printf("\nCalka z funkcji aproksymacyjnej dla 1000 podzialow: %f \n",calka_f(Y(1,1), Y(1,20), 1000,fapr)); toc
    tic(); printf("\nSprawdzenie funkcja wbudowana Octave: %f\n", quad(fapr,Y(1,1),Y(1,20))); toc

    clear fapr fint
    disp("\nKoniec dzialania programu. Uzyskane dane w toku obliczania sa widoczne w Octave w polu zmiennych.\n");
