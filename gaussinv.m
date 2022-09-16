function b = gaussinv(a)
%Funkcja odwracania macierzy metoda Gaussa
  [r,c] = size(a);  

  if r ~= c
      disp("Blad odwracania macierzy, dozwolone tylko macierze kwadratowe!");
      b = [];
      return
  endif

  b = eye(r);

  for j = 1 : r
      for i = j : r
          if a(i,j) ~= 0
              for k = 1 : r
                  s = a(j,k); 
                  a(j,k) = a(i,k); 
                  a(i,k) = s;
                  s = b(j,k); 
                  b(j,k) = b(i,k); 
                  b(i,k) = s;
              endfor
              t = 1/a(j,j);
              for k = 1 : r
                  a(j,k) = t * a(j,k);
                  b(j,k) = t * b(j,k);
              endfor
              for L = 1 : r
                  if L ~= j
                      t = -a(L,j);
                      for k = 1 : r
                          a(L,k) = a(L,k) + t * a(j,k);
                          b(L,k) = b(L,k) + t * b(j,k);
                      endfor
                  endif
              endfor           
          endif
          break
      endfor

      if a(i,j) == 0
          disp("Uwaga: Macierz osobliwa!")
          b = "Blad!";
          return
      endif
end
endfunction