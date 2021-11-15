function [svm] = f_svm_param_trim(svm)

switch svm.trim_method
    case 'threshold'
        [svm] = f_svm_param_trim_threshold(svm);
    case 'ratio'
        [svm] = f_svm_param_trim_ratio(svm);
    case 'double'
        [svm] = f_svm_param_trim_double(svm);
    otherwise
        [svm] = f_svm_param_trim_threshold(svm);
end

end
