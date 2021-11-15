function [K] = f_kernel(x1, x2, kernel, kparam)
switch kernel
    case 'gaussian'
        sigma = kparam(1,1);
        K = f_kernel_gaussian(x1,x2,sigma);
    case 'lrbf'
        sigma = kparam(1,1);
        K = f_kernel_laplace_rbf(x1,x2,sigma);
    case 'rbf'
        gamma = kparam(1,1);
        K = f_kernel_rbf(x1,x2,gamma);
    case 'tanh'
        k = kparam(1,1);
        c = kparam(1,2);
        K = f_kernel_hyperbolic_tangent(x1, x2, k, c);
    case 'ntanh'
        K = f_kernel_normalized_hyperbolic_tangent(x1, x2);
    case 'dot'
        K = f_kernel_dot(x1,x2);
    case 'polynomial'
        p = kparam(1,1);
        K = f_kernel_polynomial(x1,x2,p);
end
end