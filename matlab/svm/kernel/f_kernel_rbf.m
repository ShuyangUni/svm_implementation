    function [K] = f_kernel_rbf(x1, x2, gamma)
if gamma <=0
    disp('[Error]: f_kernel_rbf(): gamma<=0');
    return;
end

res(1:size(x1,2),1:size(x2,2)) = 0.0;
for i = 1:size(x1,2)
    for j = 1:size(x2,2)
        r = x1(:,i)-x2(:,j);
        res(i,j) = r'*r;
    end
end
K = exp(-gamma * res);

end