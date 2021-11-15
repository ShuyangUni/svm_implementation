function [alpha, b, num_pos, num_neg] = f_svm_training_standard(tdata, tlabel, kernel, kparam, c, bresout)
x = tdata;
y = tlabel;

[n, ~] = size(x);

K = f_kernel(x',x',kernel,kparam);

H = (y*y').*K;
f = ones(n,1) * -1;
A = [];
b = [];
Aeq = y';
beq = 0;
lb = zeros(n,1);
ub = ones(n,1) * c;

alpha = quadprog(H,f,A,b,Aeq,beq,lb,ub);
[~,idx] = max(alpha);

b = tlabel(idx,1) - sum(alpha .* tlabel .* K(:,idx),1);

if bresout==1
    [num_pos, num_neg] = f_svm_testing_standard(x,y,x,y,kernel,kparam,alpha,b);
    disp(['training: num_pos: ', num2str(num_pos), ' num_neg: ', num2str(num_neg)]);
end

end
