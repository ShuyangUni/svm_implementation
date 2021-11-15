function [svm] = f_svm_param_trim_double(svm)

alpha = svm.alpha;
ratio = svm.trim_param(1,1);
threshold = svm.trim_param(1,2);
n_select = floor(ratio * size(svm.alpha,1));

[~, idx] = sort(alpha,'descend');
idx_select = idx(1:n_select);

idx = find(alpha(idx_select,1)>=threshold);
idx_select = idx_select(idx,1);

alpha_trim = alpha(idx_select,:);

svm.alpha_trim = alpha_trim;
svm.tdata_trim = svm.tdata(idx_select,:);
svm.tlabel_trim = svm.tlabel(idx_select,:);

end
