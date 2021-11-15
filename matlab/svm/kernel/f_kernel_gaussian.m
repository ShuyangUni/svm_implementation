function [K] = f_kernel_gaussian(x1, x2, sigma)
if sigma <=0
    disp('[Error]: f_kernel_gaussian(): sigma<=0');
    return;
end

res(1:size(x1,2),1:size(x2,2)) = 0.0;
for i = 1:size(x1,2)
    for j = 1:size(x2,2)
        r = x1(:,i)-x2(:,j);
        res(i,j) = r'*r;
    end
end
K = exp(-res/(2*sigma^2));

end