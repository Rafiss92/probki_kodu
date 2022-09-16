function pole_obliczane=pole(a, b, c, d)
  %Funkcja obliczajaca pole trojkata na plaszczyznie
    e = sqrt((a.x - b.x)^2 + (a.z - b.z)^2);
    f = sqrt((c.y - a.y)^2 + (c.z - a.z)^2);
    podstawa = sqrt((b.x - a.x)^2 + (a.y - c.y)^2);
    g = sqrt((c.z - b.z)^2 + (podstawa)^2);
    pole_obliczane = pole_trojkata(e, f, g);
    e = sqrt((c.x - d.x)^2 + (c.z - d.z)^2);
    f = sqrt((d.y - b.y)^2 + (d.z - b.z)^2);
    pole_obliczane += pole_trojkata(e, f, g);
endfunction