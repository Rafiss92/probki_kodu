function T = trans(C)
  %Funkcja transponujaca macierze
    for i=1:rows(C)
     for j=1:columns(C)
       T(j,i)=C(i,j);
     end
   end      
endfunction