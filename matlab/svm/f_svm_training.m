function [svm] = f_svm_training(svm)
tdata = svm.tdata;
tlabel = svm.tlabel;
kernel = svm.kernel;
kparam = svm.kernel_param;
c = svm.c;
bresout = svm.terminal_output;

switch svm.training_method 
    case "standard"
        [alpha, b, t_pos, t_neg] = f_svm_training_standard(tdata, tlabel, kernel, kparam, c, bresout);
    case "smo"
%         [weight, t_pos, t_neg] = f_svm_training_smo(tdata, tlabel, kernel, kparam, c, bresout);
    otherwise
        [alpha, b, t_pos, t_neg] = f_svm_training_standard(tdata, tlabel, kernel, kparam, c, bresout);
end

svm.alpha = alpha;
svm.b = b;
svm.train_pos = t_pos;
svm.train_neg = t_neg;

end

