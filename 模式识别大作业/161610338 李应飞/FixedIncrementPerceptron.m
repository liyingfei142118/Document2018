% �̶�������֪���㷨
function FixedIncrementPerceptron(w1, w2)

[n, d] = size(w1);
figure;
plot(w1(:,1),w1(:,2),'ro');
hold on;
grid on;
plot(w2(:,1),w2(:,2),'b+');

% ������ѵ��������������������y
one = ones(10,1);
y1 = [one w1];
y2 = [one w2];
w12 = [y1; -y2]; % ���������淶��
y = zeros(size(w12,1),1); % ���������y��ʼΪ�����
% ��ʼ������
a = [0 0 0];
Eta = 1; 
% k = 0;
time = 0; % �����Ĳ���
yk = zeros(10,3);

y = a * w12';
while sum(y<=0)>0
%     for i=1:size(y,1)
%         y(i) = a * w12(i,:)';
%     end;
    y = a * w12';
    rej=[];
    for i=1:2*n    %���ѭ������a(K+1) = a(k) + sum {yj���������} y(j)
        if y(i)<=0
            a = a + w12(i,:);
            rej = [rej i];
        end
    end
    %    fprintf('after iter %d, a = %g, %g\n', time, a);
    % rej
    time = time + 1;
    if ((size(rej) == 0) | (time >= 300))
        break;
    end
end;
if (time >= 300)
        disp('Ŀ�꺯���ڹ涨���������������޷�����');
        disp(['�̶�������֪���㷨�Ľ�ʸ��aΪ�� ',num2str(a)]);
else 
disp(['�̶�������֪���㷨����ʱ��ʸ��aΪ�� ',num2str(a)]);
disp(['�̶�������֪���㷨��������ktΪ�� ',num2str(time)]);
end
%�ҵ������������еļ��������Ա��ڴ�ӡ��������ͼ
xmin = min(min(w1(:,1)),min(w2(:,1)));
xmax = max(max(w1(:,1)),max(w2(:,1)));
xindex = xmin-1:(xmax-xmin)/100:xmax+1;
% yindex = -a(2)*xindex/a(3)-a(1)/a(3);
yindex = -a(2)*xindex/a(3) - a(1)/a(3);
plot(xindex,yindex);
title('�̶�������֪���㷨ʵ���������ݵķ���');
end