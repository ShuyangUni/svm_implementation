function [K] = f_kernel_polynomial(x1,x2,p)
if p <=0
    disp('[Error]: f_kernel_polynomial(): p<=0');
    return;
end

K = x1'*x2;
K = (K + 1).^p;

end