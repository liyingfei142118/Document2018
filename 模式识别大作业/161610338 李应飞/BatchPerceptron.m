% 批处理感知器算法
function BatchPerceptron(w1, w2)

figure;
plot(w1(:,1),w1(:,2),'ro');
hold on;
grid on;
plot(w2(:,1),w2(:,2),'b+');

% 对所有训练样本求增广特征向量y
one = ones(10,1);
y1 = [one w1];
y2 = [one w2];
w12 = [y1; -y2]; % 增广样本规范化
y = zeros(size(w12,1),1); % 错分样本集y初始为零矩阵
% 初始化参数
a = [0 0 0]; % [0 0 0];
Eta = 1; 
time = 0; % 收敛步数
while any(y<=0)
    for i=1:size(y,1)
        y(i) = a * w12(i,:)';
    end;
    a = a + sum(w12(find(y<=0),:));%修正向量a
    time = time + 1;%收敛步数
    if (time >= 300)
        break;
    end
end;
if (time >= 300)
        disp('目标函数在规定的最大迭代次数内无法收敛');
        disp(['批处理感知器算法的解矢量a为： ',num2str(a)]);
else 
disp(['批处理感知器算法收敛时解矢量a为： ',num2str(a)]);
disp(['批处理感知器算法收敛步数k为： ',num2str(time)]);
end

%找到样本在坐标中的集中区域，以便于打印样本坐标图
xmin = min(min(w1(:,1)),min(w2(:,1)));
xmax = max(max(w1(:,1)),max(w2(:,1)));
xindex = xmin-1:(xmax-xmin)/100:xmax+1;
yindex = -a(2)*xindex/a(3)-a(1)/a(3);
plot(xindex,yindex);
title('批处理感知器算法实现两类数据的分类');
end