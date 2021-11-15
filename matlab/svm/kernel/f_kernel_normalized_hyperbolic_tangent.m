function [K] = f_kernel_normalized_hyperbolic_tangent(x1, x2)

K = x1'*x2;
c = -mean(K,'all');
k = 1/cov(reshape(K,[],1));
c = k*c;
K = tanh(K*k+c);

end