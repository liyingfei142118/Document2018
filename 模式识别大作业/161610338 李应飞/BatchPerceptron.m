% �������֪���㷨
function BatchPerceptron(w1, w2)

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
a = [0 0 0]; % [0 0 0];
Eta = 1; 
time = 0; % ��������
while any(y<=0)
    for i=1:size(y,1)
        y(i) = a * w12(i,:)';
    end;
    a = a + sum(w12(find(y<=0),:));%��������a
    time = time + 1;%��������
    if (time >= 300)
        break;
    end
end;
if (time >= 300)
        disp('Ŀ�꺯���ڹ涨���������������޷�����');
        disp(['�������֪���㷨�Ľ�ʸ��aΪ�� ',num2str(a)]);
else 
disp(['�������֪���㷨����ʱ��ʸ��aΪ�� ',num2str(a)]);
disp(['�������֪���㷨��������kΪ�� ',num2str(time)]);
end

%�ҵ������������еļ��������Ա��ڴ�ӡ��������ͼ
xmin = min(min(w1(:,1)),min(w2(:,1)));
xmax = max(max(w1(:,1)),max(w2(:,1)));
xindex = xmin-1:(xmax-xmin)/100:xmax+1;
yindex = -a(2)*xindex/a(3)-a(1)/a(3);
plot(xindex,yindex);
title('�������֪���㷨ʵ���������ݵķ���');
end