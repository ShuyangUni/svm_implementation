function [K] = f_kernel_laplace_rbf(x1, x2, sigma)
if sigma <=0
    disp('[Error]: f_kernel_laplace_rbf(): sigma<=0');
    return;
end

res(1:size(x1,2),1:size(x2,2)) = 0.0;
for i = 1:size(x1,2)
    for j = 1:size(x2,2)
        r = x1(:,i)-x2(:,j);
        res(i,j) = sqrt(r'*r);
    end
end
K = exp(-res/sigma);

end