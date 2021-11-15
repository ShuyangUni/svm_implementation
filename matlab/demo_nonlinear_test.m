clc;
clear;
addpath(genpath(pwd));

%% get data
load('/home/uni/matlab/MySVMLib/data/data_nonlinear.mat');

%% construct new struct
svm = [];
% data
svm.tdata = tdata;
svm.tlabel = tlabel;
svm.vdata = vdata;
svm.vlabel = vlabel;
% kernel
svm.kernel = 'rbf';
svm.kernel_param = [0.1];
% svm.kernel = 'ntanh';
% svm.kernel_param = [];

% training method
svm.training_method = 'standard';
% soft margin
svm.c = Inf;
% terminal display 
svm.terminal_output = 1;

% parameter trim
svm.trim_method = 'threshold';
svm.trim_param = [0.001];

%% training
tic
[svm] = f_svm_training(svm);
toc

%% parameter triming
[svm] = f_svm_param_trim(svm);

%% testing
tic
[svm] = f_svm_testing(svm);
toc