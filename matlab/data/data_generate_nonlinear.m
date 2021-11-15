clc;
clear;
addpath(genpath(pwd));

%% data generation
% param
n = 1000;
rate_training = 0.8;
offset = [2,4]';
range = [3,3]';

r = 1;

n_train = floor(n * rate_training);
n_test = n - n_train;

% uniform distribution
data = (rand(n,2)-0.5).*range';
label = ones(n,1);

dis = sum(data.^2,2);
idx = find(dis<(r^2));
label(idx) = -1;

data = data + offset';

%% display
f_display_data(data,label);

%% split data
idx = randperm(n);
idx_train = idx(:,1:n_train); 
idx_test = idx(:,(n_train+1):end);

tdata = data(idx_train,:);
tlabel = label(idx_train,:);
vdata = data(idx_test,:);
vlabel = label(idx_test,:);
