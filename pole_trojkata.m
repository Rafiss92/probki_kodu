function pole=pole_trojkata(r,t,g)
  %Funkcja oblicza pole trojkata
    p = (r + t + g) / 2;
    pole = sqrt(p * (p - r)*(p - t)*(p - g)); 
endfunction