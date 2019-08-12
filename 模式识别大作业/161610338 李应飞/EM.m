% global parameter which can be altered easily to run a different result
WIDTH = 10000;
HEIGHT = 10000;
RADIUS = 6000;
ITERATE_COUNT = 10;
% generate the initial points
center_points = [];
all_points = [];
color = ['b', 'm', 'g', 'y', 'c'];
path = ['*', 'o', '^'];
for i = 1:5
    center_point = [randi(WIDTH) + RADIUS, randi(HEIGHT) + RADIUS];
    center_points(i, :) = center_point;
    for j = 1:1000
        while (true)
            point = [randi(WIDTH + RADIUS * 2), randi(HEIGHT + RADIUS * 2)];
            if (sqrt((point(1) - center_point(1))^2 + (point(2) - center_point(2))^2) <= RADIUS)
                if (length(all_points) == 0)
                    all_points(1, :) = point;
                    break;
                end
                all_points(length(all_points(:,1)) + 1, :) = point;
                break;
            end
        end
        plot(point(1), point(2), [color(i), '.']);
        hold on;
    end
end
% calculate three paths with three independent initial start points
for m = 1:3
    % init the start points
    res = [];
    for i = 1:5
        point = [randi(WIDTH), randi(HEIGHT)];
        res(1, i, :) = point;
    end
    % iterate
    distance = [];
    for i = 1:ITERATE_COUNT
        s = size(res);
        % cur_center is a 3-dimension matrix
        % the length of first dimension is 1
        cur_center = res(s(1), :, :);
        for j = 1:length(all_points);
            for k = 1: s(2);
                point_1 = all_points(j, :);
                point_2 = [cur_center(1, k, 1), cur_center(1, k, 2)];
                distance(j, k) = sqrt((point_1(1) - point_2(1))^2 + (point_1(2) - point_2(2))^2);
            end
        end
        % assign each point to the new defined category
        assign = zeros(length(distance), 1);
        for j = 1:s(2)
            temp = distance(:, j);
            smallest = sort(temp);
            smallest = smallest(1:10);
            for l=1:length(smallest)
                for k = 1:length(temp)
                    if (smallest(l) == temp(k))
                        assign(k) = j;
                    end
                end
            end
        end
        for j = 1:length(distance)
            if (assign(j) ~= 0)
                continue;
            end
            [value, index] = min(distance(j, :));
            assign(j) = index;
        end
        % calculate the total value of x, y for each category
        temp2 = zeros(s(2), 3);
        for j = 1:length(assign)
            temp2(assign(j), 3) = temp2(assign(j), 3) + 1;
            temp2(assign(j), 1) = temp2(assign(j), 1) + all_points(j, 1);
            temp2(assign(j), 2) = temp2(assign(j), 2) + all_points(j, 2);
        end
        % get the new local center
        for j = 1:s(2)
            res(s(1) + 1, j, :) = [temp2(j, 1) / temp2(j, 3), temp2(j, 2) / temp2(j, 3)];
        end
    end
    % plot the local center changing path
    s = size(res);
    for i = 1:s(2)
        x = res(1:s(1), i, 1);
        y = res(1:s(1), i, 2);
        plot(x, y, ['r', path(m), '-']);
        hold on;
    end
end
% save the picture
title(['期望最大化算法 半径', num2str(RADIUS)]);
saveas(gcf, ['em_', num2str(RADIUS), '.jpg'])
hold off;
