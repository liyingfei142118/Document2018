%%K-means

clear all
clc

%% ���������ά��̬�����
mu1=[0 0 0];%��������  
S1=[0.23 0 0;0 0.87 0;0 0 0.56];%Э�������
n=100;%��ģ
data1=mvnrnd(mu1,S1,n);   %������˹�ֲ�����

%%�ڶ�������
mu2=[1.25 1.25 1.25];
S2=[0.23 0 0;0 0.87 0;0 0 0.56];
data2=mvnrnd(mu2,S2,100);

%������������
mu3=[-1.25 1.25 -1.25];
S3=[0.23 0 0;0 0.87 0;0 0 0.56];
data3=mvnrnd(mu3,S3,100);

mu4=[1.5 1.5 1.5];
S4=[0.23 0 0;0 0.87 0;0 0 0.56];
data4 =mvnrnd(mu4,S4,100);

%��ʾ����
figure;
plot3(data1(:,1),data1(:,2),data1(:,3),'+');
title('ԭʼ����');
hold on
plot3(data2(:,1),data2(:,2),data2(:,3),'r+');
plot3(data3(:,1),data3(:,2),data3(:,3),'g+');
plot3(data4(:,1),data4(:,2),data3(:,3),'y+');
grid on;


data=[data1;data2;data3;data4];   
[row,col] = size(data);
K = 4;
max_iter = 300;%%��������
min_impro = 0.1;%%%%��С����
display = 1;%%%�ж�����
center = zeros(K,col);
U = zeros(K,col);
%% ��ʼ����������
mi = zeros(col,1);
ma = zeros(col,1);
for i = 1:col
    mi(i,1) = min(data(:,i));
    ma(i,1) = max(data(:,i));
    center(:,i) = ma(i,1) - (ma(i,1) - mi(i,1)) * rand(K,1);
end

%% ��ʼ����
for o = 1:max_iter
    %% ����ŷ�Ͼ���,��norm����
    for i = 1:K
        dist{i} = [];
        for j = 1:row
            dist{i} = [dist{i};data(j,:) - center(i,:)];
        end
    end
    
    minDis = zeros(row,K);
    for i = 1:row
        tem = [];
        for j = 1:K
            tem = [tem norm(dist{j}(i,:))];
        end
        [nmin,index] = min(tem);
        minDis(i,index) = norm(dist{index}(i,:));
    end
    
    
    %% ���¾�������
     for i = 1:K
        for j = 1:col
            U(i,j) = sum(minDis(:,i).*data(:,j)) / sum(minDis(:,i));
        end
     end
     
     %% �ж�
      if display
   end
   if o >1,
       if max(abs(U - center)) < min_impro;
           break;
       else
           center = U;
       end
   end
end

 %% �������������
 class = [];
 for i = 1:row
     dist = [];
     for j = 1:K
         dist = [dist norm(data(i,:) - U(j,:))];
     end
     [nmin,index] = min(dist);
     class = [class;data(i,:) index];
 end
  
 %% ��ʾ�����
[m,n] = size(class);
figure;
title('������');
hold on;
for i=1:row 
    if class(i,4)==1   
         plot3(class(i,1),class(i,2),class(i,3),'ro'); 
    elseif class(i,4)==2
         plot3(class(i,1),class(i,2),class(i,3),'go'); 
    elseif class(i,4) == 3
         plot3(class(i,1),class(i,2),class(i,3),'bo'); 
    else
        plot3(class(i,1),class(i,2),class(i,3),'yo'); 
    end
end
grid on;
