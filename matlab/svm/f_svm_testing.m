function [svm] = f_svm_testing(svm)
%% param
tdata = svm.tdata_trim;
tlabel = svm.tlabel_trim;
vdata = svm.vdata;
vlabel = svm.vlabel;
kernel = svm.kernel;
kparam = svm.kernel_param;
bresout = svm.terminal_output;
alpha = svm.alpha_trim;
b = svm.b;

%% process
[num_pos, num_neg] = f_svm_testing_standard(tdata,tlabel,vdata,vlabel,kernel,kparam,alpha,b);

if bresout == 1
    disp(['testing: num_pos: ', num2str(num_pos), ' num_neg: ', num2str(num_neg)]);
end

svm.test_pos = num_pos;
svm.test_neg = num_neg;

end
