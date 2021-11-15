function [svm] = f_svm_param_trim_threshold(svm)

alpha = svm.alpha;
threshold = svm.trim_param(1,1);

idx_select = find(alpha>=threshold);

alpha_trim = alpha(idx_select,:);

svm.alpha_trim = alpha_trim;
svm.tdata_trim = svm.tdata(idx_select,:);
svm.tlabel_trim = svm.tlabel(idx_select,:);

end
