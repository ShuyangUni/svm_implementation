function [K] = f_kernel_hyperbolic_tangent(x1, x2, k, c)

K = x1'*x2;
K = tanh(K*k+c);

end