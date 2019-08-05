  function [raiz, fr, ea, iter] = falsapos (func, a, b, es, maxit)
    test = func(a) * func(b);
    if(test > 0) error ('Este intervalo no es permitido por que no hay cambio de signo'), 
    end  
    r=a;
    iter = 0;
    while (1)
      iter = iter + 1;
      rold = r;
      r = b - ((func(b)*(a-b)) / (func(a) - func(b))); %comentarios
      ea = abs((r-rold)/r)*100;
      test = func(a)*func(r);
      if(test < 0)
      b=r;
      elseif(test >0)
      a=r;
      else
      ea=0;
     end
        if ea<= es | iter >= maxit, break, 
        end
    end
      raiz = r; fr = func(r)
  endfunction