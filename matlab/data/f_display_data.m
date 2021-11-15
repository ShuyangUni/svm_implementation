function f_display_data(data,label)
if nargin==0
    load('data_nonlinear.mat');
end
figure;
hold on;
axis equal;

idx_po = find(label==1);
idx_ne = find(label==-1);
plot(data(idx_po,1),data(idx_po,2),'.b');
plot(data(idx_ne,1),data(idx_ne,2),'.r');
end

