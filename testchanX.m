anchor_position_=[0,60,120,180;
    0,60,0,60];
numofanchor= length(anchor_position_);
plot(anchor_position_(1,:), anchor_position_(2,:), 'rs', 'markersize',6, 'Markerfacecolor','y');
hold on;
tag_position_=[40;
    15];
%numofpoints = length(tag_position_);
Noise = 0.5;
Xs = [];
%for i = 1:numofpoints
    for k = 1: numofanchor
        R0(k) = (sqrt((anchor_position_(1,k) - tag_position_(1,1))^2 + (anchor_position_(2,k) - tag_position_(2, 1))^2)); 
    end
    
    for j = 1:1000
        for k = 1: numofanchor-1
            R(k) = R0(k+1) - R0(1)+ Noise * randn(1); 
        end
        X = chanX(numofanchor, anchor_position_, R);
        Xs = [Xs, X];        
    end
%end
plot(Xs(1,:), Xs(2,:), '.');
plot(tag_position_(1,:), tag_position_(2,:), '^', 'markersize', 10, 'Markerfacecolor','c');
legend('基站坐标', '计算所得坐标', '实际位置');







    

