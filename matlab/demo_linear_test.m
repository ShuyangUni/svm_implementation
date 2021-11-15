clc;
clear;
addpath(genpath(pwd));

%% get data
load('/home/uni/matlab/MySVMLib/data/data_linear.mat');

%% construct new struct
svm = [];
% data
svm.tdata = tdata;
svm.tlabel = tlabel;
svm.vdata = vdata;
svm.vlabel = vlabel;
% kernel
svm.kernel = 'dot';
svm.kernel_param = [];
% training method
svm.training_method = 'Standard';
% soft margin
svm.c = 1000;
% parameter trim
svm.trim_method = 'ratio';
svm.trim_param = [1.0];
% svm.trim_method = 'threshold';
% svm.trim_param = [0.01];
% svm.trim_method = 'double';
% svm.trim_param = [0.1, 0.01];

% terminal display 
svm.terminal_output = 1;

%% training
tic;
[svm] = f_svm_training(svm);
toc

%% parameter triming
[svm] = f_svm_param_trim(svm);

%% testing
tic
[svm] = f_svm_testing(svm);
toc