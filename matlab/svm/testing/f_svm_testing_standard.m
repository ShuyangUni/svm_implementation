function [num_pos, num_neg] = f_svm_testing_standard(tdata,tlabel,vdata,vlabel,kernel,kparam,alpha,b)

K = f_kernel(tdata',vdata',kernel,kparam);

res = (alpha.*tlabel)'*K + b;
res_y = sign(res);
res_y(find(res_y==0))=1;

idx = find(abs(vlabel - res_y')<1e-3);

num_pos = size(idx,1);
num_neg = size(vlabel,1) - num_pos;

end
